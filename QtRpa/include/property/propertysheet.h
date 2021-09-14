#pragma once
namespace shelllet {
	namespace property {
		class AbstractPropertyManager;
		class PropertySheetPrivate;
		class PropertySheet : public Object {
			Q_DECLARE_PRIVATE(PropertySheet)
		public:
			//  PropertySheet(Object*parent = nullptr);

			virtual ~PropertySheet();

			QList<PropertySheet*> subProperties() const;

			AbstractPropertyManager* propertyManager() const;

			QString toolTip() const { return valueToolTip(); } // Compatibility
			QString valueToolTip() const;
			QString descriptionToolTip() const;
			QString statusTip() const;
			QString whatsThis() const;
			QString propertyName() const;
			bool isEnabled() const;
			bool isModified() const;

			bool hasValue() const;
			QIcon valueIcon() const;
			String valueText() const;

			void setToolTip(const QString& text) { setValueToolTip(text); }  // Compatibility
			void setValueToolTip(const QString& text);
			void setDescriptionToolTip(const QString& text);
			void setStatusTip(const QString& text);
			void setWhatsThis(const QString& text);
			void setPropertyName(const QString& text);
			void setEnabled(bool enable);
			void setModified(bool modified);

			void addSubProperty(PropertySheet* property);
			void insertSubProperty(PropertySheet* property, PropertySheet* afterProperty);
			void removeSubProperty(PropertySheet* property);
		protected:
			explicit PropertySheet(AbstractPropertyManager* manager);
			void propertyChanged();
		private:
			friend class AbstractPropertyManager;
			//	QScopedPointer<QtPropertyPrivate> d_ptr;
		protected:
			PropertySheet(PropertySheetPrivate& d, Object* parent = nullptr);
		};
	}
}

W_REGISTER_ARGTYPE(shelllet::property::PropertySheet*)


