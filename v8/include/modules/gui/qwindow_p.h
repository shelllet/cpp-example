#pragma once
#include "qobject_p.h"
#include <boost/type_traits/is_detected.hpp>

namespace shelllet::gui {
	template<typename T, bool C>
	class QWindowPrivate : public core::QObjectPrivate<T, C>
	{
	public:
		template<typename ...Args>
		QWindowPrivate(v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(isolate, obj, std::forward<Args>(args)...) {
		}
		template<typename ... Args>
		QWindowPrivate(T* d, v8::Isolate* isolate, const v8::Local<v8::Object>& obj, Args&&... args) : QObjectPrivate(d, std::forward<Args>(args)...) {
		}
		QObject* focusObject() const override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->focusObject();
			}
			return __super::focusObject();
		}

		void exposeEvent(QExposeEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->exposeEvent(e);
			}
			return __super::exposeEvent(e);
		}

		void resizeEvent(QResizeEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->resizeEvent(e);
			}
			return __super::resizeEvent(e);
		}

		void moveEvent(QMoveEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->moveEvent(e);
			}
			return __super::moveEvent(e);
		}

		void focusInEvent(QFocusEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->focusInEvent(e);
			}
			return __super::focusInEvent(e);
		}

		void focusOutEvent(QFocusEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->focusOutEvent(e);
			}
			return __super::focusOutEvent(e);
		}

		void showEvent(QShowEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->showEvent(e);
			}
			return __super::showEvent(e);
		}

		void hideEvent(QHideEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->hideEvent(e);
			}
			return __super::hideEvent(e);
		}

		void keyPressEvent(QKeyEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->keyPressEvent(e);
			}
			return __super::keyPressEvent(e);
		}

		void keyReleaseEvent(QKeyEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->keyReleaseEvent(e);
			}
			return __super::keyReleaseEvent(e);
		}

		void mousePressEvent(QMouseEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->mousePressEvent(e);
			}
			return __super::mousePressEvent(e);
		}

		void mouseReleaseEvent(QMouseEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->mouseReleaseEvent(e);
			}
			return __super::mouseReleaseEvent(e);
		}

		void mouseDoubleClickEvent(QMouseEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->mouseDoubleClickEvent(e);
			}
			return __super::mouseDoubleClickEvent(e);
		}

		void mouseMoveEvent(QMouseEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->mouseMoveEvent(e);
			}
			return __super::mouseMoveEvent(e);
		}

		void wheelEvent(QWheelEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->wheelEvent(e);
			}
			return __super::wheelEvent(e);
		}

		void touchEvent(QTouchEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->touchEvent(e);
			}
			return __super::touchEvent(e);
		}

		void tabletEvent(QTabletEvent* e) override {
			if (q_func()->hasOwnProperty(__FUNCTION__)) {
				return q_func()->tabletEvent(e);
			}
			return __super::tabletEvent(e);
		}

		
	};
}
