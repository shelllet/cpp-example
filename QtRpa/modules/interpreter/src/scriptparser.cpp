#include <pybind11/embed.h> 
#include "interpreter/scriptparser.h"
#include "interpreter/private/scriptparser_p.h"
#include "qmetaobject.h"
#include "qvariant.h"
namespace shelllet {
	namespace py = pybind11;
	using namespace py::literals;
	namespace interpreter {
		Q_GLOBAL_STATIC(ScriptParser, __scriptparser__)
	}

}
shelllet::interpreter::ScriptParser::ScriptParser()
	:Object(*new ScriptParserPrivate, nullptr)
{
	Q_D(ScriptParser);
	//d->guard = std::make_unique<py::scoped_interpreter >();
}

void shelllet::interpreter::ScriptParser::loadFile(const Path& path)
{
	Q_D(ScriptParser);

	d->code = File::readAllAsText(path);
}

shelllet::common::String shelllet::interpreter::ScriptParser::parseImports() const
{
	Q_D(const ScriptParser);
	std::string result;
	try
	{
		auto locals = py::dict("code"_a = d->code.toStdString());

		py::eval_file(R"(C:\Users\admin\Source\Repos\rpa\assets\scripts\parse.py)", py::globals(), locals);

		//result = locals["result"].cast<std::string>();

	}
	catch (py::error_already_set& eas)
	{
		LOG_WARNING("rap") << eas.what();
	}

	return result;
}

shelllet::common::String shelllet::interpreter::ScriptParser::parseCode(std::int32_t hash)
{
	return "";
}

void shelllet::interpreter::ScriptParser::exec(const Path& path, QObject* obj, const QMetaObject* meta)
{
	Q_D(const ScriptParser);
	std::string result;
	try
	{
		py::dict locals;//= py::dict("filename"_a = "abc");
		for (int i = meta->propertyOffset(); i < meta->propertyCount(); ++i)
		{
			LOG_DEBUG(PROJECT_NAME) << "property name: " << meta->property(i).name()
				<< "\ttypenane: " << meta->property(i).typeName();

			QVariant data = meta->property(i).read(obj);
			switch (data.type())
			{
			case QVariant::String:
				locals[meta->property(i).name()] = data.toString().toStdString();
				break;
			default:
				if (String::isEquals(data.typeName(), QMetaType::typeName(qMetaTypeId<String>()))) {
				locals[meta->property(i).name()] = data.value<String>().toStdString();
				}
			}

		}

		py::eval_file(path.toString().toStdString(), py::globals(), locals);
	}
	catch (py::error_already_set& eas)
	{
		LOG_WARNING("rap") << eas.what();
	}

}

shelllet::interpreter::ScriptParser* shelllet::interpreter::ScriptParser::getInstance()
{
	return __scriptparser__;
}
