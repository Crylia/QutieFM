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

enum class FileEvent { created, modified, erased };

class FileMonitor : public QObject {
  Q_OBJECT
public:
  std::chrono::duration<int, std::milli> m_delay;

  FileMonitor(std::filesystem::path path,
    std::chrono::duration<int, std::milli> delay);
  ~FileMonitor( ) = default;

  void SetPath(std::filesystem::path path);

public slots:
  void start( );
  void stop( );

private:
  std::unordered_map<std::filesystem::path, std::filesystem::file_time_type>
    m_paths;
  bool m_running;
  std::filesystem::path m_path;

  bool contains(const std::filesystem::path& key);

  void initPathsMap( );

  bool is_hidden(const std::filesystem::path& p);

signals:
  void changed(const std::filesystem::path path, const FileEvent);
  void pathChanged(const std::filesystem::path p);
};
