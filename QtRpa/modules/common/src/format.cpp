//#include <clang/Basic/Diagnostic.h>
//#include <clang/Basic/DiagnosticOptions.h>
//#include <clang/Basic/FileManager.h>
#include "common.hpp"

#include <clang/Basic/SourceManager.h>
#include <clang/Format/Format.h>
#include <llvm/Support/Error.h>
#include <llvm/Support/Process.h>


/*
ref clang/tools/clang-format/ClangFormat.cpp
*/
namespace shelllet {
	using namespace llvm;
	using namespace clang;
	using namespace clang::format;
	using clang::tooling::Replacements;
}

shelllet::common::Format::Format()
{
}

std::string shelllet::common::Format::format(const std::string& c)
{
	std::unique_ptr<llvm::MemoryBuffer> Code = MemoryBuffer::getMemBuffer(c);
	if (Code->getBufferSize() == 0)
		return c; // Empty files are formatted correctly.
	llvm::StringRef BufStr = Code->getBuffer();

	//const char* InvalidBOM = SrcMgr::ContentCache::getInvalidBOM(BufStr);

	//if (InvalidBOM) {
		//LOG_ERROR(__FUNCTION__) << "error: encoding with unsupported byte order mark \""
		//	<< InvalidBOM << "\" detected.";
	//	return c;
	//}

	std::vector<tooling::Range> Ranges = { tooling::Range(0, Code->getBufferSize()) };

	llvm::Expected<FormatStyle> FormatStyle =
		getStyle("Google", clang::format::getLanguageName(FormatStyle::LK_JavaScript), clang::format::DefaultFallbackStyle);
	if (!FormatStyle) {
		//	LOG_ERROR(kMainModuleName) << llvm::toString(FormatStyle.takeError()) << std::endl;
		return c;
	}
	Replacements Replaces;
	FormattingAttemptStatus Status;

	Replacements cleanupChanges = clang::format::cleanup(*FormatStyle, BufStr, Ranges, clang::format::getLanguageName(FormatStyle::LK_JavaScript));
	Replaces = Replaces.merge(cleanupChanges);

	Ranges = tooling::calculateRangesAfterReplacements(Replaces, Ranges);
	Replacements FormatChanges =
		clang::format::reformat(*FormatStyle, BufStr, Ranges, clang::format::getLanguageName(FormatStyle::LK_JavaScript), &Status);
	Replaces = Replaces.merge(FormatChanges);

	auto ChangedCode = tooling::applyAllReplacements(BufStr, Replaces);
	if (!ChangedCode) {
		//		LOG_ERROR(__FUNCTION__) << llvm::toString(ChangedCode.takeError()) << std::endl;
		return c;
	}

	return *ChangedCode;
}

void shelllet::common::Format::initialize(int argc, char* argv[])
{
	llvm_ = std::make_unique<llvm::InitLLVM>(argc, argv);
}