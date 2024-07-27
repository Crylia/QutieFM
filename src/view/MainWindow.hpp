#pragma once

#include <QMainWindow>
#include <QPointer>
#include <QSvgRenderer>
#include <QPainter>
#include <QPushButton>

#include "../model/FileMonitor.hpp"
#include "../controller/FileMonitorController.hpp"
#include "../controller/PlacesController.hpp"
#include "../model/FileMonitor.hpp"
#include "GridItem.hpp"
#include "GridView.hpp"
#include "NavigationButton.hpp"
#include "PlacesSidebar.hpp"

using namespace std;
namespace fs = filesystem;

class MainWindow : public QMainWindow {
	Q_OBJECT
private:
	shared_ptr<FileMonitorController> m_fileMonitorController;
	unique_ptr<PlacesController> m_placesController;
public:
	/**
	 * @brief Construct a new Main Window object
	 *
	 * @param parent
	 */
	explicit MainWindow(QWidget* parent = nullptr);
	~MainWindow( ) = default;
	MainWindow operator= (const MainWindow& other) = delete;
	MainWindow(MainWindow&& other) = delete;
	MainWindow& operator= (MainWindow&& other) noexcept = default;
};
