#include "common/object.h"

shelllet::common::ObjectData::~ObjectData()
{

}

shelllet::common::ObjectPrivate::~ObjectPrivate()
{

}

shelllet::common::Object::Object(ObjectPrivate& dd, Object* parent /*= nullptr*/)
	: d_ptr(&dd)
{
	Q_D(Object);
	d_ptr->q_ptr = this;
}