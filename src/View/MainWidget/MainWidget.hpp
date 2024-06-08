#pragma once

#include <QLayout>
#include <QLabel>
#include <QWidget>

#include "../../Controller/FileController/FileController.hpp"

class MainWidget : public QWidget {
  Q_OBJECT
public:
  MainWidget(QWidget* parent = nullptr);
  ~MainWidget( );

private:
};
