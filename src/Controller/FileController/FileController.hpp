#pragma once

#include <QThread>
#include <memory>

#include "../../Core/FileMonitor/FileMonitor.hpp"

class FileController : public QObject {
  Q_OBJECT
public:
  FileController( );
  ~FileController( );

private:
  QThread m_fsThread;

  std::shared_ptr<FileMonitor> m_fmWorker;

private slots:

  void update(const QString path, const FileEvent);

signals:
  // Start signal to start the function in the thread
  void operate( );
  // Stop signal to stop the function in the thread
  void pause( );
  // Signal to update the path inside the thread
  void updatePath(const QString&);
};
