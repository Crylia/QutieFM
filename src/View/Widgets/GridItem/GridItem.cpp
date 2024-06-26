#include "GridItem.hpp"
#include <iostream>

GridItem::GridItem(const std::filesystem::path path, QWidget* parent)
	: QWidget(parent),
	m_path(path),
	m_name(QString::fromStdString(path.filename( ).string( ))),
	m_icon(getIconForFileType(path)) {
	widgetSize = QSize(80, 128);
	setMinimumSize(widgetSize);
	setMaximumSize(widgetSize);

	auto vLayout = new QVBoxLayout(this);
	vLayout->setSpacing(10);

	m_iconLabel = new QLabel(this);
	m_iconLabel->setPixmap(m_icon.pixmap(widgetSize.width( ), widgetSize.height( )));
	m_iconLabel->setAlignment(Qt::AlignCenter);

	m_nameLabel = new QLabel(m_name, this);
	m_nameLabel->setAlignment(Qt::AlignCenter);
	m_nameLabel->setWordWrap(true);

	vLayout->addWidget(m_iconLabel);
	vLayout->addWidget(m_nameLabel);
}

GridItem::~GridItem( ) { }

QString GridItem::formatText(const QString& text) {
	QFontMetrics fm(font( ));
	QString elidedText = fm.elidedText(text, Qt::ElideRight, widgetSize.width( ));
	QString result;
	QStringList lines = elidedText.split('\n');
	for (int i = 0; i < std::min((int)lines.size( ), 3); ++i)
		result.append(lines.at(i)).append('\n');

	if (lines.size( ) > 3)
		result.append("...");

	return result.trimmed( );
}

QIcon GridItem::getIconForFileType(const std::filesystem::path path) const {
	if (!std::filesystem::is_directory(path)) {
		QIcon icon;
		auto mdb = new QMimeDatabase( );
		QMimeType mime_type = mdb->mimeTypeForFile(QString::fromStdString(path.string( )));
		icon = QIcon::fromTheme(mime_type.iconName( ));

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
	}
	QWidget::mousePressEvent(event);
}
