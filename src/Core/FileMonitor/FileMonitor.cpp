#include "FileMonitor.hpp"
#include <filesystem>
#include <iostream>
#include <thread>

FileMonitor::FileMonitor(std::filesystem::path path,
  std::chrono::duration<int, std::milli> delay)
  : m_path(path), m_delay(delay) { }

void FileMonitor::SetPath(std::filesystem::path newPath) {
  m_path = newPath;
  std::cout << m_path.string( ) << std::endl;
  emit pathChanged(m_path);
  initPathsMap( );
}

void FileMonitor::initPathsMap( ) {
  m_paths.clear( );
  /* for (auto& file : std::filesystem::directory_iterator(m_path)) {
    m_paths[file.path( )] = std::filesystem::last_write_time(file);
  } */
}

bool FileMonitor::is_hidden(const std::filesystem::path& p) {
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

void FileMonitor::start( ) {
  while (m_running) {
    std::this_thread::sleep_for(m_delay);

    auto pbegin = m_paths.begin( );
    while (pbegin != m_paths.end( )) {
      if (!std::filesystem::exists(pbegin->first)) {
        emit changed(pbegin->first, FileEvent::erased);
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
          if (!contains(file.path( ))) {
            m_paths[file.path( )] = curr_file_last_write;
            emit changed(file.path( ), FileEvent::created);
          } else {
            if (m_paths[file.path( )] != curr_file_last_write) {
              m_paths[file.path( )] = curr_file_last_write;
              emit changed(file.path( ), FileEvent::modified);
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

bool FileMonitor::contains(const std::filesystem::path& key) {
  return m_paths.find(key) != m_paths.end( );
}
