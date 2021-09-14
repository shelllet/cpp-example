#include "frameless/standardbutton.h"
#include "qstyleoption.h"
#include "qsvgrenderer.h"
#include "qpainter.h"
#include "common/private/object_p.h"
#include "qguiapplication.h"
#include "pugixml.hpp"
namespace shelllet {
	namespace frameless {
		static constexpr std::int32_t kNumTypes = 4;
		enum class MouseStatus {
			None,
			Enter,
			Leave,
			Pressed,
			Release
		};

		class StandardButtonPrivate : public ObjectPrivate {
			Q_DECLARE_PUBLIC(StandardButton)
		public:
			MouseStatus status = {};
			Qt::ApplicationState state = {};

			std::array<pugi::xml_document, kNumTypes> xmls;

			ButtonType type = {};
			QByteArray getXmlData(const QColor& c) const {
				std::ostringstream stream;
				auto& doc = xmls[static_cast<int>(type)];
				doc.document_element().first_child().attribute("fill") = c.name().toUtf8().constData();
				doc.save(stream);
				return QByteArray(stream.str().c_str());
			}
			const QColor hoverColor = "#E5E5E5";
			const QColor pressColor = "#CCCCCC";
			const QColor hoverColorForClose = "#E81123";
			const QColor pressColorForClose = "#F1707A";
			void init() {
				Q_Q(StandardButton);
				xmls[static_cast<int>(ButtonType::Close)].load_string(R"(<svg viewBox="0 0 10.2 10.2">
					<polygon fill="#000000" points="10.2,0.7 9.5,0 5.1,4.4 0.7,0 0,0.7 4.4,5.1 0,9.5 0.7,10.2 5.1,5.8 9.5,10.2 10.2,9.5 5.8,5.1" />
				</svg>)");

				xmls[static_cast<int>(ButtonType::Restore)].load_string(R"(<svg viewBox="0 0 10 10">
					<path fill="#000000" d="M2.1,0v2H0v8.1h8.2v-2h2V0H2.1z M7.2,9.2H1.1V3h6.1V9.2z M9.2,7.1h-1V2H3.1V1h6.1V7.1z" />
				</svg>)");

				xmls[static_cast<int>(ButtonType::Maximize)].load_string(R"(<svg viewBox="0 0 10 10">
					<path fill="#000000" d="M0,0v10h10V0H0z M9,9H1V1h8V9z" />
				</svg>)");

				xmls[static_cast<int>(ButtonType::Minimize)].load_string(R"(<svg viewBox="0 0 10.2 1">
					<rect fill="#000000" width="10.2" height="0.5" />
				</svg>)");
			}
		};
	}
}
shelllet::frameless::StandardButton::StandardButton(ButtonType t, QWidget* parent /*= nullptr*/)
	: QSvgWidget(parent)
	, Object(*new StandardButtonPrivate, nullptr)
{
	Q_D(StandardButton);
	d->type = t;
	d->init();
	load(d->getXmlData(Qt::black));
	QObject::connect(qApp, &QGuiApplication::applicationStateChanged, this, &StandardButton::applicationStateChanged);
}

QSize shelllet::frameless::StandardButton::sizeHint() const
{
	return { qRound(geometry().height() * 1.36) ,geometry().height() };
}

void shelllet::frameless::StandardButton::applicationStateChanged(Qt::ApplicationState state)
{
	Q_D(StandardButton);
	d->state = state;
	if (state == Qt::ApplicationActive) {
		load(d->getXmlData(Qt::black));
	}
	else {
		load(d->getXmlData(Qt::darkGray));
	}
	update();
}

void shelllet::frameless::StandardButton::paintEvent(QPaintEvent* event)
{
	Q_D(StandardButton);

	QStyleOption opt;
	opt.initFrom(this);
	QPainter painter(this);

	switch (d->status)
	{
	case MouseStatus::Enter:
		painter.fillRect(rect(), d->type == ButtonType::Close ? d->hoverColorForClose : d->hoverColor);
		break;
	case MouseStatus::Pressed:
		painter.fillRect(rect(), d->type == ButtonType::Close ? d->pressColorForClose : d->pressColor);
		break;
	case MouseStatus::Release:
		painter.fillRect(rect(), palette().window());
		break;
	case MouseStatus::Leave:
		painter.fillRect(rect(), palette().window());
		break;
	default:
		break;
	}
	QRectF rc = QRectF({ .0f, .0f }, renderer()->defaultSize() * .7f);
	rc.moveCenter(rect().center());

	renderer()->render(&painter, rc);
}

void shelllet::frameless::StandardButton::mousePressEvent(QMouseEvent* event)
{
	Q_D(StandardButton);
	d->status = MouseStatus::Pressed;
	update();
}

void shelllet::frameless::StandardButton::enterEvent(QEvent* event)
{
	Q_D(StandardButton);
	d->status = MouseStatus::Enter;
	update();
}

void shelllet::frameless::StandardButton::leaveEvent(QEvent* event)
{
	Q_D(StandardButton);
	d->status = MouseStatus::Leave;
	update();
}

void shelllet::frameless::StandardButton::mouseReleaseEvent(QMouseEvent* event)
{
	Q_D(StandardButton);
	d->status = MouseStatus::Release;
	update();
	if (event->button() == Qt::LeftButton && underMouse())
		emit clicked();
}

