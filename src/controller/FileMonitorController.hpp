#pragma once

#include <QObject>
#include <stack>
#include <QThread>
#include <chrono>

#include "../model/FileMonitor.hpp"
#include "../view/GridView.hpp"

using namespace std;
namespace fs = filesystem;

class FileMonitorController : public QObject {
	Q_OBJECT
public:
	/**
	 * @brief Construct a new File Monitor Controller object, manages the file monitor
	 * thread and updates the gridview when the file monitor updates
	 *
	 * @param fileMonitor
	 * @param gridView
	 */
	explicit FileMonitorController(shared_ptr<FileMonitor> fileMonitor, GridView* gridView);
	~FileMonitorController( ) = default;
	FileMonitorController& operator= (const FileMonitorController& other) = delete;
	FileMonitorController(FileMonitorController&& other) noexcept = default;
	FileMonitorController& operator= (FileMonitorController&& other) noexcept = default;

	/**
	 * @brief Get the Path object
	 *
	 * @return const fs::path
	 */
	const fs::path getPath( ) const;

	/**
	 * @brief Set the Path object and puts the it onto the previousPath stack
	 *
	 * @param path
	 */
	void setPath(const fs::path path) const;

private:
	shared_ptr<FileMonitor> m_FileMonitor;
	GridView* m_GridView;

	unique_ptr<stack<fs::path>> m_previousPaths;

	QThread m_Thread;

private slots:
	/**
	 * @brief Slot executed when the filemonitor sends a changed signal
	 *
	 * @param path
	 */
	void fm_changed(const fs::path path, FileEvent event);

	void clear_gridLayout(fs::path path);

signals:
	void operate( );
};
