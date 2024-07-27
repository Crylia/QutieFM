#pragma once

#include <QWidget>
#include <QFrame>

#include "PlacesButton.hpp"

class PlacesSidebar :public QFrame {
	Q_OBJECT
private:
	QList<PlacesButton*> m_computerList;
	QList<PlacesButton*> m_devicesList;

	QVBoxLayout* m_mainLayout;
	QVBoxLayout* m_mycomputerLayout;
	QVBoxLayout* m_devicesLayout;
public:
	/**
	 * @brief Construct a new Places Sidebar object
	 *
	 * @param parent
	 */
	explicit PlacesSidebar(QWidget* parent = nullptr);
	~PlacesSidebar( ) = default;
	PlacesSidebar& operator= (const PlacesSidebar& other) = delete;
	PlacesSidebar(PlacesSidebar&& other) = delete;
	PlacesSidebar& operator= (PlacesSidebar&& other) noexcept = default;

	/**
	 * @brief Get the Computer List object
	 *
	 * @return const QList<Places*>&
	 */
	const QList<PlacesButton*>& getComputerList( ) const;

	/**
	 * @brief Get the Devices List object
	 *
	 * @return const QList<Places*>&
	 */
	const QList<PlacesButton*>& getDevicesList( ) const;

	/**
	 * @brief Add a new place to the computer layout
	 *
	 * @param place
	 */
	const void addComputerToList(PlacesButton* place);

	/**
	 * @brief Add a new place to the device layout
	 *
	 * @param place
	 */
	const void addDeviceToList(PlacesButton* place);

};
