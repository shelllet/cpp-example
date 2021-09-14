#pragma once

namespace shelllet {
    namespace property{
        class PropertyEditorDelegatePrivate;
        class PropertyEditorDelegate : public QItemDelegate {
            Q_DECLARE_PRIVATE(PropertyEditorDelegate)
				W_OBJECT(PropertyEditorDelegate)
        public:
            PropertyEditorDelegate(Object*parent = nullptr);

			//Q_OBJECT

		public:
			PropertyEditorDelegate(QObject* parent = 0);

			void setEditorPrivate(PropertyBrowserPrivate* editorPrivate)
			{
				m_editorPrivate = editorPrivate;
			}

			QWidget* createEditor(QWidget* parent, const QStyleOptionViewItem& option,
				const QModelIndex& index) const;

			void updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option,
				const QModelIndex& index) const;

			void paint(QPainter* painter, const QStyleOptionViewItem& option,
				const QModelIndex& index) const;

			QSize sizeHint(const QStyleOptionViewItem& option, const QModelIndex& index) const;

			void setModelData(QWidget*, QAbstractItemModel*,
				const QModelIndex&) const {}

			void setEditorData(QWidget*, const QModelIndex&) const {}

			bool eventFilter(QObject* object, QEvent* event);
			void closeEditor(PropertySheet* property);

			QTreeWidgetItem* editedItem() const { return m_editedItem; }

		private slots:
			void slotEditorDestroyed(QObject* object);

		private:
			int indentation(const QModelIndex& index) const;

			typedef QMap<QWidget*, PropertySheet*> EditorToPropertyMap;
			mutable EditorToPropertyMap m_editorToProperty;

			typedef QMap<PropertySheet*, QWidget*> PropertyToEditorMap;
			mutable PropertyToEditorMap m_propertyToEditor;
			PropertyBrowserPrivate* m_editorPrivate;
			mutable QTreeWidgetItem* m_editedItem;
			mutable QWidget* m_editedWidget;
        protected:
            PropertyEditorDelegate(PropertyEditorDelegatePrivate& d, QObject* parent1 = 0, Object*parent = nullptr);
        };
    }
}
    