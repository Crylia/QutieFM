#include "PlacesController.hpp"

PlacesController::PlacesController(PlacesSidebar* placesSidebar, shared_ptr<FileMonitorController> fileMonitorcontroller) :
	m_placesSidebar(placesSidebar),
	m_fileMonitorController(fileMonitorcontroller) {

	const std::vector<std::tuple<std::string, std::string, std::string>> defaultPlaces = {
			{"Home", getenv("HOME"), ":icons/home.svg"},
			{"Desktop", string(getenv("HOME")) + "/Desktop", ":/icons/monitor.svg"},
			{"Bilder", string(getenv("HOME")) + "/Bilder", ":/icons/image.svg"},
			{"Dokumente", string(getenv("HOME")) + "/Dokumente", ":/icons/file-document-outline.svg"},
			{"Downloads", string(getenv("HOME")) + "/Downloads", ":/icons/download.svg"},
			{"Musik", string(getenv("HOME")) + "/Musik", ":/icons/music-note.svg"},
			{"Videos", string(getenv("HOME")) + "/Videos", ":/icons/video-outline.svg"},
			{"Offentlich", string(getenv("HOME")) + "/Öffentlich", ":/icons/folder-account.svg"},
			{"Vorgaben", string(getenv("HOME")) + "/Vorgaben", ":/icons/android-studio.svg"},
			{"Papierkorb", string(getenv("HOME")) + "/.local/share/Trash", ":/icons/delete.svg"}
	};

	for (auto&& place : defaultPlaces) {
		auto p = make_shared<Place>(
			QString::fromStdString(get<0>(place)),
			fs::path(get<1>(place)),
			QString::fromStdString(get<2>(place)),
			PlaceType::MyComputer
		);

		//m_placesList->append(p);

		auto pb = new PlacesButton(
			p->getName( ),
			p->getIconPath( )
		);

		connect(pb, &PlacesButton::clicked, this, [this, p]( ) {
			this->m_fileMonitorController->setPath(p->getPath( ));
			});

		m_placesSidebar->addComputerToList(pb);
	}

}
