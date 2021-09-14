#pragma once
#include "framework.h"
#include "randomdevice_implement.h"
#include "uniformintdistribution_implement.h"
#include "qsize_implement.h"
#include "qrect_implement.h"
#include "qpoint_implement.h"
#include "qobject_implement.h"
#include "qurl_implement.h"
#include "qcoreapplication_implement.h"
#include "qtimer_implement.h"
#include "qpointf_implement.h"
#include "qdiriterator_implement.h"
#include "qdir_implement.h"

namespace shelllet {
	namespace qtcore {
		void initialize(v8::Isolate* isolate, const v8::Local<v8::ObjectTemplate>& proto) {
			using namespace shelllet::core;
			{
				//objectTemplate->Set(isolate, RandomDevice::Name(), RandomDevice::WrapClass(isolate));
				//objectTemplate->Set(isolate, UniformIntDistribution::Name(), UniformIntDistribution::WrapClass(isolate));

				proto->Set(isolate, Object::Name(), Object::WrapClass(isolate));
				proto->Set(isolate, CoreApplication::Name(), CoreApplication::WrapClass(isolate));
				proto->Set(isolate, Point::Name(), Point::WrapClass(isolate));
				proto->Set(isolate, PointF::Name(), PointF::WrapClass(isolate));
				proto->Set(isolate, Size::Name(), Size::WrapClass(isolate));
				proto->Set(isolate, Rect::Name(), Rect::WrapClass(isolate));
				proto->Set(isolate, Url::Name(), Url::WrapClass(isolate));
				proto->Set(isolate, Timer::Name(), Timer::WrapClass(isolate));
				proto->Set(isolate, DirIterator::Name(), DirIterator::WrapClass(isolate));
				proto->Set(isolate, Dir::Name(), Dir::WrapClass(isolate));
			}
		}
	}
}