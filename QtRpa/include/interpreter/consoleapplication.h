#pragma once

namespace shelllet {
	namespace events { class ConsoleEvent; }
	namespace interpreter {
		class ConsoleApplicationPrivate;
		class ConsoleApplication : public Runnable, public Object{
			Q_DECLARE_PRIVATE(ConsoleApplication)
		public:
			ConsoleApplication();
			~ConsoleApplication();
			void initialize();
			void run(QEvent* event) override;

			static String translate(const String& xml);

			static ConsoleApplication* getInstance();
		protected:
			ConsoleApplication(ConsoleApplicationPrivate& d);
		};
	}
}
