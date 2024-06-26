#include "FileController.hpp"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>

FileController::FileController( ) {
#ifdef _WIN32
  m_fmWorker = std::make_shared<FileMonitor>(
    std::filesystem::path(std::getenv("USERPROFILE")),
    std::chrono::milliseconds(1000));
#else
  m_fmWorker = std::make_shared<FileMonitor>(
    std::filesystem::path(std::getenv("HOME")),
    std::chrono::milliseconds(1000));
#endif

  m_fmWorker->moveToThread(&m_fsThread);

  connect(this, &FileController::operate, m_fmWorker.get( ),
    &FileMonitor::start);
  connect(m_fmWorker.get( ), &FileMonitor::changed, this,
    &FileController::update);
  connect(m_fmWorker.get( ), &FileMonitor::pathChanged, this,
    &FileController::newPath);

  //Why this no workie
  //connect(this, &FileController::updatePath, m_fmWorker.get( ), &FileMonitor::SetPath);
  connect(this, &FileController::updatePath, this, [this](std::filesystem::path p) {
    m_fmWorker.get( )->SetPath(p);
    });


  m_fsThread.start( );

  emit operate( );
}

FileController::~FileController( ) {
  m_fsThread.quit( );
  m_fsThread.wait( );
}

void FileController::newPath(const std::filesystem::path p) {
  emit pathChanged(p);
}

void FileController::update(const std::filesystem::path path,
  const FileEvent event) {
  emit contentChanged(path, event);
}
