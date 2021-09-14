#pragma once
namespace shelllet {
	namespace interpreter {
		class MousePrivate;
		class Mouse : public Object {
			Q_DECLARE_PRIVATE(Mouse)
		public:
			Mouse();
			static void Move(int x, int y);

			static void Click();

			static void RightClick();

			static void MoveAndClick(int x, int y);

			static void InstallHook();
			static BOOL RemoveHook();
		protected:

			Mouse(MousePrivate& d);

		};

	}
}
