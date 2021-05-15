#include "framework.h"
#include <boost/algorithm/string.hpp>
#include <qprocess.h>
#include <qstandardpaths.h>
#include <qdatetime.h>
#include <qcoreapplication.h>
#include "native/global.h"

QString shelllet::global::MyGlobal::Version()
{
	return VERSION;
}

std::string shelllet::global::MyGlobal::dirname()
{
	return std::filesystem::current_path().string();
}

std::string shelllet::global::MyGlobal::Chdir(const std::string& tar)
{
	std::filesystem::path target = { tar };
	std::filesystem::path dir = std::filesystem::current_path().string();

	if (!target.empty() && std::filesystem::exists(target)) {
		std::filesystem::current_path(target);
	}
	return dir.string();
}

bool shelllet::global::MyGlobal::IEquals(const std::string& s1, const std::string& s2)
{
	return std::equal(s1.begin(), s1.end(), s2.begin(), s2.end(), [](char ch1, char ch2) {
		return tolower(ch1) == tolower(ch2);
		});
}

bool shelllet::global::MyGlobal::Start(const std::string& file, const std::vector<std::string>& args)
{
	const char* quoted = R"(")";
	QString fixed = QString::fromStdString(file);
	if (fixed.contains(" ")) {
		if (!fixed.startsWith(quoted)) {
			fixed = quoted + fixed;
		}

		if (!fixed.endsWith(quoted)) {
			fixed = fixed + quoted;
		}
	}

	if (args.empty()) {
		return QProcess::startDetached(fixed);
	}
	QVector<QString> arguments(args.size());
	std::for_each(args.begin(), args.end(), [&arguments](const std::string& arg) {
		arguments.push_back(QString::fromStdString(arg));
		});
	return QProcess::startDetached(fixed, QStringList::fromVector(arguments));
}

void shelllet::global::MyGlobal::Sleep(int64_t ms)
{
	std::this_thread::sleep_for(std::chrono::milliseconds(ms));
}

std::filesystem::path shelllet::global::MyGlobal::GetExePath()
{
	return QCoreApplication::applicationDirPath().toStdString();
}

std::filesystem::path shelllet::global::MyGlobal::GetHomePath()
{
	return QStandardPaths::writableLocation(QStandardPaths::HomeLocation).toStdString();
}

std::string shelllet::global::MyGlobal::Now()
{
	std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
	std::vector<char> buf(0xff, '\0');
	if (size_t size = std::strftime(buf.data(), buf.size(), "%F %T", std::localtime(&t))) {
		return std::string(buf.begin(), buf.begin() + size);
	}
	return QDateTime::currentDateTime().toString().toStdString();
}

void shelllet::global::MyGlobal::WriteFile(const std::string& filename, const std::string& txt, std::ios_base::openmode mode /*= std::ios_base::trunc*/)
{
	std::ofstream file(filename, std::ofstream::out | mode);
	if (file.is_open()) {
		file << txt;
	}
}

std::string shelllet::global::MyGlobal::ToUpperCase(const std::string& string, int index /*= -1*/)
{
	std::string result = string;
	if (index == -1) {
		result = boost::to_upper_copy<std::string>(string);
	}
	else if (index < string.length() && index >= 0) {
		result[index] = std::toupper(result[index]);
	}
	return result;
}