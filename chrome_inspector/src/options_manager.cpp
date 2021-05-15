#include "framework.h"
#include "options_manager.h"
#include "native/global_implement.h"

shelllet::options::options_manager::options_manager()
{
	options.modules_path = std::filesystem::current_path() / "modules";
	options.extension = ".dll";
}

void shelllet::options::options_manager::set_modules_path(const QString& path)
{
	options.modules_path = path.toStdString();
}