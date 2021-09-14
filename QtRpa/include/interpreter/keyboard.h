#pragma once

namespace shelllet {
	namespace interpreter {
		class KeyboardPrivate;
		class Keyboard : public Object {
			Q_DECLARE_PRIVATE(Keyboard)
		public:
			static LPINPUT SendInput(WORD wVk, BOOL u);

			static UINT Release(LPINPUT input);

			static void SendText(const std::wstring& text);

			static SHORT KeyCode(char ch);

			static void Simulate(const std::vector<WORD>& wVks);
			static std::string KeyName(WORD wVk);
			static bool GetAsyncKeyState(std::uint8_t wVk)
			{
				return Invoke<&::GetAsyncKeyState>(wVk) & (1 << 15);
			}
			static void InstallHook( const v8::Local<v8::Function>& fn);
			static BOOL RemoveHook();

		protected:
			Keyboard(KeyboardPrivate&d);
		};
		
	}
}
