#pragma once

#include <QWidget>
#include <QLabel>
#include <QLayout>
#include <QStyleOption>
#include <QPainter>
#include <QMimeDatabase>
#include <QApplication>
#include <filesystem>
#include <QMouseEvent>

using namespace std;
namespace fs = filesystem;

class GridItem : public QWidget {
	Q_OBJECT
private:
	QString m_name;
	QIcon m_icon;
	QSize m_size;

	const fs::path m_path;

public:
	/**
	 * @brief Construct a new Grid Item object and automatically find the correct icon.
	 * Will also create a preview for image files
	 *
	 * @param path
	 * @param parent
	 */
	explicit GridItem(const fs::path path, QWidget* parent = nullptr);
	~GridItem( ) = default;
	GridItem& operator=(const GridItem& other) = delete;
	GridItem(GridItem&& other) = delete;
	GridItem& operator=(GridItem&& other) noexcept = default;

	QLabel* m_nameLabel;
	QLabel* m_iconLabel;

	/**
	 * @brief Get the Path object
	 *
	 * @return const fs::path
	 */
	const fs::path getPath( ) const;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;

signals:
	void clicked( );
	void doubleClicked( );
};
