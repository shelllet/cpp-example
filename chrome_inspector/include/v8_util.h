#include <boost/format.hpp>
#include <QString>
#include <v8.h>
namespace shelllet {
	static inline bool V8_IsBoolean(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsBoolean();
	}
	static inline bool V8_IsString(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsString();
	}
	static inline bool V8_IsUint8Array(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsUint8Array();
	}
	static inline bool V8_IsNumber(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsNumber();
	}
	static inline bool V8_IsUint32(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsUint32();
	}
	static inline bool V8_IsInt32(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsInt32();
	}
	static inline bool V8_IsBigInt(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsBigInt();
	}
	static inline bool V8_IsObject(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsObject();
	}
	static inline bool V8_IsSymbol(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsSymbol();
	}
	static inline bool V8_IsExternal(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsExternal();
	}
	static inline bool V8_IsFunction(const v8::FunctionCallbackInfo<v8::Value>& args, int index) {
		return args.Length() > index && args[index]->IsFunction();
	}

	template<typename T>
	static inline T V8_To_Ptr(const v8::Local<v8::Value>& value) {
		v8::Local<v8::External> external = v8::Local<v8::External>::Cast(value);
		return static_cast<T>(external->Value());
	}

	namespace convert {
		class String : public v8::String {
		public:
			static v8::Local<v8::String> New(v8::Isolate* isolate, const QString& data) {
				return v8::String::NewFromUtf8(isolate, data.toUtf8().constData()).ToLocalChecked();
			}
			static v8::Local<v8::String> New(v8::Isolate* isolate, const char* data) {
				return v8::String::NewFromUtf8(isolate, data).ToLocalChecked();
			}
			static v8::Local<v8::String> New(v8::Isolate* isolate, const std::string& data) {
				return v8::String::NewFromUtf8(isolate, data.c_str()).ToLocalChecked();
			}
			static inline QString To(v8::Isolate* isolate, const v8::Local<v8::Value>& value) {
				v8::String::Utf8Value s = { isolate, value };
				if (*s) {
					return *s;
				}
				return QString();
			}
		};

		class Object : public v8::Object {
		public:
			template<typename T>
			static inline T* UnWrap(const v8::Local<v8::Object>& obj, int index = 0) {
				if (obj->InternalFieldCount() > index)
					return dynamic_cast<T*>(static_cast<empty*>(obj->GetAlignedPointerFromInternalField(index)));
				return nullptr;
			}
			static inline v8::Local<v8::Value> Wrap(v8::Isolate* isolate, v8::Local<v8::Context> context, const char* name, int argc, v8::Local<v8::Value> argv[])
			{
				v8::EscapableHandleScope scope(isolate);
				v8::Local<v8::Value> f = context->Global()->Get(context, convert::String::New(isolate, name)).ToLocalChecked();
				if (f->IsFunction()) {
					v8::Local<v8::Function> ctor = f.As<v8::Function>();
					auto r = ctor->CallAsConstructor(context, argc, argv);
					if (!r.IsEmpty())
						return scope.Escape(r.ToLocalChecked());
				}
				throw std::runtime_error((boost::format("!`%1%` not registered.") % name).str());
			}
		};
		class External : public v8::External {
		public:
			template<typename T>
			static inline T Value(const v8::Local<v8::Value>& value) {
				v8::Local<v8::External> external = v8::Local<v8::External>::Cast(value);
				return static_cast<T>(external->Value());
			}
		};
		class Array : public v8::Array {
		public:
			static inline v8::Local<v8::Array> New(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const QStringList& c) {
				v8::EscapableHandleScope scope(isolate);
				v8::Local<v8::Array> array = v8::Array::New(isolate, c.size());
				for (int i = 0; i < c.size(); i++) {
					array->Set(context, i, convert::String::New(isolate, c[i]));
				}
				return scope.Escape(array);
			}
			static inline void To(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const v8::Local<v8::Value>& value, QStringList& list) {
				v8::Local<v8::Array> array = v8::Local<v8::Array>::Cast(value);
				if (!array.IsEmpty()) {
					for (std::uint32_t i = 0; i < array->Length(); ++i) {
						list.push_back(convert::String::To(isolate, array->Get(context, i).ToLocalChecked()));
					}
				}
			}
		};
		class Uint8Array : public v8::Uint8Array {
		public:
			static inline v8::Local<v8::Uint8Array> New(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const QByteArray& bytes) {
				v8::Local<v8::ArrayBuffer> buffer = v8::ArrayBuffer::New(isolate, bytes.size());
				std::memcpy(buffer->GetContents().Data(), bytes.constData(), bytes.size());
				return v8::Uint8Array::New(buffer, 0, buffer->ByteLength());
			}

			static inline void To(const v8::Local<v8::Value>& value, QByteArray& buffer) {
				v8::Local<v8::Uint8Array> array = v8::Local<v8::Uint8Array>::Cast(value);
				if (!array.IsEmpty()) {
					buffer.resize(array->Length());
					array->CopyContents(buffer.data(), array->Length());
				}
			}
		};
		class Int32Array : public v8::Int32Array {
		public:
			template<typename T>
			static inline v8::Local<v8::Int32Array> New(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const T& c) {
				v8::Local<v8::ArrayBuffer> ar = v8::ArrayBuffer::New(isolate, c.size());
				for (int i = 0; i < c.size(); i++) {
					ar->Set(context, i, v8::Int32::New(isolate, c[i]));
				}

				return v8::Int32Array::New(ar, 0, ar->ByteLength());
			}

			static inline void ToVector(const v8::Local<v8::Value>& value, QVector<std::int32_t>& buffer) {
				v8::Local<v8::Int32Array> ar = v8::Local<v8::Int32Array>::Cast(value);
				if (!ar.IsEmpty()) {
					buffer.resize(ar->Length());
					ar->CopyContents(buffer.data(), ar->ByteLength());
				}
			}
			static inline QVector<std::int32_t> ToVector(const v8::Local<v8::Value>& value) {
				v8::Local<v8::Int32Array> ar = v8::Local<v8::Int32Array>::Cast(value);
				QVector<std::int32_t> buffer;
				if (!ar.IsEmpty()) {
					buffer.resize(ar->Length());
					ar->CopyContents(buffer.data(), ar->ByteLength());
				}
				return buffer;
			}
		};
	}
	template<typename T>
	static inline v8::Local<v8::Int32Array> V8_From_Int32Array(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const T& c) {
		v8::Local<v8::ArrayBuffer> ar = v8::ArrayBuffer::New(isolate, c.size());
		for (int i = 0; i < c.size(); i++) {
			ar->Set(context, i, v8::Int32::New(isolate, c[i]));
		}

		return v8::Int32Array::New(ar, 0, ar->ByteLength());
	}
	template<typename T>
	static inline v8::Local<v8::Array> V8_From_ObjectArray(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const char* name, const T& c) {
		v8::Local<v8::Array> ar = v8::Array::New(isolate, c.size());
		for (int i = 0; i < c.size(); i++) {
			v8::Local<v8::Value> argv[] = { v8::External::New(isolate, (void*)&c[i]) };
			ar->Set(context, i, convert::Object::Wrap(isolate, context, name, std::size(argv), argv));
		}
		return ar;
	}

	static inline v8::Local<v8::Value> Call(v8::Isolate* isolate, const v8::Local<v8::Context>& context, const char* name, const char* object, int argc, v8::Local<v8::Value> argv[]) {
		if (object == nullptr) {
			auto v = context->Global()->Get(context, convert::String::New(isolate, name)).ToLocalChecked();
			auto f = v8::Local<v8::Function>::Cast(v);
			return f->CallAsFunction(context, context->Global(), argc, argv).ToLocalChecked();
		}
		auto m = context->Global()->Get(context, convert::String::New(isolate, object)).ToLocalChecked();
		auto o = m->ToObject(context).ToLocalChecked();
		auto v = o->Get(context, convert::String::New(isolate, name)).ToLocalChecked();
		auto f = v8::Local<v8::Function>::Cast(v);
		return f->CallAsFunction(context, o, argc, argv).ToLocalChecked();
	}
}
