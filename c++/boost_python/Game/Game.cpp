// Game.cpp : Defines the entry point for the application.
//

#include "framework.h"
#include "Game.h"
#include <boost/python.hpp>
#include <boost/algorithm/string/join.hpp>
#include <fstream>
#include <vector>
#include <filesystem>
#define MAX_LOADSTRING 100

// Global Variables:

// Forward declarations of functions included in this code module:

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	// TODO: Place code here.
	using namespace boost::python;

	std::vector<std::wstring> ss;

	std::wstring base = _PythonLib;
	if (!IsDebuggerPresent())
	{
		wchar_t szFileName[MAX_PATH] = { 0 };

		GetModuleFileName(NULL, szFileName, MAX_PATH);

		std::filesystem::path p = szFileName;

		base = p.parent_path().wstring();
	}
	{
		//ss.push_back(base.c_str());
		ss.push_back(base + L"\\site-packages");
		ss.push_back(base + L"\\Lib");
		ss.push_back(base + L"\\DLLs");

		Py_SetProgramName(L"Test");
		Py_SetPath((boost::join(ss, ";")).c_str());

		Py_SetPythonHome(base.c_str());
	}
	Py_Initialize();

	std::string config = "config.txt";
	std::ifstream fstream(config);
	std::string filename((std::istreambuf_iterator<char>(fstream)), std::istreambuf_iterator<char>());

	try
	{

		object main_module = import("__main__");

		object main_namespace = main_module.attr("__dict__");

		//object cpp_module((boost::python::handle<>(PyImport_ImportModule("hello_ext"))));


		exec_file(filename.c_str(), main_namespace, object());
	}
	catch (error_already_set const& err)
	{
		if (PyErr_ExceptionMatches(PyExc_ZeroDivisionError))
		{
			// handle ZeroDivisionError specially
		}
		else
		{
			// print all other errors to stderr
			PyObject* exc, * val, * tb;

			PyErr_Fetch(&exc, &val, &tb);
			PyErr_NormalizeException(&exc, &val, &tb);

			boost::python::handle<> hexc(exc), hval(allow_null(val)), htb(allow_null(tb));

			std::string message;

			if (!hval)
			{
				message = extract<std::string>(boost::python::str(hexc));
			}
			else
			{
				object traceback(import("traceback"));
				object format_exception(traceback.attr("format_exception"));
				object formatted_list(format_exception(hexc, hval, htb));
				object formatted(str("").join(formatted_list));
				message = extract<std::string>(formatted);

			}


			if (IsDebuggerPresent())
			{
				::OutputDebugStringA(message.c_str());
				::OutputDebugStringA("\n");
			}
			else {
				std::ofstream out("error.txt", std::ios::trunc);
				out << message;
				out.close();
			}

		}
	}


	return 0;
}

