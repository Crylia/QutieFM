#pragma once

#include <QObject>
#include <chrono>
#include <filesystem>
#include <unordered_map>

#ifdef _WIN32
#include <windows.h>
#elif __unix__
#include <sys/stat.h>
#endif

using namespace std;
namespace fs = filesystem;

enum class FileEvent { created, modified, erased };

class FileMonitor : public QObject {
	Q_OBJECT
public:
	/**
	 * @brief Construct a new File Monitor object and automatically created the
	 * file monitor thread then starts it
	 *
	 * @param delay Delay in milliseconds for the update interval on the file monitor
	 */
	explicit FileMonitor(chrono::duration<int, milli> delay);
	~FileMonitor( );
	FileMonitor(const FileMonitor& other);
	const FileMonitor& operator=(const FileMonitor& other);
	FileMonitor(FileMonitor&& other) noexcept;
	const FileMonitor& operator=(FileMonitor&& other) noexcept;

	/**
	 * @brief Set the Path object
	 *
	 * @param path
	 */
	void SetPath(fs::path path);

	/**
	 * @brief Get the Path object
	 *
	 * @return fs::path
	 */
	fs::path GetPath( );

public slots:
	/**
	 * @brief Start slot for the main thread, no idea why it doesnt work as a regular function
	 * but it works.
	 *
	 */
	void start( );

	/**
	 * @brief Stop function for the worker thread
	 *
	 */
	void stop( );

private:
	chrono::duration<int, milli> m_delay;

	unordered_map<fs::path, fs::file_time_type>	m_paths;
	bool m_running = true;
	fs::path m_path;

signals:
	/**
	 * @brief Fires when a file is deleted or created, created also means
	 * if its found when the paths map is created for the first time
	 *
	 * @param path path of the created/deleted path
	 * @param fe Event indicating if its deleted or created
	 */
	void update(const fs::path path, const FileEvent fe);

	/**
	 * @brief Signal fired when the path is changed and the paths map is cleared
	 * This is so that the view gets cleared before new paths come in
	 *
	 */
	void pathChanged(fs::path path);
};
