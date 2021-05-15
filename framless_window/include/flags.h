#pragma once
namespace shelllet {
	namespace frameless {


		enum class WindowType
		{
			None = 1 << 0,
			MinimizeButtonHint = 1 << 1,
			MaximizeButtonHint = 1 << 2,
			MinMaxButtonsHint = MinimizeButtonHint | MaximizeButtonHint,
			CloseButtonHint = 1 << 3,
			AllButton = CloseButtonHint | MinMaxButtonsHint,
			MinCloseButton = MinimizeButtonHint | CloseButtonHint,
			CustomButtonHint = 1 << 4
		};

		//Q_ENUM(WindowType);
		Q_DECLARE_FLAGS(WindowTypeFlags, WindowType)
			Q_DECLARE_OPERATORS_FOR_FLAGS(WindowTypeFlags)


			enum class SizePolicy
		{
			None = 1 << 0,
			FixedWidth = 1 << 1,
			FixedHeigth = 1 << 2,
			FixedAll = FixedWidth | FixedHeigth
		};

		Q_DECLARE_FLAGS(SizePolicyFlags, SizePolicy)
			Q_DECLARE_OPERATORS_FOR_FLAGS(SizePolicyFlags)
	}
}
