#include "PlacesButton.hpp"

PlacesButton::PlacesButton(QString name, QString icon, QWidget* parent) {
	auto layout = new QHBoxLayout(this);

	setObjectName("PlacesButton");

	QSvgRenderer renderer(icon);
	QPixmap pixmap(16, 16);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	renderer.render(&painter);

	m_icon = new QLabel( );
	m_icon->setPixmap(pixmap);
	m_name = new QLabel(name);

	layout->addWidget(m_icon, 0, Qt::AlignLeft);
	layout->addWidget(m_name, 1, Qt::AlignLeft);

	setObjectName("placesbutton");

	setStyleSheet(R"(
		#placesbutton{
			color: #212121;
			background-color: #80DEEA;
			font-size: 14px;
			border-radius: 4px;
		}
	)");
}

void PlacesButton::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style( )->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}

void PlacesButton::mousePressEvent(QMouseEvent* event) {
	if (event->button( ) == Qt::LeftButton) {
		emit clicked( );
	} else if (event->button( ) == Qt::RightButton) {

	}
	QWidget::mousePressEvent(event);
}

void PlacesButton::mouseDoubleClickEvent(QMouseEvent* event) {
	if (event->button( ) == Qt::LeftButton) {
		emit doubleClicked( );
	}

	QWidget::mousePressEvent(event);
}

void PlacesButton::enterEvent(QEnterEvent* event) {
	setStyleSheet(R"(
		#placesbutton{
			color: #212121;
			background-color: #90EEFA;
			font-size: 14px;
			border-radius: 4px;
		}
	)");

	QWidget::enterEvent(event);
}

void PlacesButton::leaveEvent(QEvent* event) {
	setStyleSheet(R"(
		#placesbutton{
			color: #212121;
			background-color: #80DEEA;
			font-size: 14px;
			border-radius: 4px;
		}
	)");
	QWidget::leaveEvent(event);
}
