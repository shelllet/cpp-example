#include "common.hpp"
#include "property.hpp"
#include "interpreter/composite_property.h"
#include "interpreter/private/composite_property_p.h"
#include "qjsondocument.h"
#include "qjsonobject.h"
#include "qjsonvalue.h"
#include "qmetaobject.h"
#include "interpreter.hpp"
#include "interpreter/scriptparser.h"
namespace shelllet {

}


shelllet::interpreter::CompositeProperty::CompositeProperty(CompositePropertyPrivate& d, const XmlNode& node, QObject* parent /*= nullptr*/)
	: Property(d, node, parent)
{
	/*d.x_ = std::atof(node.attribute("x").value());
	d.y_ = std::atof(node.attribute("y").value());
	d.width_ = std::atof(node.attribute("width").value());
	d.height_ = std::atof(node.attribute("height").value());*/
	//d.dtype_ = static_cast<DiagramType>(node.attribute("type").value().toInt());
	d.category = node.attribute("category").value();
	d.meta = node.attribute("meta").value();
}

shelllet::interpreter::CompositeProperty::CompositeProperty(const XmlNode& node, QObject* parent /*= nullptr*/)
	: CompositeProperty(*new CompositePropertyPrivate, node, parent)

{
}


void shelllet::interpreter::CompositeProperty::restore_from_xml(const std::string& xml)
{
}



shelllet::common::String shelllet::interpreter::CompositeProperty::category() const
{
	Q_D(const CompositeProperty);
	return d->category;
}

int32_t shelllet::interpreter::CompositeProperty::getId() const
{
	Q_D(const CompositeProperty);
	return d->id_;
}

void shelllet::interpreter::CompositeProperty::setId(int32_t id)
{
	Q_D(CompositeProperty);
	d->id_ = id;
}

int32_t shelllet::interpreter::CompositeProperty::getParentId() const
{
	Q_D(const CompositeProperty);
	return d->pid_;
}

void shelllet::interpreter::CompositeProperty::setParentId(int32_t id)
{
	Q_D(CompositeProperty);
	d->pid_ = id;
}



String shelllet::interpreter::CompositeProperty::getImport() const
{
	LOG_DEBUG(PROJECT_NAME) << "# object name: " << metaObject()->className();
	auto path = Environment::getInstance()->getViewPath() / String::toLower(String::removeNamespace(metaObject()->className()));
	path.replaceExtension(Environment::getInstance()->getScriptExtension());
	ScriptParser parser;
	parser.loadFile(path);

	return parser.parseImports();
}

void shelllet::interpreter::CompositeProperty::exec()
{
	/*LOG_DEBUG(PROJECT_NAME) << "# object name: " << metaObject()->className();
	auto path = Environment::getInstance()->getModePath()
		/ category()
		/ String::toLower(String::removeNamespace(metaObject()->className()));
	path.replaceExtension(Environment::getInstance()->getScriptExtension());

	ScriptParser::getInstance()->exec(path, this, metaObject());*/
}

void shelllet::interpreter::CompositeProperty::getDefines(std::ostringstream& oss)
{

}

std::shared_ptr<XmlDocument> shelllet::interpreter::CompositeProperty::getNode()
{
	auto doc = __super::getNode();
	doc->documentElement().appendAttribute("meta") = meta();
	//doc->documentElement().appendAttribute("x") = x();
	//doc->documentElement().appendAttribute("y") = y();
	//doc->documentElement().appendAttribute("width") = width();
	//doc->documentElement().appendAttribute("height") = height();
	//doc->documentElement().appendAttribute("type") = type();
	doc->documentElement().appendAttribute("category") = category();
	doc->documentElement().setName(tagName());
	return doc;
}

std::string shelllet::interpreter::CompositeProperty::json() const
{
	QJsonObject object;
	for (int i = metaObject()->propertyOffset(); i < metaObject()->propertyCount(); ++i) {
		//qDebug() << metaObj->property(i).type() << " " << metaObj->property(i).typeName();
		object.insert(metaObject()->property(i).name(), QJsonValue::fromVariant(metaObject()->property(i).read(this)));
	}

	QJsonDocument document(object);
	return QString(document.toJson(QJsonDocument::Indented)).toStdString();;
}

PropertySheet* shelllet::interpreter::CompositeProperty::getInput(PropertyBrowser*)
{
	Q_D(CompositeProperty);
	GroupPropertyManager* groupManager = new GroupPropertyManager();

	d->m_input = groupManager->addProperty(String::fromQString(&static_cast<const QString&>(QObject::tr("Input"))));

	return d->m_input;
}

PropertySheet* shelllet::interpreter::CompositeProperty::getOutput(PropertyBrowser*)
{
	Q_D(CompositeProperty);
	GroupPropertyManager* groupManager = new GroupPropertyManager();

	d->m_output = groupManager->addProperty(String::fromQString(&static_cast<const QString&>(QObject::tr("Output"))));

	return d->m_output;
}

shelllet::interpreter::DiagramType shelllet::interpreter::CompositeProperty::type()
{
	Q_D(CompositeProperty);
	return d->dtype_;
}

float shelllet::interpreter::CompositeProperty::x() const
{
	Q_D(const CompositeProperty);
	return d->x_;
}

float shelllet::interpreter::CompositeProperty::y() const
{
	Q_D(const CompositeProperty);
	return d->y_;
}

void shelllet::interpreter::CompositeProperty::setX(float x)
{
	Q_D(CompositeProperty);
	d->x_ = x;
}

void shelllet::interpreter::CompositeProperty::setY(float y)
{
	Q_D(CompositeProperty);
	d->y_ = y;
}

float shelllet::interpreter::CompositeProperty::width() const
{
	Q_D(const CompositeProperty);
	return d->width_;
}

float shelllet::interpreter::CompositeProperty::height() const
{
	Q_D(const CompositeProperty);
	return d->height_;
}

shelllet::common::String shelllet::interpreter::CompositeProperty::meta() const
{
	Q_D(const CompositeProperty);
	return d->meta;
}

QPointF shelllet::interpreter::CompositeProperty::pos() const
{
	Q_D(const CompositeProperty);
	return { d->x_, d->y_ };
}

UniquePointer<shelllet::interpreter::CompositeProperty> shelllet::interpreter::CompositeProperty::CreateNode(const XmlNode& node)
{
	//CompositeProperty* child = nullptr;

	//QString n = Prefix() + "::" + node.attribute("meta").value() + "*";

	////LOG_TRACE(__FUNCTION__) << "# record meta: " << n << std::endl;
	//int id = QMetaType::type(n.toUtf8());

	//if (id != QMetaType::UnknownType) {
	//	const auto* meta = QMetaType::metaObjectForType(id);
	//	child = dynamic_cast<properties::CompositeProperty*>(meta->newInstance(Q_ARG(pugi::xml_node, node)));
	//}
	//else {
	//	LOG_WARNING("rpa") << "# meta type is unknown: " << node.name() << "-" << node.attribute("meta").value() << std::endl;
	//}
	//BOOST_ASSERT_MSG(child != nullptr, "create failed.");

	// load prop py
	// exec prop py
	//return PropParser::getInstance()->loadPy(node);
	return nullptr;
	//return std::unique_ptr<shelllet::properties::CompositeProperty>(child);
}

//std::unique_ptr<shelllet::properties::CompositeProperty> shelllet::properties::CompositeProperty::CreateNode(const QString& name)
//{
//	pugi::xml_node node;
//	node.attribute("meta") = name.toUtf8().constData();
//	return CreateNode(node);
//}