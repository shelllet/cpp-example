#include "common.hpp"
#include "creator.hpp"
#include <QtSql>
#include <libzippp/libzippp.h>
#include <qgraphicswidget.h>
#include "tabitem_page.h"
#include "events/activity_create_event.h"
namespace {
	using namespace shelllet;
	using namespace libzippp;
}
shelllet::creator::TabItemPage::TabItemPage(QWidget* parent /*= nullptr*/)
	: GraphicsView(parent)


{
	events::EventDispatcher::Dispatcher()->push(this);
}

shelllet::creator::TabItemPage::~TabItemPage()
{
}

void shelllet::creator::TabItemPage::create()
{
	/*std::unique_ptr<properties::sequence_properties> item =
		std::make_unique<properties::sequence_properties>(QStringList({ "main function" }), nullptr);
	auto db = QSqlDatabase::database();

	auto tableName = getTabName().remove(".js");
	LOG_TRACE(kMainModuleName) << "# db file" << db.databaseName() << std::endl;
	if (!db.open()) {
		LOG_ERROR(kMainModuleName) << db.lastError().text() << std::endl;
		return;
	}

	db.exec(QString("DROP TABLE IF EXIST %1 ").arg(tableName));
	db.exec(QString("CREATE TABLE %1 (id INTEGER PRIMARY KEY AUTOINCREMENT, name TEXT, meta TEXT, prop TEXT, parent INTEGER)").arg(tableName));

	LOG_TRACE(kMainModuleName) << "# last error: " << db.lastError().text() << std::endl;

	QSqlQuery query;
	query.prepare(QString("INSERT INTO %1 (name, meta, prop, parent) "
		"VALUES (?, ?, ?, ?)").arg(tableName));
	query.bindValue(0, item->getDisplayName());
	query.bindValue(1, item->metaObject()->className() + QString("*"));
	query.bindValue(2, item->toXml());
	query.bindValue(3, 0);
	if (!query.exec()) {
		LOG_ERROR(kMainModuleName) << "# sql error: " << query.lastError().text() << std::endl;
	}*/
}

void shelllet::creator::TabItemPage::load(const Path& filename)
{

	filename_ = filename;

	auto file = Environment::getInstance()->getCurrentProjectPath() / Environment::getInstance()->indexXmlPath();

	XmlDocument doc;
	doc.loadFile(file.toString());
	

	setXml(doc);
	//model_ = std::make_unique<model::SequenceModel>(doc_, this);

	//setModel(model_.get());
}

void shelllet::creator::TabItemPage::save(const Path& filename)
{
	if (filename_.isEmpty()) {
		return;
	}
	File file(Environment::getInstance()->getCurrentProjectPath()/ filename_);


	std::stringstream stream;
	std::unique_ptr< XmlDocument> doc = getXml();
	doc->print(stream);
	std::string xml = stream.str();


	file.write(stream.str());


	/*{
		auto f = filename_;
		f.replace_extension(Environment::getInstance()->getOptions()->script_extension.toUtf8().constData());
		std::ofstream ss(Environment::getInstance()->getOptions()->current_filepath.string() / f);

		QString code = getCode();

		ss << code;
	}*/
}

void shelllet::creator::TabItemPage::add(const std::function<void(const std::string&, int64_t)>& f)
{
	/*ActivitiesWindow::launchAsync([this, f](XmlElement* element)
		{
			try
			{
				SQLite::Statement q(*db, (boost::format("INSERT INTO %1% (name, xml, parent) VALUES (?, ?, ?)") % filename.stem()).str());
				q.bind(1, element->getTagName().toRawUTF8());
				q.bind(2, element->toString().toRawUTF8());
				q.bind(3, parent_id());
				q.exec();
				f(element->getTagName().toRawUTF8(), db->getLastInsertRowid());
			}
			catch (const SQLite::Exception & err)
			{
				LOG_ERROR(kMainModuleName) << "# add element error: " << err.what() << std::endl;
			}
		}, GET_APPLICATION->getMainWindow().getComponent());*/
}

void shelllet::creator::TabItemPage::customEvent(QEvent* event)
{
	if (event->type() == events::ActivityCreateEvent::Type) {
		auto* e = dynamic_cast<events::ActivityCreateEvent*>(event);
		/*QModelIndex index = rootIndex();
		auto* sel = selectionModel();
		if (sel && !sel->selectedRows().isEmpty()) {
			index = sel->selectedRows().first();
		}*/

		//	LOG_DEBUG("rpa") << "# create " << e->meta();

			//int meta = QMetaType::type(e->meta().append("*").c_str());

			//if (meta != QMetaType::UnknownType) {
			//	//
			//	model_->insertRow(0, index, QMetaType::metaObjectForType(meta));
			//}
	}
}

//void shelllet::widgets::TabItemPage::setXml(const std::string& xml)
//{
//}
//
//std::string shelllet::widgets::TabItemPage::getXml() const
//{
//	return "";
//}

std::filesystem::path shelllet::creator::TabItemPage::relative()
{
	//return relative_;
	assert(false);
	return "";
}