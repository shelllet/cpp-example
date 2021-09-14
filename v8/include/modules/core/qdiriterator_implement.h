#pragma once
#include "framework.h"
#include <qdiriterator.h>
#include "qdiriterator_p.h"
#include "qdiriterator_wrapper.h"

namespace shelllet {
	namespace core {
		class DirIterator : public QDirIteratorWrapper<QDirIterator, DirIterator, true>
		{
			using ReturnType = QDirIteratorPrivate<QDirIterator, true>;
			using ReturnType2 = QDirIteratorPrivate<QDirIterator, false>;
			ReturnType* Param(const v8::FunctionCallbackInfo<v8::Value>& args) {
				if (args[0]->IsString()) {
					std::string path = ToString({ args.GetIsolate(), args[0] });
					std::filesystem::path fixed = FixRelativePath(path, args.GetIsolate());

					QDir::Filters filters = QDir::NoFilter;
					QDirIterator::IteratorFlags flags = QDirIterator::NoIteratorFlags;
					if (args.Length() > 1) {
						filters = static_cast<QDir::Filters>(args[1]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(filters));
					}
					if (args.Length() > 2) {
						flags = static_cast<QDirIterator::IteratorFlags>(args[2]->Int32Value(args.GetIsolate()->GetCurrentContext()).FromMaybe(flags));
					}

					return new ReturnType(args.GetIsolate(), args.This(), QString::fromStdString(fixed.string()), filters, flags);
				}
				throw std::invalid_argument(K_CONST_ERROR_INVLAID_PARAM);
			}
		public:
			DirIterator(const v8::FunctionCallbackInfo<v8::Value>& args) :QDirIteratorWrapper(*Param(args), args)
			{
			}
			DirIterator(QDirIterator* p, const v8::FunctionCallbackInfo<v8::Value>& args) :QDirIteratorWrapper(*new ReturnType2(args.GetIsolate(), args.This(), p), args)
			{
			}
			DirIterator(v8::Isolate* isolate, const v8::Local<v8::FunctionTemplate>& tpl) : QDirIteratorWrapper(isolate, tpl)
			{
			}

			DirIterator(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) : QDirIteratorWrapper(isolate, proto)
			{
			}

		protected:
			void toString(std::stringstream& ss) const {}
		public:
			static const char* Name() { return "DirIterator"; }
		protected:
		};
	}
}
