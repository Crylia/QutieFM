#pragma once

#include <QObject>
#include <QString>
#include <chrono>
#include <filesystem>
#include <unordered_map>

enum class FileEvent { created, modified, erased };

class FileMonitor : public QObject {
  Q_OBJECT
public:
  std::chrono::duration<int, std::milli> m_delay;

  FileMonitor(QString path, std::chrono::duration<int, std::milli> delay);
  ~FileMonitor() = default;

  void SetPath(QString path) { m_path = path; }

public slots:
  void start(const QString path);
  void stop();

private:
  std::unordered_map<QString, std::filesystem::file_time_type> m_paths;
  bool m_running;
  QString m_path;

  bool contains(const QString &key);

signals:
  void update(const QString path, const FileEvent);
};
