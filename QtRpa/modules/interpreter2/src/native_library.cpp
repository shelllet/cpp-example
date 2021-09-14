#include "common.hpp"
#include "v8.hpp"
#include "interpreter/native_library.h"

#include "libs/core/qobject_implement.h"
//#include "libs/core/randomdevice_implement.h"
//#include "libs/core/uniformintdistribution_implement.h"
#include "libs/core/qcoreapplication_implement.h"
#include "libs/core/qsize_implement.h"
#include "libs/core/qrect_implement.h"
#include "libs/core/qurl_implement.h"
#include "libs/core/qpoint_implement.h"
#include "libs/core/qtimer_implement.h"
#include "libs/core/qdiriterator_implement.h"
#include "libs/core/qdir_implement.h"
#include "libs/core/qfile_implement.h"


namespace shelllet {
	namespace library {

	Q_GLOBAL_STATIC(NativeLibrary, global_native_library)
	
	


	}

	namespace core {
		void initialize(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& global) {
			using namespace shelllet::core;
			{
				//objectTemplate->Set(isolate, RandomDevice::Name(), RandomDevice::WrapClass(isolate));
				//objectTemplate->Set(isolate, UniformIntDistribution::Name(), UniformIntDistribution::WrapClass(isolate));

				global->Set(isolate, Object::Name(), Object::WrapClass(isolate));
				global->Set(isolate, CoreApplication::Name(), CoreApplication::WrapClass(isolate));
				global->Set(isolate, Size::Name(), Size::WrapClass(isolate));
				global->Set(isolate, Rect::Name(), Rect::WrapClass(isolate));
				global->Set(isolate, Url::Name(), Url::WrapClass(isolate));
				global->Set(isolate, Point::Name(), Point::WrapClass(isolate));
				global->Set(isolate, Timer::Name(), Timer::WrapClass(isolate));
				global->Set(isolate, DirIterator::Name(), DirIterator::WrapClass(isolate));
				global->Set(isolate, Dir::Name(), Dir::WrapClass(isolate));
				global->Set(isolate, File::Name(), File::WrapClass(isolate));
			}
		}
	}

}
bool shelllet::library::NativeLibrary::initialize(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& global)
{
	core::initialize(isolate, global);

	return true;
}


shelllet::library::NativeLibrary* shelllet::library::NativeLibrary::getInstance()
{
	return global_native_library;
}

shelllet::library::NativeLibrary::~NativeLibrary()
{
}