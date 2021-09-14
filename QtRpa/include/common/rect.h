#pragma once
#include "framework.h"
#include "object.h"
#include <qrect.h>

namespace shelllet {
	namespace common {
		class RectPrivate : public ObjectPrivate {
		public:
			std::variant<QRect, QRectF> rect;
		};
		template<class T>
		class Rect : public Object {
			Q_DECLARE_PRIVATE(Rect)
		public:
			Rect() : Rect(*new RectPrivate) {

			}
			Rect(const Rect& rect) : Rect(*new RectPrivate) {
				Q_D(Rect);
				d->rect = rect.d_func()->rect;
			}

			Rect(const QRect* rc) : Rect(*new RectPrivate) {
				Q_D(Rect);
				d->rect = { *rc };
			}

			Rect&  operator = (const QRect* rc) {
				Q_D(Rect);
				d->rect = { *rc };
				return *this;
			}
			
			Rect&  operator = (const Rect& rc) {
				Q_D(Rect);
				//d->rect = { *rc };
			}
 			bool isReal() const{
				return (std::is_same<T, float>::value || std::is_same<T, double>::value);
			}
			bool isEmpty() const {
				Q_D(const Rect);
				if (isReal()) {
					return std::get<QRectF>(d->rect).isEmpty();
				}
				else {
					return std::get<QRect>(d->rect).isEmpty();
				}
			}
			bool isValid() const {
				Q_D(const Rect);
				if (isReal()) {
					return std::get<QRectF>(d->rect).isValid();
				}
				else {
					return std::get<QRect>(d->rect).isValid();
				}
			}

			T width() const {
				Q_D(const Rect);
				if (isReal()) {
					return std::get<QRectF>(d->rect).width();
				}
				else {
					return std::get<QRect>(d->rect).width();
				}
			}

			T height() const {
				Q_D(const Rect);
				if (isReal()) {
					return std::get<QRectF>(d->rect).height();
				}
				else {
					return std::get<QRect>(d->rect).height();
				}
			}

			T x() const {
				Q_D(const Rect);
				if (isReal()) {
					return std::get<QRectF>(d->rect).x();
				}
				else {
					return std::get<QRect>(d->rect).x();
				}
			}

			T y() const {
				Q_D(const Rect);
				if (isReal()) {
					return std::get<QRectF>(d->rect).y();
				}
				else {
					return std::get<QRect>(d->rect).y();
				}
			}

		protected:
			Rect(RectPrivate& d) : Object(d, nullptr) {

			}
		};


	}
}
