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

  std::unique_ptr<FileMonitor> m_fmWorker;
};
