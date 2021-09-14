#pragma once
#include "framework.h"
#include "object.h"
#include "qpoint.h"

namespace shelllet {
	namespace common {
		using N = QPoint;
		using F = QPointF;

		class PointPrivate : public ObjectPrivate {
		public:
			std::variant<N, F> point;

			auto x();
		};
		template<class T>
		class Point : public Object {
			Q_DECLARE_PRIVATE(Point)
		public:
			Point() : Point(*new PointPrivate) {

			}
			T x() const {
				Q_D(const Point);
				if (isReal()) {
					return std::get<F>(d->point).x();
				}
				else {
					return std::get<N>(d->point).x();
				}
			}
			T y() const {
				Q_D(const Point);
				if (isReal()) {
					return std::get<F>(d->point).y();
				}
				else {
					return std::get<N>(d->point).y();
				}
			}
		protected:
			Point(PointPrivate& d) : Object(d, nullptr) {

			}

		private:
			bool isReal() const {
				return (std::is_same<T, float>::value || std::is_same<T, double>::value);
			}

		};
	}
}
