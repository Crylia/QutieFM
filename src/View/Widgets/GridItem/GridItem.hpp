#pragma once

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QStyleOption>
#include <QPainter>
#include <QMimeDatabase>
#include <QApplication>
#include <filesystem>

class GridItem : public QWidget {
	Q_OBJECT
private:
	QString m_name;
	QIcon m_icon;
	int m_size;

	std::filesystem::path m_path;

	QSize widgetSize;
	QMimeDatabase mime_database;

	QString formatText(const QString& text);

	QIcon getIconForFileType(const std::filesystem::path path) const;

public:
	GridItem(const std::filesystem::path path, QWidget* parent = nullptr);
	~GridItem( );

	QLabel* m_nameLabel;
	QLabel* m_iconLabel;

	void setIconSize(const QSize& size);

protected:
	void paintEvent(QPaintEvent* event)override;
};
