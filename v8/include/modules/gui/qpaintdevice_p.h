#pragma once

namespace shelllet::gui {
	template<typename T, bool C>
	class QPaintDevicePrivate : public ObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		QPaintDevicePrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}

		int metric(QPaintDevice::PaintDeviceMetric metric) const {
			if (hasOwnProperty(strrchr(__FUNCTION__, ':') + 1)) {
				//v8::Local<v8::Value> argv[] = { v8::Int32::New(v8::Isolate::GetCurrent(), metric) }
				v8::Local<v8::Value> v = call(__FUNCTION__, v8::Int32::New(v8::Isolate::GetCurrent(), metric));
				return v->Int32Value(v8::Isolate::GetCurrent()->GetCurrentContext()).FromJust();

			}
			if constexpr (std::is_abstract<T>::value)
				throw std::logic_error("The method or operation is not implemented.");
			else {
				return T::metric(metric);
			}
		}
		QPaintEngine* paintEngine() const {

			if (hasOwnProperty(strrchr(__FUNCTION__, ':') + 1)) {
				//v8::Local<v8::Value> argv[] = { v8::Int32::New(v8::Isolate::GetCurrent(), metric) }
				v8::Local<v8::Value> v = call(__FUNCTION__, v8::External::New(v8::Isolate::GetCurrent(), nullptr));
				return static_cast<QPaintEngine*>(v.As<v8::External>()->Value());

			}
			if constexpr (std::is_abstract<T>::value)
				throw std::logic_error("The method or operation is not implemented.");

			throw std::logic_error("The method or operation is not implemented.");
		}

	};
}
