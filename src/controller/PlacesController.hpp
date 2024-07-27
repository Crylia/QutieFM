#pragma once

#include <QObject>
#include <QList>
#include <filesystem>
#include <vector>
#include <string>

#include "../model/Place.hpp"
#include "../view/PlacesButton.hpp"
#include "../view/PlacesSidebar.hpp"
#include "../controller/FileMonitorController.hpp"

using namespace std;
namespace fs = filesystem;

class PlacesController :public QObject {
	Q_OBJECT
private:
	QList<shared_ptr<Place>>* m_placesList;
	PlacesSidebar* m_placesSidebar;
	shared_ptr<FileMonitorController> m_fileMonitorController;

public:
	explicit PlacesController(PlacesSidebar* placesSidebar, shared_ptr<FileMonitorController> fileMonitorcontroller);
	~PlacesController( ) = default;
	PlacesController& operator= (const PlacesController& other) = default;
	PlacesController(PlacesController&& other) = delete;
	PlacesController& operator=(PlacesController&& other) noexcept = default;
};
