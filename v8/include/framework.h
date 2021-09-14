#pragma once

#include <any>
#include <array>
#include <string>
#include <vector>
#include <variant>
#include <iterator>
#include <stack>
#include <memory>
#include <unordered_map>
#include <mutex>
#include <map>
#include <cmath>
#include <limits>
#include <tuple>
#include <utility>
#include <functional>
#include <thread>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <regex>
#include <chrono>
#include <random>
#include <stdexcept>
#include <boost/format.hpp>
#include <boost/log/sinks.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/sources/severity_channel_logger.hpp>
#include <boost/log/sources/global_logger_storage.hpp>
#include <boost/locale.hpp>
#include <boost/log/support/date_time.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>
#include <boost/log/expressions/predicates/is_debugger_present.hpp>
#include <boost/log/utility/setup/console.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/expressions.hpp>
#include <boost/algorithm/string/erase.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <v8.h>

using namespace std::chrono_literals;
namespace sinks = boost::log::sinks;
BOOST_LOG_INLINE_GLOBAL_LOGGER_DEFAULT(__LOG__, boost::log::sources::severity_channel_logger_mt<boost::log::trivial::severity_level>);

namespace shelllet {
#define LOG_TRACE(c) BOOST_LOG_CHANNEL_SEV(__LOG__::get(), c, boost::log::trivial::trace)
#define LOG_DEBUG(c) BOOST_LOG_CHANNEL_SEV(__LOG__::get(), c, boost::log::trivial::debug)
#define LOG_INFO(c) BOOST_LOG_CHANNEL_SEV(__LOG__::get(), c,boost::log::trivial::info)
#define LOG_WARN(c) BOOST_LOG_CHANNEL_SEV(__LOG__::get(), c, boost::log::trivial::warning)
#define LOG_ERROR(c) BOOST_LOG_CHANNEL_SEV(__LOG__::get(), c,boost::log::trivial::error)
#define LOG_FATAL(c) BOOST_LOG_CHANNEL_SEV(__LOG__::get(), c,boost::log::trivial::fatal)

#define THROW_SYSTEM_ERROR(n) throw boost::system::system_error(n, boost::system::detail::system_error_category(), (boost::format("%1% %2%") % __FUNCTION__ % __LINE__).str())

#define STR(str) #str

#define VERSION "0.5.0"
	static inline const char K_CONST_MARK_UNKNOWN[] = "unknown";
	static inline const char K_CONST_ERROR_CALLED[] = "# invalid object.";
	static inline const char K_CONST_ERROR_NULL_PTR[] = "# this null.";
	static inline const char K_CONST_ERROR_INVLAID_PARAM[] = "# invalid param.";
}

namespace shelllet {
	namespace logs {
		typedef boost::log::sinks::synchronous_sink<boost::log::sinks::debug_output_backend> sink_debug_t;
		typedef boost::log::sinks::synchronous_sink<boost::log::sinks::simple_event_log_backend> event_sink_t;

		BOOST_LOG_ATTRIBUTE_KEYWORD(keyword_channel, "Channel", std::string);

		static inline auto global_log_format = (boost::log::expressions::format("[%1%]<%2%> : <%3%> %4%")
			% boost::log::expressions::format_date_time<boost::posix_time::ptime>("TimeStamp", "%Y-%m-%d %H:%M:%S")
			% boost::log::expressions::attr< std::string >("Channel")
			% boost::log::trivial::severity
			% boost::log::expressions::message);

		static inline void Initialize(const std::filesystem::path& filename, boost::log::trivial::severity_level level) {
			boost::log::add_common_attributes();

			boost::log::core::get()->set_filter(boost::log::trivial::severity >= level);

			boost::shared_ptr<sink_debug_t> sink(new sink_debug_t());
			sink->set_formatter(global_log_format);
			sink->set_filter(boost::log::expressions::is_debugger_present());
			//boost::log::core::get()->set_filter(boost::log::expressions::is_debugger_present());
			boost::log::core::get()->add_sink(sink);

			boost::log::add_console_log(std::clog, boost::log::keywords::format = global_log_format);

			boost::log::add_file_log(boost::log::keywords::file_name = filename.c_str(),
				boost::log::keywords::rotation_size = 1 * 1024 * 1024,
				boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
				boost::log::keywords::format = global_log_format
				//boost::log::keywords::channel = keyword_channel == channel
			);
		}

		static inline boost::log::trivial::severity_level LevelFromString(const std::string& level) {
			static std::map<std::string, boost::log::trivial::severity_level> map = {
			{"trace", boost::log::trivial::trace} ,
			{"debug", boost::log::trivial::debug} ,
			{"info", boost::log::trivial::info} ,
			{"warning", boost::log::trivial::warning} ,
			{"error", boost::log::trivial::error} ,
			{"fatal", boost::log::trivial::fatal}
			};

			if (auto itor = map.find(level); itor != map.cend()) {
				return itor->second;
			}
			return boost::log::trivial::fatal;
		}
	}

	enum class IsolateData : uint32_t {
		GlobalContext,
		GlobalValue,
		SetErrorAddress,
	};
	enum class ContextEmbedderData : uint32_t {
		WorkingDirectory,
	};
#define V8_GL_CONTEXT(isolate) static_cast<v8::Global<v8::Context>*>(isolate->GetData(static_cast<uint32_t>(IsolateData::GlobalContext)))
#define V8_GL_VALUE(isolate) static_cast<std::list<std::unique_ptr<Resource, Resource::Deleter>>*>(isolate->GetData(static_cast<uint32_t>(IsolateData::GlobalValue)))
#define F_SET_LAST_ERROR(isolate, err) static_cast<void(*)(const std::variant<int, std::string>&)>(isolate->GetData(static_cast<uint32_t>(IsolateData::SetErrorAddress)))(err)

#define V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(Args) v8::Isolate* isolate = Args.GetIsolate();	\
		v8::HandleScope handleScope(isolate);	\
		v8::Local<v8::Context> context = v8::Local<v8::Context>::New(isolate, V8_GL_CONTEXT(isolate)->Get(isolate));	\
		v8::Context::Scope contextScope(context); \
	    try

#define V8_CREATE_LOCAL_CONTEXT_END \
        catch (const std::exception& err) { \
		    isolate->ThrowException(v8::String::NewFromUtf8(isolate, err.what()).ToLocalChecked()); \
	    }

#define V8_CREATE_LOCAL_CONTEXT_END_WITH_RETURN(ret) \
        catch (const std::exception& err) { \
		    isolate->ThrowException(v8::String::NewFromUtf8(isolate, err.what()).ToLocalChecked()); \
	    } \
        return ret;

#define V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate) \
		v8::Locker locker(isolate);	\
		v8::Isolate::Scope isolateScope(isolate); \
		v8::HandleScope handleScope(isolate);	\
		v8::Local<v8::Context> context = v8::Local<v8::Context>::New(isolate, V8_GL_CONTEXT(isolate)->Get(isolate));	\
		v8::Context::Scope contextScope(context);   \
        try

#define V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_ISOLATE(isolate)	\
		v8::HandleScope handleScope(isolate);	\
		v8::Local<v8::Context> context = v8::Local<v8::Context>::New(isolate, V8_GL_CONTEXT(isolate)->Get(isolate));	\
		v8::Context::Scope contextScope(context); \
        try

#define V8_NEW_STRING_VAR(isolate, v) v8::String::NewFromUtf8(isolate, v).ToLocalChecked()
#define V8_NEW_WSTRING_VAR(isolate, v) v8::String::NewFromTwoByte(isolate, reinterpret_cast<const uint16_t*>(v)).ToLocalChecked()
}
namespace shelllet {
	template <typename T>
	using CopyablePersistent = v8::Persistent<T, v8::CopyablePersistentTraits<T>>;

	static inline const char* ToString(const v8::String::Utf8Value& value) {
		return *value ? *value : "<string conversion failed>";
	}
	static inline const wchar_t* ToWString(const v8::String::Value& value) {
		return *value ? reinterpret_cast<const wchar_t*>(*value) : L"<string conversion failed>";
	}
	static inline std::string GetConstructorName(v8::Isolate* isolate, const v8::Local<v8::Value>& value) {
		if (value->IsObject())
			return ToString({ isolate ,value->ToObject(isolate->GetCurrentContext()).ToLocalChecked()->GetConstructorName() });
		return std::string();
	}
	static inline std::string GetException(v8::Isolate* isolate, const v8::TryCatch& tryCatch)
	{
		v8::HandleScope handleScope(isolate);
		v8::String::Utf8Value exception(isolate, tryCatch.Exception());
		const char* exceptionString = ToString(exception);
		v8::Local<v8::Message> message = tryCatch.Message();
		std::ostringstream stream;
		if (message.IsEmpty()) {
			// V8 didn't provide any extra information about this error; just print the exception.
			stream << exceptionString;
		}
		else {
			// Print (filename):(line number): (message).
			v8::String::Utf8Value filename(isolate, message->GetScriptOrigin().ResourceName());
			v8::Local<v8::Context> context(isolate->GetCurrentContext());
			const char* filenameString = ToString(filename);
			int linenum = message->GetLineNumber(context).FromJust();

			stream << filenameString << ":" << linenum << ": " << exceptionString;
			// Print line of source code.
			v8::String::Utf8Value sourceline(isolate, message->GetSourceLine(context).ToLocalChecked());
			const char* sourcelineString = ToString(sourceline);
			stream << sourcelineString;
			// Print wavy underline (GetUnderline is deprecated).
			int start = message->GetStartColumn(context).FromJust();
			for (int i = 0; i < start; i++) {
				stream << " ";
			}
			int end = message->GetEndColumn(context).FromJust();
			for (int i = start; i < end; i++) {
				stream << "^";
			}
			stream << "\n";
			v8::Local<v8::Value> stackTrace;
			if (tryCatch.StackTrace(context).ToLocal(&stackTrace) && stackTrace->IsString() && v8::Local<v8::String>::Cast(stackTrace)->Length() > 0) {
				v8::String::Utf8Value stackTrace(isolate, stackTrace);
				stream << ToString(stackTrace);
			}
		}

		return stream.str();
	}

	template <typename T>
	static void ToArray(v8::Isolate* isolate, const v8::Local<v8::TypedArray>& value, std::vector<T>& buffer) {
		if constexpr (std::is_same<std::decay_t<T>, std::uint32_t>::value)
		{
			if (v8::Local<v8::Uint32Array> array = v8::Local<v8::Uint32Array>::Cast(value); !array.IsEmpty()) {
				buffer.resize(array->ByteLength());
				array->CopyContents(buffer.data(), array->ByteLength());
			}
		}
		else if constexpr (std::is_same<std::decay_t<T>, std::uint16_t>::value)
		{
			if (v8::Local<v8::Uint16Array> array = v8::Local<v8::Uint16Array>::Cast(value); !array.IsEmpty()) {
				buffer.resize(array->ByteLength());
				array->CopyContents(buffer.data(), array->ByteLength());
			}
		}
		else if (std::is_same<std::decay_t<T>, std::uint8_t>::value)
		{
			if (v8::Local<v8::Uint8Array> array = v8::Local<v8::Uint8Array>::Cast(value); !array.IsEmpty()) {
				buffer.resize(array->ByteLength());
				array->CopyContents(buffer.data(), array->ByteLength());
			}
		}
		else if (std::is_same<std::decay_t<T>, std::int8_t>::value) {
			if (v8::Local<v8::Int8Array> array = v8::Local<v8::Int8Array>::Cast(value); !array.IsEmpty()) {
				buffer.resize(array->ByteLength());
				array->CopyContents(buffer.data(), array->ByteLength());
			}
		}

		if (v8::Local<v8::Int32Array> array = v8::Local<v8::Int32Array>::Cast(value); !array.IsEmpty()) {
			buffer.resize(array->ByteLength());
			array->CopyContents(buffer.data(), array->ByteLength());
		}
	}

	template <typename T>
	static void ToArray(v8::Isolate* isolate, const v8::Local<v8::Array>& value, std::vector<T>& buffer) {
		buffer.resize(value->Length());
		if constexpr (std::is_same<T, std::uint32_t>::value
			|| std::is_same<std::decay_t<T>, std::uint8_t>::value
			|| std::is_same<std::decay_t<T>, std::uint16_t>::value)
		{
			for (std::uint32_t i = 0; i < value->Length(); ++i) {
				buffer[i] = value->Get(isolate->GetCurrentContext(), i).ToLocalChecked()->Uint32Value(isolate->GetCurrentContext()).FromJust();
			}
		}
		if constexpr (std::is_same<std::decay_t<T>, std::byte>::value) {
			for (std::uint32_t i = 0; i < value->Length(); ++i) {
				buffer[i] = static_cast<std::byte>(value->Get(isolate->GetCurrentContext(), i).ToLocalChecked()->Uint32Value(isolate->GetCurrentContext()).FromJust());
			}
		}
		//	else {
				//for (std::uint32_t i = 0; i < value->Length(); ++i) {
		//buffer[i] = value->Get(isolate->GetCurrentContext(), i).ToLocalChecked()->Int32Value(isolate->GetCurrentContext()).FromJust();
		//}
	//}
	}
	template<typename T>
	static auto ToArray(v8::Isolate* isolate, const v8::Local<v8::Value>& value) {
		std::vector<T> buffer;
		if (value->IsArray()) {
			ToArray<T>(isolate, v8::Local<v8::Array>::Cast(value), buffer);
		}
		else if (value->IsTypedArray()) {
			ToArray<T>(isolate, v8::Local<v8::TypedArray>::Cast(value), buffer);
		}

		return buffer;
	}

	static	inline v8::Local<v8::Uint8Array> NewArray(v8::Isolate* isolate, const std::vector<std::byte>& value)
	{
		v8::Local<v8::ArrayBuffer> array = v8::ArrayBuffer::New(isolate, value.size());
		std::memcpy(array->GetContents().Data(), &value[0], array->ByteLength());

		return v8::Uint8Array::New(array, 0, array->ByteLength());
	}
	template <typename T>
	static inline v8::Local<v8::Array> NewArray(v8::Isolate* isolate, const std::vector<T>& v)
	{
		v8::Local<v8::Array> array = v8::Array::New(isolate, v.size());
		for (int i = 0; i < v.size(); ++i) {
			if constexpr (std::is_same<T, std::wstring>::value) {
				array->Set(isolate->GetCurrentContext(), i, V8_NEW_WSTRING_VAR(isolate, v.at(i).c_str()));
			}
			else if constexpr (std::is_same<T, std::string>::value) {
				array->Set(isolate->GetCurrentContext(), i, V8_NEW_STRING_VAR(isolate, v.at(i).c_str()));
			}
		}
		return array;
	}
	static inline std::filesystem::path FixRelativePath(const std::filesystem::path& path, v8::Isolate* isolate) {
		if (path.is_relative()) {
			std::filesystem::path root = ToString({ isolate, isolate->GetCurrentContext()->GetEmbedderData(static_cast<int>(ContextEmbedderData::WorkingDirectory)) });
			LOG_DEBUG("v8") << "# rel: " << std::filesystem::relative(path, root);
			if (std::filesystem::relative(path, root).empty())
				return (root / path).lexically_normal();
		}
		return path.lexically_normal();
	}
}
#define V8_CREATE_ENUM_SYMBOL(T, I, C, N, V) \
T->Set(I, #V, v8::Symbol::New(I, V8_NEW_STRING_VAR(I, std::to_string(C::N::V).c_str())))

namespace shelllet {
	class Private
	{
	public:
		Private() = default;
		virtual ~Private() {
			if (!weak.IsEmpty()) {
				weak.ClearWeak();
				weak.Reset();
			}
		}
		v8::Persistent<v8::Object> weak;
	};

	template<typename T, bool M, typename = void>
	class ObjectPrivate :public T, public Private {
	public:
		template<typename ... Args>
		ObjectPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : T(std::forward<Args>(args)...), object(isolate, obj) {
		}

		T* operator-> () {
			return dynamic_cast<T*>(this);
		}
		const T* operator-> () const {
			return dynamic_cast<T*>(this);
		}
		operator T* () {
			return dynamic_cast<T*>(this);
		}
		operator const T* () const {
			return dynamic_cast<const T*>(this);
		}

		template<typename... Args>
		v8::Local<v8::Value> call(const char* name, Args&&... args) const {
			v8::Isolate* isolate = v8::Isolate::GetCurrent();
			v8::Local<v8::Object> local = holder(isolate);
			v8::Local<v8::Object> proto = local->GetPrototype()->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
			v8::Local<v8::Value> value = proto->Get(isolate->GetCurrentContext(), V8_NEW_STRING_VAR(isolate, name)).ToLocalChecked();
			v8::Local<v8::Function> func = v8::Local<v8::Function>::Cast(value);
			if constexpr (sizeof...(Args) == 0) {
				return func->CallAsFunction(isolate->GetCurrentContext(), local, 0, {}).ToLocalChecked();
			}
			else {
				v8::Local<v8::Value> argv[] = { std::forward<Args>(args)... };
				return func->CallAsFunction(isolate->GetCurrentContext(), local, std::size(argv), argv).ToLocalChecked();
			}
		}

		virtual bool hasOwnProperty(const std::string& name) const
		{
			v8::Isolate* isolate = v8::Isolate::GetCurrent();
			v8::Local<v8::Object> proto = holder(isolate)->GetPrototype()->ToObject(isolate->GetCurrentContext()).ToLocalChecked();
			return proto->HasOwnProperty(isolate->GetCurrentContext(), V8_NEW_STRING_VAR(isolate, name.c_str())).FromJust();
		}

		v8::Local<v8::Object> holder(v8::Isolate* isolate) const { return object.Get(isolate); }
	private:
		v8::Global<v8::Object> object;
		ObjectPrivate() = delete;
	};

	template<typename T, bool M>
	class ObjectPrivate<T, M, typename std::enable_if<!std::bool_constant<M>::value>::type> : public Private {
	public:
		ObjectPrivate(v8::Isolate*, const v8::Local<v8::Object>&, T* p) : p(p) {
		}

		operator T* () {
			return dynamic_cast<T*>(p.get());
		}
		operator const T* () const {
			return dynamic_cast<const T*>(p.get());
		}

		T* operator-> () {
			return dynamic_cast<T*>(p.get());
		}
		const T* operator-> () const {
			return dynamic_cast<const T*>(p.get());
		}
	private:
		std::shared_ptr<T> p;
		//ObjectPrivate() = delete;
	};
}

namespace shelllet {
	class Empty {
	public:
		virtual ~Empty() {}
	};

	template<typename T, typename U, bool C> // can remove c.
	class ObjectWrapper : public Empty
	{
	public:
		template <bool M>
		ObjectWrapper(ObjectPrivate<T, M>& d, const v8::FunctionCallbackInfo<v8::Value>& args)
			: d_ptr(std::unique_ptr<ObjectPrivate<T, M>>(&d))
		{
		}

		ObjectWrapper(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) {}
		ObjectWrapper(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) {}

		virtual ~ObjectWrapper() {}
		virtual void toString(std::stringstream& ss) const { ss << "[object" << " " << U::Name() << "]"; }

		template <typename... Args>
		static v8::Local<v8::Value> New(v8::Isolate* isolate, Args&&... args)
		{
			//std::unique_ptr<T> p = std::make_unique<T>(std::forward<Args>(args)...);
			v8::Local<v8::Value> argv[] = { std::forward<Args>(args)... };
			v8::Local<v8::Name> name = V8_NEW_STRING_VAR(isolate, U::Name());
			v8::Local<v8::Value> value = isolate->GetCurrentContext()->Global()->Get(isolate->GetCurrentContext(), name).ToLocalChecked();
			if (!value->IsFunction()) {
				throw std::runtime_error((boost::format("#! `%1%` not registered.") % U::Name()).str());
			}
			v8::Local<v8::Function> func = value.As<v8::Function>();
			auto result = func->CallAsConstructor(isolate->GetCurrentContext(), std::size(argv), argv);
			if (!result.IsEmpty())
				return result.ToLocalChecked();
			return v8::Local<v8::Value>();
		}

		static v8::Local<v8::Value> New2(v8::Isolate* isolate, T* p)
		{
			auto fn = WrapClass(isolate, p);
			auto v = fn->GetFunction(isolate->GetCurrentContext()).ToLocalChecked()->CallAsConstructor(isolate->GetCurrentContext(), 0, {});
			return v.ToLocalChecked();
		}
		static U* From(const v8::Local<v8::Value>& value, int index = 0) {
			if (value->IsObject()) {
				v8::Local<v8::Object> o = value.As<v8::Object>();
				if (o->InternalFieldCount() > index)
					return dynamic_cast<U*>(static_cast<Empty*>(o->GetAlignedPointerFromInternalField(index)));
			}
			return nullptr;
		}
		template<typename M>
		static inline M* UnWrap(const v8::Local<v8::Object>& value, int index = 0) {
			if (value->InternalFieldCount() > index)
				return dynamic_cast<M*>(static_cast<Empty*>(value->GetAlignedPointerFromInternalField(index)));

			return nullptr;
		}
	public:
		operator const T* () const {
			if (std::holds_alternative<std::unique_ptr<ObjectPrivate<T, true>>>(d_ptr))
				return	*std::get<std::unique_ptr<ObjectPrivate<T, true>>>(d_ptr);
			else {
				return *std::get<std::unique_ptr<ObjectPrivate<T, false>>>(d_ptr);
			}
			//return *d_ptr;
		}
		operator T* () {
			//return *d_ptr;
			if (std::holds_alternative<std::unique_ptr<ObjectPrivate<T, true>>>(d_ptr))
				return	*std::get<std::unique_ptr<ObjectPrivate<T, true>>>(d_ptr);
			else {
				return	*std::get < std::unique_ptr<ObjectPrivate<T, false>>>(d_ptr);
			}
		}

		const T* operator -> () const {
			return static_cast<const T*>(*this);
		}
		T* operator -> () {
			return static_cast<T*>(*this);
		}

		static v8::Local<v8::FunctionTemplate> WrapClass(v8::Isolate* isolate, T* p = nullptr)
		{
			v8::Local<v8::FunctionTemplate> tpl = v8::FunctionTemplate::New(isolate, U::NewCallback, v8::External::New(isolate, p));
			//if constexpr (C) {
			static_cast<void>(std::make_unique<U>(isolate, tpl));
			static_cast<void>(std::make_unique<U>(isolate, tpl->PrototypeTemplate()));
			//}
			tpl->PrototypeTemplate()->Set(isolate, "toString", v8::FunctionTemplate::New(isolate, [](const v8::FunctionCallbackInfo<v8::Value>& args) {
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					if (auto* self = UnWrap<ObjectWrapper<T, U, C>>(args.This()); self) {
						std::stringstream ss;
						self->toString(ss);
						args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, ss.str().c_str()));
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
				}));
			tpl->InstanceTemplate()->SetInternalFieldCount(1);
			return tpl;
		}

	protected:
		static void NewCallback(const v8::FunctionCallbackInfo<v8::Value>& args)
		{
			V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
			{
				if constexpr (!C) {
					throw std::logic_error((boost::format("`%1%` is not a constructor") % U::Name()).str());
				}

				if (!args.IsConstructCall()) {
					throw std::logic_error("should use `new` to create instance");
				}
				ObjectWrapper<T, U, C>* value = nullptr;
				if (auto* self = args.Data().As<v8::External>()->Value(); self) {
					value = new U(static_cast<T*>(self), args);
				}
				else {
					value = new U(args);
				}

				args.This()->SetAlignedPointerInInternalField(0, static_cast<Empty*>(value));
				if (std::holds_alternative<std::unique_ptr<ObjectPrivate<T, true>>>(value->d_ptr)) {
					std::get<std::unique_ptr<ObjectPrivate<T, true>>>(value->d_ptr)->weak.Reset(isolate, args.This());
					std::get<std::unique_ptr<ObjectPrivate<T, true>>>(value->d_ptr)->weak.SetWeak(dynamic_cast<U*>(value), [](const v8::WeakCallbackInfo<U>& data) {
						delete data.GetParameter();
						LOG_INFO("v8") << "# free class `" << U::Name() << "`" << std::endl;
						}, v8::WeakCallbackType::kParameter);
				}
				else {
					std::get<std::unique_ptr<ObjectPrivate<T, false>>>(value->d_ptr)->weak.Reset(isolate, args.This());
					std::get<std::unique_ptr<ObjectPrivate<T, false>>>(value->d_ptr)->weak.SetWeak(dynamic_cast<U*>(value), [](const v8::WeakCallbackInfo<U>& data) {
						delete data.GetParameter();
						LOG_INFO("v8") << "# free class `" << U::Name() << "`" << std::endl;
						}, v8::WeakCallbackType::kParameter);
				}

				args.GetReturnValue().Set(args.This());
			}
			V8_CREATE_LOCAL_CONTEXT_END
		}

	protected:
		std::variant<std::unique_ptr<ObjectPrivate<T, true>>, std::unique_ptr<ObjectPrivate<T, false>>> d_ptr;
	};
}
