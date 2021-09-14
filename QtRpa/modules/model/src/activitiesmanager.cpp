#include "qobject.h"
#include "qdiriterator.h"
#include "qsharedpointer.h"
#include "qglobalstatic.h"
#include "model/activitiesmanager.h"
#include "private/qobject_p.h"
namespace shelllet {
	namespace model {
		class ActivitiesManagerPrivate : public QObjectPrivate {
			Q_DECLARE_PUBLIC(ActivitiesManager)
		public:
			SharedPointer<XmlDocument> doc = std::make_shared<XmlDocument>();
		};

		Q_GLOBAL_STATIC(ActivitiesManager, __activitiesmanager__)
	}
}
shelllet::model::ActivitiesManager::ActivitiesManager(ActivitiesManagerPrivate& d, QObject* parent /*= nullptr*/)
	: QObject(d, parent)
{

	d.doc->appendChild("activities").appendAttribute("display") = tr("activities").toStdString().c_str();

}

void shelllet::model::ActivitiesManager::loadAll()
{
	Q_D(ActivitiesManager);
	Path root = Environment::getInstance()->getActivitiesPath();


	//QDirIterator it(root.toString().toQString(), QStringList() << "*.xml", QDir::Files, QDirIterator::NoIteratorFlags);

	for (auto& p : DirectoryIterator(root))
	{
		XmlDocument doc(root / p.path());
		LOG_DEBUG(PROJECT_NAME) << "doc: \n" << doc;
		d->doc->documentElement().appendCopy(doc.documentElement());
	}
	//while (it.hasNext()) {

	//}

	LOG_DEBUG(PROJECT_NAME) << "activities: " << "\n\t" << *d->doc;
}

SharedPointer<XmlDocument> shelllet::model::ActivitiesManager::document() const
{
	Q_D(const ActivitiesManager);
	return d->doc;
}

shelllet::model::ActivitiesManager* shelllet::model::ActivitiesManager::getInstance()
{
	return __activitiesmanager__;
}

shelllet::model::ActivitiesManager::ActivitiesManager(QObject* parent /*= nullptr*/)
	: ActivitiesManager(*new ActivitiesManagerPrivate, parent)
{

}
