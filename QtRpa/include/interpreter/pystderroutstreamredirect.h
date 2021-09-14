#pragma once
#include "common.hpp"
namespace shelllet {
	namespace interpreter {
		class PyStdErrOutStreamRedirectPrivate;
		class PyStdErrOutStreamRedirect : public Object {
			Q_DECLARE_PRIVATE(PyStdErrOutStreamRedirect)
		public:
			PyStdErrOutStreamRedirect();
			virtual ~PyStdErrOutStreamRedirect();

			String stdoutString() const;
			String stderrString()const;

			void initialize();
			void release();

			static PyStdErrOutStreamRedirect* getInstance();

		protected:
			PyStdErrOutStreamRedirect(PyStdErrOutStreamRedirectPrivate& d);
		};
	}
}
