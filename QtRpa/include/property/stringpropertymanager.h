#pragma once
namespace shelllet {
    namespace property{
        class StringPropertyManagerPrivate;
        class StringPropertyManager : public AbstractPropertyManager {
				Q_OBJECT
            Q_DECLARE_PRIVATE(StringPropertyManager)
        public:
            //StringPropertyManager(Object*parent = nullptr);
			//Q_OBJECT
		public:
			StringPropertyManager(QObject* parent = 0);
			~StringPropertyManager();

			String value(const PropertySheet* property) const;
			QRegExp regExp(const PropertySheet* property) const;

		public slots:
			void setValue(PropertySheet* property, const String& val);

			void setRegExp(PropertySheet* property, const QRegExp& regExp);
		signals:
			void valueChanged(PropertySheet* property, const String& val);
			void regExpChanged(PropertySheet* property, const QRegExp& regExp);
		protected:
			String valueText(const PropertySheet* property) const;
			virtual void initializeProperty(PropertySheet* property);
			virtual void uninitializeProperty(PropertySheet* property);
		private:
		//	QScopedPointer<QtStringPropertyManagerPrivate> d_ptr;
			//Q_DECLARE_PRIVATE(QtStringPropertyManager)
			//	Q_DISABLE_COPY_MOVE(QtStringPropertyManager)
        protected:
            StringPropertyManager(StringPropertyManagerPrivate& d, QObject* parent, Object*);
        };
    }
}
    