#pragma once

#include <QMainWindow>

#include "../MainWidget/MainWidget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow( );

private:

  std::shared_ptr<MainWidget> m_mainWidget;
};
