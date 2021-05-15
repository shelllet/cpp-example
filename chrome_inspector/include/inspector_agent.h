#pragma once
#include "framework.h"
#include <include/libplatform/libplatform.h>
#include <qthreadpool.h>
#include <qrunnable.h>
#include <qeventloop.h>
#include "resource.h"
#include "inspector_client.h"
QT_FORWARD_DECLARE_CLASS(QEvent)

namespace shelllet {
	namespace engine {
		class InspectorAgent :public QObject, public QRunnable
		{
		public:
			InspectorAgent(QObject* receiver, v8::Platform* platform, const std::string& filename, const std::string& source, const std::string& dir, bool inspect_brk);
			~InspectorAgent();
		public:
			void postInspectorMessage(const QString& message);
			void disconnectInspector();
			void pumpMessageLoop();

			void run() override;
			void cleanup();
			void evaluate();
		private:
			bool loadModules(v8::Local<v8::Context> context);
		private:
			v8::Platform* platform_;
			v8::Isolate* isolate_ = nullptr;
			std::unique_ptr<inspect::InspectorClient> inspector_client_;
			v8::Isolate::CreateParams create_params_;
			std::string name_;
			std::string code_;
			QObject* receiver_;
			std::string dir_;
			bool inspect_brk_;
			//static std::list<std::unique_ptr<Resource, Resource::Deleter>> resources;
		};
	}
}
