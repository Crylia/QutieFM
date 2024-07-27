#include "GridItem.hpp"

bool isImageFile(const fs::path path) {
	static const std::vector<std::string> imageExtensions = { ".png", ".jpg", ".jpeg", ".bmp", ".gif" };
	return std::find(imageExtensions.begin( ), imageExtensions.end( ), path.extension( ).string( )) != imageExtensions.end( );
}

QIcon getIconForFileType(const fs::path path) {
	if (!fs::is_directory(path)) {
		QIcon icon;
		if (isImageFile(path)) {
			QPixmap pixmap(QString::fromStdString(path.string( )));
			icon = QIcon(pixmap);
		} else {
			auto mdb = make_unique<QMimeDatabase>( );
			QMimeType mime_type = mdb->mimeTypeForFile(QString::fromStdString(path.string( )));
			icon = QIcon::fromTheme(mime_type.iconName( ));
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

QString formatText(const QString& text, const QSize& size) {
	QFontMetrics metrics(text);
	QString elidedText = metrics.elidedText(text, Qt::ElideRight, size.width( ) * 3);

	QStringList lines = elidedText.split(' ');
	QStringList finalText;
	QString currentLine;

	for (const QString& word : lines) {
		QString textLine = currentLine.isEmpty( ) ? word : currentLine + ' ' + word;
		if (metrics.horizontalAdvance(textLine) <= size.width( )) {
			currentLine = textLine;
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

	return finalText.join('\n');
}

GridItem::GridItem(const fs::path path, QWidget* parent) :
	QWidget(parent),
	m_path(path),
	m_name(QString::fromStdString(path.filename( ).string( ))),
	m_icon(getIconForFileType(path)),
	m_size(QSize(128, 128)) {
	setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
	setMinimumSize(m_size);
	setMaximumSize(m_size);
	setObjectName("gridItem");
	setAttribute(Qt::WA_Hover);

	auto vLayout = new QVBoxLayout(this);
	vLayout->setSpacing(10);

	m_iconLabel = new QLabel(this);
	m_iconLabel->setPixmap(m_icon.pixmap(m_size));
	m_iconLabel->setAlignment(Qt::AlignCenter);

	m_nameLabel = new QLabel(formatText(m_name, m_size), this);
	m_nameLabel->setAlignment(Qt::AlignCenter);
	m_nameLabel->setWordWrap(true);

	vLayout->addWidget(m_iconLabel);
	vLayout->addWidget(m_nameLabel);

	setStyleSheet(R"(
		QLabel{
			color: #D8D8D8;
			font - weight: bold;
		}
	)");
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
			background-color: #80DEEA;
			border-radius: 8px;
		}
		QLabel{
			color: #212121;
			font-weight: bold;
		}
	)");

	QWidget::enterEvent(event);
}

void GridItem::leaveEvent(QEvent* event) {
	setStyleSheet(R"(
		#gridItem{
			background-color: none;
			border-radius: 8px;
		}
		QLabel{
			color: #D8D8D8;
			font-weight: bold;
		}
	)");
	QWidget::leaveEvent(event);
}

const fs::path GridItem::getPath( ) const {
	return m_path;
}
