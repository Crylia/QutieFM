#include "FileController.hpp"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>

FileController::FileController( ) {
  m_fmWorker = std::make_shared<FileMonitor>(
    std::chrono::milliseconds(1000));
  m_fmWorker->moveToThread(&m_fsThread);

  // starts the directory monitoring thread, forgot why it has to be a signal, only works this way not with a direct call
  connect(this, &FileController::operate, m_fmWorker.get( ),
    &FileMonitor::start);
  // main signal to populate the file grid, passes the path and event each time a file is deleted, created or updated
  connect(m_fmWorker.get( ), &FileMonitor::changed, this,
    &FileController::update);
  // Propagating signal from the monitor that fires when the path is changed
  connect(m_fmWorker.get( ), &FileMonitor::pathChanged, this,
    &FileController::newPath);
#ifdef _WIN32
  m_fmWorker.get( )->SetPath(std::filesystem::path(std::getenv("USERPROFILE")));
#else
  m_fmWorker.get( )->SetPath(std::filesystem::path(std::getenv("HOME")));
#endif
  // Signal to update the path, when fired passes the new path and will be given to the monitor
  connect(this, &FileController::updatePath, this, [this](std::filesystem::path p) {
    previousPaths.push(m_fmWorker.get( )->GetPath( ));
    m_fmWorker.get( )->SetPath(p);
    });
  connect(this, &FileController::previousPath, this, [this]( ) {
    if (previousPaths.empty( )) return;

    m_fmWorker.get( )->SetPath(previousPaths.top( ));
    previousPaths.pop( );
    });
  m_fsThread.start( );

  emit operate( );
}

FileController::~FileController( ) {
  m_fsThread.quit( );
  m_fmWorker.get( )->stop( );
  m_fsThread.wait( );
}

void FileController::newPath(const std::filesystem::path p) {
  emit pathChanged(p);
}

void FileController::update(const std::filesystem::path path,
  const FileEvent event) {
  emit contentChanged(path, event);
}
