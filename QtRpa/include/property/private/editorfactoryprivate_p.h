#pragma once

namespace shelllet {
	namespace property {


		template <class Editor>
		class EditorFactoryPrivate : public AbstractEditorFactoryPrivate
		{
		public:

			typedef QList<Editor*> EditorList;
			typedef QMap<PropertySheet*, EditorList> PropertyToEditorListMap;
			typedef QMap<Editor*, PropertySheet*> EditorToPropertyMap;

			Editor* createEditor(PropertySheet* property, QWidget* parent);
			void initializeEditor(PropertySheet* property, Editor* e);
			void slotEditorDestroyed(QObject* object);

			PropertyToEditorListMap  m_createdEditors;
			EditorToPropertyMap m_editorToProperty;
		};

		template <class Editor>
		Editor* EditorFactoryPrivate<Editor>::createEditor(PropertySheet* property, QWidget* parent)
		{
			Editor* editor = new Editor(parent);
			initializeEditor(property, editor);
			return editor;
		}

		template <class Editor>
		void EditorFactoryPrivate<Editor>::initializeEditor(PropertySheet* property, Editor* editor)
		{
			typename PropertyToEditorListMap::iterator it = m_createdEditors.find(property);
			if (it == m_createdEditors.end())
				it = m_createdEditors.insert(property, EditorList());
			it.value().append(editor);
			m_editorToProperty.insert(editor, property);
		}

		template <class Editor>
		void EditorFactoryPrivate<Editor>::slotEditorDestroyed(QObject* object)
		{
			const typename EditorToPropertyMap::iterator ecend = m_editorToProperty.end();
			for (typename EditorToPropertyMap::iterator itEditor = m_editorToProperty.begin(); itEditor != ecend; ++itEditor) {
				if (itEditor.key() == object) {
					Editor* editor = itEditor.key();
					PropertySheet* property = itEditor.value();
					const typename PropertyToEditorListMap::iterator pit = m_createdEditors.find(property);
					if (pit != m_createdEditors.end()) {
						pit.value().removeAll(editor);
						if (pit.value().empty())
							m_createdEditors.erase(pit);
					}
					m_editorToProperty.erase(itEditor);
					return;
				}
			}
		}


	}
}