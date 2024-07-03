#pragma once

#include <QThread>
#include <memory>
#include <unordered_map>
#include <filesystem>
#include <QApplication>
#include <stack>

#include "../../Core/FileMonitor/FileMonitor.hpp"

class FileController : public QObject {
  Q_OBJECT
public:
  // Static method to access the singleton instance
  static FileController* instance( ) {
    static FileController instance;
    return &instance;
  }

  // Deleting the copy constructor and assignment operator to prevent copying
  FileController(const FileController&) = delete;
  FileController& operator=(const FileController&) = delete;

  std::stack<std::filesystem::path> previousPaths;

private:
  // Private constructor to prevent instantiation
  FileController( );
  ~FileController( );

private:
  QThread m_fsThread;
  std::shared_ptr<FileMonitor> m_fmWorker;

private slots:
  void update(const std::filesystem::path path, const FileEvent event);
  void newPath(const std::filesystem::path p);

signals:
  // Start signal to start the function in the thread
  void operate( );
  // Stop signal to stop the function in the thread
  void pause( );
  // Signal to update the path inside the thread
  void updatePath(const std::filesystem::path& p);

  void pathChanged(const std::filesystem::path p);
  void contentChanged(std::filesystem::path path, FileEvent event);
  void previousPath( );
};
