function propExpression(type, name) {
    let exp1, exp2;
    switch (type) {
        case "bool":
            exp1 = `info.GetReturnValue().Set(p->d_func()->${name}());`;
            exp2 = `p->d_func()->${name}(value->BooleanValue(context).FromJust());`;
            break;
        case "int":
            exp1 = `info.GetReturnValue().Set(p->d_func()->${name}());`;
            exp2 = `p->d_func()->${name}(value->Int32Value(context).FromJust());`;
            break;
        case "uint":
        case "quint16":
            exp1 = `info.GetReturnValue().Set(v8::Uint32::New(isolate, self->d_func()->${name}}()));`
            exp2 = `p->d_func()->${name}(value->Uint32Value(context).FromJust());`;
            break;
        case "QString":
            exp1 = `info.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, self->d_func()->${name}().toUtf8().constData()));`
            exp2 = `p->d_func()->${name}(value->Uint32Value(context).FromJust());`;
            break;
        default:
    }
    return { exp1, exp2 }
}

function wrapArgs(element, name) {
    let argGroup = element.match(/\((.+)\)/);
    let args = "";
    if (argGroup) {
        args = argGroup[1];
    }
    let wrapArgs = [];
    args.split(", ").forEach(element => {
        let types = element.match(/(.+?) /);
        if (!types)
            return;
        let exp1 = "";
        switch (types[1]) {
            case "bool":
                exp1 = `v8::Boolean::New(isolate, ${name})`
                break;
            case "int":
                exp1 = `v8::Int32::New(isolate, ${name});`
                break;
            case "uint":
            case "quint16":
                exp1 = `v8::UInt32::New(isolate, ${name})`
                break;
            case "QString":
                exp1 = `V8_NEW_STRING_VAR(isolate, self->d_func()->${name}().toUtf8().constData())`
                break;
            default:
        }
        wrapArgs.push(exp1);
    });

    return wrapArgs.join(",");
}

function returnExpression(type, name) {
    let exp1;
    switch (type) {
        case "bool":
            exp1 = `args.GetReturnValue().Set(self->d_func()->${name}());`
            break;
        case "int":
            exp1 = `args.GetReturnValue().Set(v8::Int32::New(isolate, self->d_func()->${name}()));`
            break;
        case "uint":
        case "quint16":
            exp1 = `args.GetReturnValue().Set(v8::Uint32::New(isolate, self->d_func()->${name}()));`
            break;
        case "QString":
            exp1 = `args.GetReturnValue().Set(V8_NEW_STRING_VAR(isolate, self->d_func()->${name}()->toUtf8()->constData()));`
            break;
        default:
    }
    return exp1;
}

export function declareFuncs(tpl, text) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let nameGroups = element.match(/(\w+)\(.*?\)/);
        if (nameGroups) {
            results.push(`${tpl}->Set(isolate, "${nameGroups[1]}", v8::FunctionTemplate::New(isolate, ${toUpperCase(nameGroups[1], 0)}));`)
        }
    });

    return results.join("\n");
}

export function implFuncs(text, className) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let nameGroups = element.match(/(\w+)\(.*?\)/);
        if (nameGroups) {
            let types = element.match(/(.+?) /);
            let exp1 = returnExpression(types[1], nameGroups[1]);

            let text = `static void ${toUpperCase(nameGroups[1], 0)}(const v8::FunctionCallbackInfo<v8::Value>& args)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(args)
				{
					auto* self = UnWrap<${className}Wrapper<T, U, C>>(args.This());
					if (!self)
					throw std::domain_error(K_CONST_ERROR_CALLED);
					
					${exp1}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			`;
            results.push(text);
        }
    });

    return results.join("\n");
}

export function declareEnums(className, text) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let enumNames = element.match(/\s+(\w+)\s+\{/); // match name
        let fixedName = "";
        if (!enumNames) {
            return;
        }

        fixedName = toLowerCase(enumNames[1], 0);

        let exp1 = `auto ${fixedName} = v8::FunctionTemplate::New(isolate);`;
        results.push(exp1);
        let values = element.match(/{(.+)}/);
        values.split(",").trim().forEach(element => {
            let exp2 = `${fixedName}->Set(isolate, "${element}", v8::Int32::New(isolate, ${className}::${element}));`;
            results.push(exp2);
        });

        let exp3 = `tpl->Set(isolate, "${enumNames[1]}", ${fixedName});`;

        results.push(exp3);
    });

    return results.join("\n");
}


export function declareProps(text) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let groups = element.split(":");
        if (groups) {
            let name = groups[0].trim();
            let fixedName = toUpperCase(name, 0);
            results.push(`proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "${name}"), Get${fixedName}, Set${fixedName});`)
        }
    });

    return results.join("\n");
}

export function implProps(text, className) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let groups = element.split(":");
        if (groups) {
            let name = groups[0].trim();
            let fixedName = toUpperCase(name, 0);
            let type = groups[1]?.trim();
            let exp = propExpression(type, name);

            let text = `static void Get${fixedName}(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
                    auto* self = UnWrap<${className}Wrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					${exp.exp1}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}

			static void Set${fixedName}(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<${className}Wrapper<T, U, C>>(info.This());
					if (!self)
                        throw std::domain_error(K_CONST_ERROR_CALLED);
                        
					${exp.exp2}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			`;
            results.push(text);
        }
    });

    return results.join("\n");
}

export function declareSignals(text) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let nameGroups = element.match(/(\w+)\(.*?\)/);
        if (nameGroups) {
            let exp1 = `proto->SetAccessor(V8_NEW_STRING_VAR(isolate, "${nameGroups[1]}"), nullptr, ${toUpperCase(nameGroups[1], 0)});`;
            results.push(exp1);
        }
    });

    return results.join("\n");
}

export function implSignals(text, className) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let nameGroups = element.match(/(\w+)\(.*?\)/);
        if (nameGroups) {
            let name = nameGroups[1];
            let fixedName = toUpperCase(nameGroups[1], 0);
            let argGroup = element.match(/\((.+)\)/);
            let args = "";
            if (argGroup) {
                args = argGroup[1];
            }
            let vargs = wrapArgs(element);

            let text = `static void ${fixedName}(v8::Local<v8::String> property, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
			{
				V8_CREATE_LOCAL_CONTEXT_WITHOUT_LOCKER_BY_CALLBACK_INFO(info)
				{
					auto* self = UnWrap<${className}Wrapper<T, U, C>>(info.This());
					if (!self)
						throw std::domain_error(K_CONST_ERROR_CALLED);

					if (value->IsFunction()) {
						std::shared_ptr<v8::Global<v8::Function>>weakPersistent = std::make_shared<v8::Global<v8::Function>>(isolate, v8::Local<v8::Function>::Cast(value));
						QObject::connect(*self, &${className}::${name}, [isolate, weakPersistent](${args}) {
							V8_CREATE_LOCAL_LOCKER_CONTEXT_BY_ISOLATE(isolate)
							{
								v8::TryCatch tryCatch(isolate);
								v8::Local<v8::Value> argv[] = { ${vargs} };
								weakPersistent->Get(isolate)->CallAsFunction(context, context->Global(), std::size(argv), argv);
								if (tryCatch.HasCaught()) {
									throw std::runtime_error(GetException(isolate, tryCatch));
								}
							}
							V8_CREATE_LOCAL_CONTEXT_END
							});
					}
					else if (value->IsNullOrUndefined()) {
						QObject::disconnect(*self, &${className}::${name}, nullptr, nullptr);
					}
				}
				V8_CREATE_LOCAL_CONTEXT_END
			}
			`;
            results.push(text);
        }
    });

    return results.join("\n");
}


export function virtuals(text, parentClassName) {
    let results = [];
    var functions = text.trim().split('\n');
    functions.forEach(element => {
        let nameGroups = element.match(/(\w+)\(.*?\)/);
        if (!nameGroups) {
            return;
        }
        let vargs = wrapArgs(element);
        let name = nameGroups[1];
        let text = `${element}
        {
            if (q_func()->hasOwnProperty(strrchr(__FUNCTION__, ':') + 1)) {
                v8::Local<v8::Value> argv[] = { ${vargs} };
                v8::Local<v8::Value> value = call(__FUNCTION__, std::size(argv), argv);
                return value->BooleanValue(v8::Isolate::GetCurrent());
            }
            if constexpr (std::is_abstract<T>::value)
					throw std::logic_error("The method or operation is not implemented.");
				else {
					return T::${name}();
				}
        }`;

        results.push(text);
    });

    return results.join("\n");
}
