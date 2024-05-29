#include "FileController.hpp"
#include <chrono>
#include <memory>

FileController::FileController() {
  m_fmWorker = std::make_unique<FileMonitor>(QString("/home/crylia/"),
                                             std::chrono::milliseconds(1000));
  m_fmWorker->moveToThread(&m_fsThread);

  m_fmWorker->start(QString("/home/crylia/"));
}

FileController::~FileController() {
  m_fsThread.quit();
  m_fsThread.wait();
}
