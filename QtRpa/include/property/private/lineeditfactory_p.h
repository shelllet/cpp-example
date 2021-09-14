#pragma once
namespace shelllet {
    namespace property{
        class LineEditFactoryPrivate : public EditorFactoryPrivate<QLineEdit> {
            Q_DECLARE_PUBLIC(LineEditFactory)
        public:

			void slotPropertyChanged(PropertySheet* property, const String& value);
			void slotRegExpChanged(PropertySheet* property, const QRegExp& regExp);
			void slotSetValue(const QString& value);
        };
    }
}
