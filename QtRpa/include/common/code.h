#pragma once

namespace shelllet {
	namespace common {
		class code
		{
		public:
			virtual ~code() {  }

			//virtual void startProcess() = 0;

			//virtual void endProcess() = 0;
			virtual	void javascript_code(std::stringstream& stream) = 0;
			virtual void process_start(std::stringstream& stream);
			virtual void process_end(std::stringstream& stream);
		};
	}
}