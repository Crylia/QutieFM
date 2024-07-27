#include "FileMonitor.hpp"
#include <filesystem>
#include <iostream>
#include <thread>

bool is_hidden(const std::filesystem::path& p) {
#ifdef _WIN32
	DWORD attrs = GetFileAttributes(p.c_str( ));
	if (attrs == INVALID_FILE_ATTRIBUTES) {
		throw std::runtime_error("Error getting file attributes");
	}
	return (attrs & FILE_ATTRIBUTE_HIDDEN);
#elif __unix__
	return p.filename( ).string( ).front( ) == '.';
#endif
	return false;
}

FileMonitor::FileMonitor(std::chrono::duration<int, std::milli> delay)
	: m_delay(delay) { }

FileMonitor::~FileMonitor( ) {
	stop( );
}

FileMonitor::FileMonitor(const FileMonitor& other) :
	m_delay(other.m_delay),
	m_paths(other.m_paths),
	m_running(other.m_running),
	m_path(other.m_path) { }

const FileMonitor& FileMonitor::operator=(const FileMonitor& other) {
	if (this == &other) return *this;

	m_delay = other.m_delay;
	m_paths = other.m_paths;
	m_running = other.m_running;
	m_path = other.m_path;
	return *this;
}

FileMonitor::FileMonitor(FileMonitor&& other) noexcept :
	m_delay(move(other.m_delay)),
	m_paths(move(other.m_paths)),
	m_running(other.m_running),
	m_path(move(other.m_path)) {
	other.m_running = false;
}

const FileMonitor& FileMonitor::operator=(FileMonitor&& other) noexcept {
	if (this == &other) return *this;

	m_delay = move(other.m_delay);
	m_paths = move(other.m_paths);
	m_running = other.m_running;
	m_path = move(other.m_path);
	other.m_running = false;
	return *this;
}

void FileMonitor::SetPath(std::filesystem::path newPath) {
	if (m_path == newPath) return;

	m_path = newPath;
	//stop( );
	emit pathChanged(m_path);
	m_paths.clear( );
	//start( );
}

fs::path FileMonitor::GetPath( ) {
	return m_path;
}

void FileMonitor::start( ) {
	while (m_running) {
		std::this_thread::sleep_for(m_delay);

		auto pbegin = m_paths.begin( );
		while (pbegin != m_paths.end( )) {
			if (!std::filesystem::exists(pbegin->first)) {
				emit update(pbegin->first, FileEvent::erased);
				pbegin = m_paths.erase(pbegin);
			} else
				pbegin++;
		}
		try {
			for (auto& file : std::filesystem::directory_iterator(m_path)) {
				std::filesystem::file_time_type curr_file_last_write;
				if (!file.is_symlink( )) {
					curr_file_last_write = std::filesystem::last_write_time(file);
				} else {
					curr_file_last_write = std::filesystem::file_time_type(std::chrono::nanoseconds(0));
				}


				if (!is_hidden(file)) {
					if (!(m_paths.find(file.path( )) != m_paths.end( ))) {
						m_paths[file.path( )] = curr_file_last_write;
						emit update(file.path( ), FileEvent::created);
					} else {
						if (m_paths[file.path( )] != curr_file_last_write) {
							m_paths[file.path( )] = curr_file_last_write;
							emit update(file.path( ), FileEvent::modified);
						}
					}
				}
			}
		}
		catch (std::filesystem::filesystem_error err) {
			std::cout << err.what( ) << std::endl;
		}
	}
}

void FileMonitor::stop( ) { m_running = false; }
