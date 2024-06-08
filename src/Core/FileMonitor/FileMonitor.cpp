#include "FileMonitor.hpp"
#include <filesystem>
#include <thread>

FileMonitor::FileMonitor(QString path,
  std::chrono::duration<int, std::milli> delay)
  : m_path(path), m_delay(delay) {

  for (auto& file :
    std::filesystem::directory_iterator(m_path.toStdString( ))) {
    m_paths[QString::fromStdString(file.path( ).string( ))] =
      std::filesystem::last_write_time(file);
  }
}

void FileMonitor::start( ) {
  while (m_running) {
    std::this_thread::sleep_for(m_delay);

    auto pbegin = m_paths.begin( );
    while (pbegin != m_paths.end( )) {
      if (!std::filesystem::exists(pbegin->first.toStdString( ))) {
        emit update(pbegin->first, FileEvent::erased);
        pbegin = m_paths.erase(pbegin);
      } else
        pbegin++;
    }

    for (auto& file :
      std::filesystem::directory_iterator(m_path.toStdString( ))) {
      auto curr_file_last_write = std::filesystem::last_write_time(file);

      if (!contains(QString::fromStdString(file.path( ).string( )))) {
        m_paths[QString::fromStdString(file.path( ).string( ))] =
          curr_file_last_write;
        emit update(QString::fromStdString(file.path( ).string( )),
          FileEvent::created);
      } else {
        if (m_paths[QString::fromStdString(file.path( ).string( ))] !=
          curr_file_last_write) {
          m_paths[QString::fromStdString(file.path( ).string( ))] =
            curr_file_last_write;
          emit update(QString::fromStdString(file.path( ).string( )),
            FileEvent::modified);
        }
      }
    }
  }
}

void FileMonitor::stop( ) { m_running = false; }

bool FileMonitor::contains(const QString& key) {
  return m_paths.find(key) != m_paths.end( );
}
