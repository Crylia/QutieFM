#include "FileMonitorController.hpp"

FileMonitorController::FileMonitorController(
	shared_ptr<FileMonitor> fileMonitor,
	GridView* gridView
) :
	m_FileMonitor(fileMonitor),
	m_GridView(gridView),
	m_previousPaths(make_unique<stack<fs::path>>( )) {

	m_FileMonitor->moveToThread(&m_Thread);

	connect(this, &FileMonitorController::operate,
		m_FileMonitor.get( ), &FileMonitor::start);

	connect(m_FileMonitor.get( ), &FileMonitor::update,
		this, &FileMonitorController::fm_changed);

	connect(m_FileMonitor.get( ), &FileMonitor::pathChanged,
		this, &FileMonitorController::clear_gridLayout);

#ifdef _WIN32
	m_FileMonitor.get( )->SetPath(fs::path(getenv("USERPROFILE")));
#else
	m_FileMonitor.get( )->SetPath(fs::path(getenv("HOME")));
#endif

	m_Thread.start( );

	emit operate( );
}

void FileMonitorController::setPath(const fs::path path) const {
	if (path == m_FileMonitor->GetPath( ))
		return;

	m_previousPaths->push(m_FileMonitor->GetPath( ));
	m_FileMonitor->SetPath(path);
}

const fs::path FileMonitorController::getPath( ) const {
	return m_FileMonitor->GetPath( );
}

void FileMonitorController::fm_changed(const fs::path path, FileEvent event) {
	if (event == FileEvent::created) {
		auto w = new GridItem(path);

		connect(w, &GridItem::doubleClicked, this, [this, path]( ) {
			if (!std::filesystem::is_directory(path))
				return;
			m_FileMonitor->SetPath(path);
			});
		connect(w, &GridItem::clicked, this, [this, path]( ) {
			if (std::filesystem::is_directory(path))
				return;

			std::string cmd = "xdg-open \"" + path.string( ) + "\"";
			std::system(cmd.c_str( ));
			});

		m_GridView->addWidget(w);
	} else if (event == FileEvent::erased) {
		m_GridView->removeWidgetByPath(path);
	} else if (event == FileEvent::modified) {
		// Idk what this would be used for
	}
}

void FileMonitorController::clear_gridLayout(fs::path path) {
	m_GridView->clear( );
}
