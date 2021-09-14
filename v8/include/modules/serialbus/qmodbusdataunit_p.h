#pragma once

namespace shelllet {
	namespace serialbus {
		template<typename T, bool C>
		class QModbusDataUnitPrivate : public ObjectPrivate<T, C>
		{
		public:
			template<typename ...Args>
			QModbusDataUnitPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
			}
		};
	}
}
