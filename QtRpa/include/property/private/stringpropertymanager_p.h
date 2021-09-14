#pragma once
namespace shelllet {
    namespace property{
        class StringPropertyManagerPrivate : public AbstractPropertyManagerPrivate {
            Q_DECLARE_PUBLIC(StringPropertyManager)
		public:

			struct Data
			{
				Data() : regExp(QString(QLatin1Char('*')), Qt::CaseSensitive, QRegExp::Wildcard)
				{
				}
				String val;
				QRegExp regExp;
			};

			typedef QMap<const PropertySheet*, Data> PropertyValueMap;
			QMap<const PropertySheet*, Data> m_values;
        };
    }
}
