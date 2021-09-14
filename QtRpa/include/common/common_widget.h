#pragma once
#include <QRect>
namespace shelllet {
	namespace common {
		namespace widget {
			enum ExitCode {
				ExitWithNormal,
				ExitWithCreate,
				ExitWithOpen,
				ExitWithGit
			};

			class CommonWidget {
			public:
				virtual ExitCode show() = 0;
				virtual void centerToScreen(const QRect& rect) = 0;
			};
		}
	}
}