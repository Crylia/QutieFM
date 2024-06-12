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

  FileMonitor(std::filesystem::path path,
              std::chrono::duration<int, std::milli> delay);
  ~FileMonitor() = default;

  void SetPath(std::filesystem::path path);

public slots:
  void start();
  void stop();

private:
  std::unordered_map<std::filesystem::path, std::filesystem::file_time_type>
      m_paths;
  bool m_running;
  std::filesystem::path m_path;

  bool contains(const std::filesystem::path &key);

  void initPathsMap();

signals:
  void fileDeleted(const std::filesystem::path path, const FileEvent);
  void fileCreated(const std::filesystem::path path, const FileEvent);
  void fileModified(const std::filesystem::path path, const FileEvent);
  void pathChanged(const std::unordered_map<std::filesystem::path,
                                            std::filesystem::file_time_type>
                       paths);
};
