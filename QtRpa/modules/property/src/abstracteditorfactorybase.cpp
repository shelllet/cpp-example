#include "property/framework.h"
#include "property/abstracteditorfactorybase.h"
#include "private/qobject_p.h"
#include "property/private/abstracteditorfactorybaseprivate_p.h"
namespace shelllet {
	namespace property {

	}
}
using namespace shelllet::property;


AbstractEditorFactoryBase::AbstractEditorFactoryBase(AbstractEditorFactoryBasePrivate& d, QObject* parent)
	:QObject(d, parent)
{

}

