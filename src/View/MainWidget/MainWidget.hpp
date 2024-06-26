#pragma once

#include <QLayout>
#include <QLabel>
#include <QWidget>
#include <QGridLayout>

#include "../Widgets/GridItem/GridItem.hpp"
#include "../GridItemView/GridItemView.hpp"
#include "../Path/Path.hpp"

class MainWidget : public QWidget {
  Q_OBJECT
public:
  MainWidget(QWidget* parent = nullptr);
  ~MainWidget( );

private:
};
