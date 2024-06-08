#pragma once

#include <QMainWindow>

#include "../MainWidget/MainWidget.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget* parent = nullptr);
  ~MainWindow( );

private:

  MainWidget* m_mainWidget;
};
