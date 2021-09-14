#pragma once
#include <include/libplatform/libplatform.h>
#include <qthreadpool.h>
#include <qrunnable.h>
#include <qeventloop.h>
#include "resource.h"
#include "inspector_client.h"
QT_FORWARD_DECLARE_CLASS(QEvent)

namespace shelllet {
	namespace interpreter {
		class InspectorAgent :public QObject, public QRunnable
		{
		public:
			InspectorAgent(QObject* receiver, v8::Platform* platform, const std::filesystem::path& filename, bool inspect_brk);
			~InspectorAgent();
		public:
			void postInspectorMessage(const QString& message);
			void disconnectInspector();
			void pumpMessageLoop();

			void run() override;
			void cleanup();
			void evaluate();
		private:

			static std::string translate(const std::string& xml);
		private:
			v8::Platform* platform_;
			v8::Isolate* isolate_ = nullptr;
			std::unique_ptr<inspect::InspectorClient> inspector_client_;
			v8::Isolate::CreateParams create_params_;
			std::filesystem::path filename_;
			QObject* receiver_;
			bool inspect_brk_;
			std::string index_code_;
			//static std::list<std::unique_ptr<Resource, Resource::Deleter>> resources;
		};
	}
}
