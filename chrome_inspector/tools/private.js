
export function create(data, filename){
    var code = `#pragma once
namespace shelllet {
	namespace ${data.namespace} {
		template<typename T, bool M>
		class ${data.className}Private : public ${data.parent}Private<T, M>
		{
		public:
			template<typename ...Args>
			${data.className}Private(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : ${data.parent}Private(isolate, obj, std::forward<Args>(args)...) {
			}

		};
	}
}
`;
    writeFile(filename, code);

}
