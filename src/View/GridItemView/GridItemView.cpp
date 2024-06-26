#include "GridItemView.hpp"
#include <iostream>

GridItemView::GridItemView(QWidget* parent)
  : QFrame(parent), fileController(FileController::instance( )) {

  QGridLayout* mainLayout = new QGridLayout( );

  this->setLayout(mainLayout);

  connect(fileController, &FileController::pathChanged, this,
    [this, mainLayout](const std::filesystem::path path) {
      while (mainLayout->count( )) {
        QWidget* widget = mainLayout->itemAt(0)->widget( );
        if (widget) {
          mainLayout->removeWidget(widget);
          delete widget;
        }
      }
    });

  connect(fileController, &FileController::contentChanged, this, [this, mainLayout](std::filesystem::path path, FileEvent event) {
    if (event == FileEvent::created) {
      auto w = new GridItem(path);
      gridMap[path] = w;
      connect(w, &GridItem::clicked, this, [this, path]( ) {
        emit fileController->updatePath(path);
        });
      int pos = gridMap.size( ) - 1;
      mainLayout->addWidget(w, pos / 8, pos % 8);
      w->show( );
    } else if (event == FileEvent::erased) {
      mainLayout->removeWidget(gridMap[path]);
      delete gridMap[path];
      gridMap.erase(path);

      int pos = 0;
      for (const auto& [key, widget] : gridMap) {
        mainLayout->addWidget(widget, pos / 8, pos % 8);
        pos++;
      }
    } else if (event == FileEvent::modified) {
      std::cout << "modified" << std::endl;
    }

    });

}

GridItemView::~GridItemView( ) { }
