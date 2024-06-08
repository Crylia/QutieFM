#include "FileController.hpp"
#include <chrono>
#include <memory>
#include <iostream>

FileController::FileController( ) {
  m_fmWorker = std::make_shared<FileMonitor>(QString("/home/crylia/Dokumente"),
    std::chrono::milliseconds(1000));
  m_fmWorker->moveToThread(&m_fsThread);

  connect(this, &FileController::operate, m_fmWorker.get( ), &FileMonitor::start);
  connect(m_fmWorker.get( ), &FileMonitor::update, this, &FileController::update);

  m_fsThread.start( );

  emit operate( );
}

FileController::~FileController( ) {
  m_fsThread.quit( );
  m_fsThread.wait( );
}

void FileController::update(const QString path, const FileEvent event) {
  std::cout << path.toStdString( ) << std::endl;
}
