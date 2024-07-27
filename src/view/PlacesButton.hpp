#pragma once

#include <QPushButton>
#include <QWidget>
#include <filesystem>
#include <QHBoxLayout>
#include <QLabel>
#include <QStyleOption>
#include <QPainter>
#include <QMouseEvent>
#include <QEvent>
#include <QSvgRenderer>

using namespace std;
namespace fs = filesystem;

class PlacesButton : public QWidget {
	Q_OBJECT
private:
	QLabel* m_name;
	QLabel* m_icon;

public:
	/**
	 * @brief Construct a new Places object
	 *
	 * @param name
	 * @param path
	 * @param icon
	 * @param parent
	 */
	explicit PlacesButton(QString name, QString icon, QWidget* parent = nullptr);
	~PlacesButton( ) = default;
	PlacesButton& operator= (const PlacesButton& other) = default;
	PlacesButton(PlacesButton&& other) = delete;
	PlacesButton& operator= (PlacesButton&& other) noexcept = default;

protected:
	void paintEvent(QPaintEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent*) override;
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;

signals:
	void clicked( );
	void doubleClicked( );
};
