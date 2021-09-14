#pragma once
#include "boost/core/noncopyable.hpp"
#include "qobject.h"
namespace shelllet {
	class MiniDumpPrivate;
	namespace debug {
		class MiniDump: public QObject, public boost::noncopyable {
			Q_DECLARE_PRIVATE(MiniDump)
		public:
			MiniDump(QObject *parent = nullptr);
			~MiniDump();
			bool startCrashServer(const std::wstring& dump_path);
			void stopCrashServer();
		};
	}
}