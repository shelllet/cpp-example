#include "property/framework.h"
#include "qlineedit.h"
#include "qvalidator.h"
#include "property/abstracteditorfactorybase.h"
#include "property/abstractpropertymanager.h"
#include "property/stringpropertymanager.h"
#include "property/abstracteditorfactory.h"
#include "property/lineeditfactory.h"
#include "private/qobject_p.h"
#include "property/private/abstracteditorfactorybaseprivate_p.h"
#include "property/private/abstracteditorfactoryprivate_p.h"
#include "property/private/editorfactoryprivate_p.h"
#include "property/private/lineeditfactory_p.h"
namespace shelllet {
	namespace property {

	}
}

using namespace shelllet::property;


void LineEditFactoryPrivate::slotPropertyChanged(PropertySheet* property,
	const String& value)
{
	Q_Q(LineEditFactory);
	const auto it = m_createdEditors.constFind(property);
	if (it == m_createdEditors.constEnd())
		return;

	for (QLineEdit* editor : it.value()) {
		if (editor->text() != *value.toQString())
			editor->setText(*value.toQString());
	}
}


void LineEditFactoryPrivate::slotRegExpChanged(PropertySheet* property,
	const QRegExp& regExp)
{
	Q_Q(LineEditFactory);
	const auto it = m_createdEditors.constFind(property);
	if (it == m_createdEditors.constEnd())
		return;

	StringPropertyManager* manager = q->propertyManager(property);
	if (!manager)
		return;

	for (QLineEdit* editor : it.value()) {
		editor->blockSignals(true);
		const QValidator* oldValidator = editor->validator();
		QValidator* newValidator = 0;
		if (regExp.isValid()) {
			newValidator = new QRegExpValidator(regExp, editor);
		}
		editor->setValidator(newValidator);
		if (oldValidator)
			delete oldValidator;
		editor->blockSignals(false);
	}
}

void LineEditFactoryPrivate::slotSetValue(const QString& value)
{
	Q_Q(LineEditFactory);
	QObject* object = q->sender();
	const QMap<QLineEdit*, PropertySheet*>::ConstIterator ecend = m_editorToProperty.constEnd();
	for (QMap<QLineEdit*, PropertySheet*>::ConstIterator itEditor = m_editorToProperty.constBegin(); itEditor != ecend; ++itEditor)
		if (itEditor.key() == object) {
			PropertySheet* property = itEditor.value();
			StringPropertyManager* manager = q->propertyManager(property);
			if (!manager)
				return;
			manager->setValue(property, String::fromQString(&value));
			return;
		}
}


//LineEditFactory::LineEditFactory(Object* parent /*= nullptr*/)
//    :LineEditFactory(*new LineEditFactoryPrivate, nullptr, parent)
//{

//}
LineEditFactory::LineEditFactory(LineEditFactoryPrivate& d, QObject* parent, Object* /*parent*/ /*= nullptr*/)
	: AbstractEditorFactory<StringPropertyManager>(d, parent)
{

}




LineEditFactory::LineEditFactory(QObject* parent)
	: AbstractEditorFactory<StringPropertyManager>(*new LineEditFactoryPrivate(), parent)
{
}

/*!
	Destroys this factory, and all the widgets it has created.
*/
LineEditFactory::~LineEditFactory()
{
	Q_D(LineEditFactory);
	qDeleteAll(d->m_editorToProperty.keys());
}

/*!
	\internal

	Reimplemented from the AbstractEditorFactory class.
*/
void LineEditFactory::connectPropertyManager(StringPropertyManager* manager)
{
	Q_D(LineEditFactory);
	connect(manager, &StringPropertyManager::valueChanged, this, [d](auto... args) {d->slotPropertyChanged(std::forward<decltype(args)>(args)...); });
	connect(manager, &StringPropertyManager::regExpChanged, this, [d](auto... args) { d->slotRegExpChanged(std::forward<decltype(args)>(args)...); });
}

/*!
	\internal

	Reimplemented from the AbstractEditorFactory class.
*/
QWidget* LineEditFactory::createEditor(StringPropertyManager* manager,
	PropertySheet* property, QWidget* parent)
{
	Q_D(LineEditFactory);
	QLineEdit* editor = d->createEditor(property, parent);
	QRegExp regExp = manager->regExp(property);
	if (regExp.isValid()) {
		QValidator* validator = new QRegExpValidator(regExp, editor);
		editor->setValidator(validator);
	}
	editor->setText(*manager->value(property).toQString());

	connect(editor, &QLineEdit::textEdited, this, [d](auto... args) {
		d->slotSetValue(std::forward<decltype(args)>(args)...); });
	connect(editor, &QLineEdit::destroyed, this, [d](auto... args) {d->slotEditorDestroyed(std::forward<decltype(args)>(args)...); });

	return editor;
}

/*!
	\internal

	Reimplemented from the AbstractEditorFactory class.
*/
void LineEditFactory::disconnectPropertyManager(StringPropertyManager* manager)
{
	manager->disconnect(SIGNAL(valueChanged(PropertySheet*, const String&)));
	manager->disconnect(SIGNAL(regExpChanged(PropertySheet*, const QRegExp&)));
}
