#pragma once
namespace shelllet {
	namespace global {
		class MyGlobal {
		public:
			static QString Version();

			static std::string dirname();

			static std::string Chdir(const std::string& tar);

			static bool IEquals(const std::string& s1, const std::string& s2);

			static bool Start(const std::string& file, const std::vector<std::string>& args);

			static void Sleep(int64_t ms);

			static std::filesystem::path GetExePath();
			static std::filesystem::path GetHomePath();

			static std::string Now();
			static void WriteFile(const std::string& filename, const std::string& txt, std::ios_base::openmode mode = std::ios_base::trunc);

			static std::string ToUpperCase(const std::string& string, int index = -1);

			static double ToNumber(const std::vector<std::uint16_t>& v, int type = 0) {
				const int L = sizeof(double) / sizeof(std::uint16_t);
				union Convert
				{
					std::uint16_t u[L];
					double real;
				};
				Convert convert;
				for (int i = 0; i < v.size(); ++i) {
					convert.u[i] = v[i];
				}
				return convert.real;
			}
		};
	}
}