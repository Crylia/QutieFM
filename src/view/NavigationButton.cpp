#include "NavigationButton.hpp"

NavigationButton::NavigationButton(const QPixmap& icon, QWidget* parent) :
	QPushButton(parent) {
	setIcon(icon);
	setMouseTracking(true);
}

void NavigationButton::enterEvent(QEnterEvent* event) {
	QPushButton::enterEvent(event);
	setStyleSheet(R"(
		QPushButton{
			background-color: #212121;
			border: 2px solid #F48FB1;
			font-size: 26px;
			font-weight: 900;
			color: #F48FB1;
			border-radius: 8;
		}
	)");
}

void NavigationButton::leaveEvent(QEvent* event) {
	QPushButton::leaveEvent(event);

	setStyleSheet(R"(
		QPushButton{
			background-color: #212121;
			border: 2px solid #414141;
			font-size: 26px;
			font-weight: 900;
			color: #F48FB1;
			border-radius: 8;
		}
	)");
}

void NavigationButton::mousePressEvent(QMouseEvent* event) {
	if (event->button( ) == Qt::LeftButton) {
		emit clicked( );
	}
	QPushButton::mousePressEvent(event);
}

void NavigationButton::setIcon(const QPixmap& icon) {
	QPushButton::setIcon(icon);
}
