#pragma once
#include "common.hpp"
namespace shelllet {
    namespace property{
		class PropertyBrowserPrivate;
        class PropertyEditorViewPrivate;
        class PropertyEditorView : public QTreeWidget {
            Q_DECLARE_PRIVATE(PropertyEditorView)
				W_OBJECT(PropertyEditorView)
        public:
            PropertyEditorView(Object*parent = nullptr);

			//Q_OBJECT
		public:
			PropertyEditorView(QWidget* parent = 0);

			void setEditorPrivate(PropertyBrowserPrivate* editorPrivate)
			{
				m_editorPrivate = editorPrivate;
			}

			QTreeWidgetItem* indexToItem(const QModelIndex& index) const
			{
				return itemFromIndex(index);
			}

		protected:
			void keyPressEvent(QKeyEvent* event);
			void mousePressEvent(QMouseEvent* event);
			void drawRow(QPainter* painter, const QStyleOptionViewItem& option, const QModelIndex& index) const;

		private:
			PropertyBrowserPrivate* m_editorPrivate;
        protected:
            PropertyEditorView(PropertyEditorViewPrivate& d, QWidget* parent1 = 0, Object*parent = nullptr);
        };
    }
}
    