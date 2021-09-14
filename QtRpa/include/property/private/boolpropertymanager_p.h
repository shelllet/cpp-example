#pragma once
namespace shelllet {
    namespace property{
        class BoolPropertyManagerPrivate : public AbstractPropertyManagerPrivate {
            Q_DECLARE_PUBLIC(BoolPropertyManager)
     
		public:
			QtBoolPropertyManagerPrivate();

			QMap<const PropertySheet*, bool> m_values;
			const QIcon m_checkedIcon;
			const QIcon m_uncheckedIcon;
        };
    }
}
