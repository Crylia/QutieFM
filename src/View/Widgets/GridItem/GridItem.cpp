#include "GridItem.hpp"
#include <iostream>

GridItem::GridItem(const std::filesystem::path path, QWidget* parent)
	: QWidget(parent),
	m_path(path),
	m_name(QString::fromStdString(path.filename( ).string( ))),
	m_icon(getIconForFileType(path)) {
	widgetSize = QSize(128, 128);
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setMinimumSize(widgetSize);
	setMaximumSize(widgetSize);

	setObjectName("gridItem");
	setAttribute(Qt::WA_Hover);

	auto vLayout = new QVBoxLayout(this);
	vLayout->setSpacing(10);

	m_iconLabel = new QLabel(this);
	m_iconLabel->setPixmap(m_icon.pixmap(widgetSize.width( ), widgetSize.height( )));
	m_iconLabel->setAlignment(Qt::AlignCenter);

	m_nameLabel = new QLabel(this);
	formatText(m_name);
	m_nameLabel->setAlignment(Qt::AlignCenter);
	m_nameLabel->setWordWrap(true);

	vLayout->addWidget(m_iconLabel);
	vLayout->addWidget(m_nameLabel);
}

GridItem::~GridItem( ) { }

void GridItem::formatText(const QString& text) {
	QFontMetrics metrics(m_nameLabel->font( ));
	QString elidedText = metrics.elidedText(text, Qt::ElideRight, m_nameLabel->width( ) * 3);

	QStringList lines = elidedText.split(' ');
	QStringList finalText;
	QString currentLine;

	for (const QString& word : lines) {
		QString testLine = currentLine.isEmpty( ) ? word : currentLine + ' ' + word;
		if (metrics.horizontalAdvance(testLine) <= m_nameLabel->width( )) {
			currentLine = testLine;
		} else {
			finalText.append(currentLine);
			currentLine = word;
		}

		if (finalText.size( ) == 2 && currentLine.isEmpty( ) == false) {
			currentLine += "...";
			break;
		}
	}

	if (!currentLine.isEmpty( ) && finalText.size( ) < 3) {
		finalText.append(currentLine);
	}

	m_nameLabel->setText(finalText.join('\n'));
}

bool isImageFile(std::filesystem::path path) {
	static const std::vector<std::string> imageExtensions = { ".png", ".jpg", ".jpeg", ".bmp", ".gif" };
	return std::find(imageExtensions.begin( ), imageExtensions.end( ), path.extension( ).string( )) != imageExtensions.end( );
}

QIcon GridItem::getIconForFileType(const std::filesystem::path path) const {
	if (!std::filesystem::is_directory(path)) {
		QIcon icon;
		if (isImageFile(path)) {
			QPixmap pixmap(QString::fromStdString(path.string( )));
			icon = QIcon(pixmap);
		} else {
			auto mdb = new QMimeDatabase( );
			QMimeType mime_type = mdb->mimeTypeForFile(QString::fromStdString(path.string( )));
			icon = QIcon::fromTheme(mime_type.iconName( ));
			delete mdb;
		}

		if (!icon.isNull( )) {
			QPixmap pixmap = icon.pixmap(QSize(64, 64));
			icon = QIcon(pixmap);
		}

		return icon.isNull( ) ? QApplication::style( )->standardIcon(QStyle::SP_FileIcon) : icon;
	} else {

		auto icon = QIcon::fromTheme("folder");

		if (!icon.isNull( )) {
			QPixmap pixmap = icon.pixmap(QSize(64, 64));
			icon = QIcon(pixmap);
		}

		return icon;
	}
}

void GridItem::setIconSize(const QSize& size) {
	widgetSize = size;
}

void GridItem::paintEvent(QPaintEvent* event) {
	QStyleOption opt;
	opt.initFrom(this);
	QPainter p(this);
	style( )->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
	QWidget::paintEvent(event);
}

void GridItem::mousePressEvent(QMouseEvent* event) {
	if (event->button( ) == Qt::LeftButton) {
		emit clicked( );
	} else if (event->button( ) == Qt::RightButton) {

	}
	QWidget::mousePressEvent(event);
}

void GridItem::mouseDoubleClickEvent(QMouseEvent* event) {
	if (event->button( ) == Qt::LeftButton) {
		emit doubleClicked( );
	}

	QWidget::mousePressEvent(event);
}

void GridItem::enterEvent(QEnterEvent* event) {
	setStyleSheet(R"(
		#gridItem{
			border: 2px solid #414141;
			background-color: #00ACC1;
			border-radius: 8px;
		}
	)");
	QWidget::enterEvent(event);
}

void GridItem::leaveEvent(QEvent* event) {
	setStyleSheet(R"(
		#gridItem{
			background-color: none;
			border: 0px solid #414141;
			border-radius: 8px;
		}
	)");
	QWidget::leaveEvent(event);
}
