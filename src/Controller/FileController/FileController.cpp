#include "FileController.hpp"
#include <chrono>
#include <filesystem>
#include <iostream>
#include <memory>
#include <unordered_map>

FileController::FileController() {
#ifdef _WIN32
  m_fmWorker = std::make_shared<FileMonitor>(
      std::filesystem::path(std::getenv("USERPROFILE")),
      std::chrono::milliseconds(1000));
#else
  m_fmWorker = std::make_shared<FileMonitor>(
      std::filesystem::path("/home/crylia/Dokumente"),
      std::chrono::milliseconds(1000));
#endif

  m_fmWorker->moveToThread(&m_fsThread);

  connect(this, &FileController::operate, m_fmWorker.get(),
          &FileMonitor::start);
  connect(m_fmWorker.get(), &FileMonitor::fileCreated, this,
          &FileController::update);
  connect(m_fmWorker.get(), &FileMonitor::pathChanged, this,
          &FileController::newPath);

  m_fsThread.start();

  emit operate();
}

FileController::~FileController() {
  m_fsThread.quit();
  m_fsThread.wait();
}

void FileController::newPath(
    std::unordered_map<std::filesystem::path, std::filesystem::file_time_type>
        path) {
  std::cout << "test" << std::endl;
  emit pathChanged(path);
}

void FileController::update(const std::filesystem::path path,
                            const FileEvent event) {
  std::cout << "bruh" << std::endl;
  std::cout << path.string() << std::endl;
}
