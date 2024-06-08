#include "FileMonitor.hpp"
#include <filesystem>
#include <thread>
#include <iostream>

FileMonitor::FileMonitor(std::filesystem::path path,
  std::chrono::duration<int, std::milli> delay)
  : m_path(path), m_delay(delay) {

  for (auto& file :
    std::filesystem::directory_iterator(m_path)) {
    m_paths[file.path( )] = std::filesystem::last_write_time(file);
    std::cout << file.path( ).string( ) << std::endl;
  }

  emit newPathEntered(m_paths);
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

    for (auto& file :
      std::filesystem::directory_iterator(m_path)) {
      auto curr_file_last_write = std::filesystem::last_write_time(file);

      if (!contains(file.path( ))) {
        m_paths[file.path( )] =
          curr_file_last_write;
        emit update(file.path( ), FileEvent::created);
      } else {
        if (m_paths[file.path( )] !=
          curr_file_last_write) {
          m_paths[file.path( )] =
            curr_file_last_write;
          emit update(file.path( ), FileEvent::modified);
        }
      }
    }
  }
}

void FileMonitor::stop( ) { m_running = false; }

bool FileMonitor::contains(const std::filesystem::path& key) {
  return m_paths.find(key) != m_paths.end( );
}
