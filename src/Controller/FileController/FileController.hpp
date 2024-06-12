#pragma once

#include <QThread>
#include <memory>

#include "../../Core/FileMonitor/FileMonitor.hpp"

class FileController : public QObject {
  Q_OBJECT
public:
  FileController();
  ~FileController();

private:
  QThread m_fsThread;

  std::shared_ptr<FileMonitor> m_fmWorker;

private slots:

  void update(const std::filesystem::path path, const FileEvent);
  void newPath(const std::unordered_map<std::filesystem::path,
                                        std::filesystem::file_time_type>
                   paths);

signals:
  // Start signal to start the function in the thread
  void operate();
  // Stop signal to stop the function in the thread
  void pause();
  // Signal to update the path inside the thread
  void updatePath(const std::filesystem::path &);

  void pathChanged(const std::unordered_map<std::filesystem::path,
                                            std::filesystem::file_time_type>
                       paths);
};
