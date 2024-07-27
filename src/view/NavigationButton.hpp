#pragma once

#include <QPushButton>
#include <QMouseEvent>

class NavigationButton :public QPushButton {
	Q_OBJECT
public:
	/**
	 * @brief Construct a new Navigation Button object
	 *
	 * @param icon
	 * @param parent
	 */
	explicit NavigationButton(const QPixmap& icon, QWidget* parent = nullptr);
	~NavigationButton( ) = default;
	NavigationButton& operator= (const NavigationButton& other) = delete;
	NavigationButton(NavigationButton&& other) = delete;
	NavigationButton& operator= (NavigationButton&& other) noexcept = default;

	/**
	 * @brief Set the Icon object
	 *
	 * @param icon
	 */
	void setIcon(const QPixmap& icon);

protected:
	void enterEvent(QEnterEvent* event) override;
	void leaveEvent(QEvent* event) override;
	void mousePressEvent(QMouseEvent* event) override;

signals:
	void clicked( );
};
