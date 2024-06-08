#pragma once

#include <QObject>
#include <chrono>
#include <filesystem>
#include <unordered_map>

enum class FileEvent { created, modified, erased };

class FileMonitor : public QObject {
  Q_OBJECT
public:
  std::chrono::duration<int, std::milli> m_delay;

  FileMonitor(std::filesystem::path path, std::chrono::duration<int, std::milli> delay);
  ~FileMonitor( ) = default;

  void SetPath(std::filesystem::path path) { m_path = path; }

public slots:
  void start( );
  void stop( );

private:
  std::unordered_map<std::filesystem::path, std::filesystem::file_time_type> m_paths;
  bool m_running;
  std::filesystem::path m_path;

  bool contains(const std::filesystem::path& key);

signals:
  void update(const std::filesystem::path path, const FileEvent);
  void newPathEntered(const std::unordered_map<std::filesystem::path, std::filesystem::file_time_type> paths);
};
