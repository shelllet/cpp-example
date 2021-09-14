#pragma once
#include <qglobalstatic.h>
#include <llvm/Support/InitLLVM.h>

namespace shelllet {
	namespace common {
		class Format
		{
		public:
			Format();
			virtual ~Format() {  }

			std::string format(const std::string& c);
			void initialize(int argc, char* argv[]);
		private:
			std::unique_ptr<llvm::InitLLVM> llvm_;
		};
		Q_GLOBAL_STATIC(Format, glFormat)
	}
}