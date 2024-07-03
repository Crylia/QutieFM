#include "GridItemView.hpp"
#include <iostream>

GridItemView::GridItemView(QWidget* parent)
  : QFrame(parent), fileController(FileController::instance( )) {

  QVBoxLayout* mainLayout = new QVBoxLayout(this);
  QGridLayout* gridLayout = new QGridLayout( );

  gridLayout->setAlignment(Qt::AlignTop);

  mainLayout->addLayout(gridLayout);
  setLayout(mainLayout);

  connect(fileController, &FileController::pathChanged, this,
    [this, gridLayout](const std::filesystem::path path) {
      // No, QT Does not offer a better way to clear a layout, at least this solution doesnt segfault
      QLayoutItem* wItem;
      while ((wItem = gridLayout->takeAt(0)) != 0) {
        if (wItem->widget( ))
          wItem->widget( )->setParent(nullptr);
        delete wItem;
      }
      gridMap.clear( );
    });

  connect(fileController, &FileController::contentChanged, this, [this, gridLayout](std::filesystem::path path, FileEvent event) {
    if (event == FileEvent::created) {
      auto w = new GridItem(path);
      gridMap[path] = w;
      connect(w, &GridItem::doubleClicked, this, [this, path]( ) {
        if (!std::filesystem::is_directory(path))
          return;
        emit fileController->updatePath(path);
        });
      connect(w, &GridItem::clicked, this, [this, path]( ) {
        if (std::filesystem::is_directory(path))
          return;

        std::string cmd = "xdg-open \"" + path.string( ) + "\"";
        std::system(cmd.c_str( ));
        });
      int pos = gridMap.size( ) - 1;
      gridLayout->addWidget(w, pos / 8, pos % 8);
      w->show( );
    } else if (event == FileEvent::erased) {
      gridLayout->removeWidget(gridMap[path]);
      delete gridMap[path];
      gridMap.erase(path);

      int pos = 0;
      for (const auto& [key, widget] : gridMap) {
        gridLayout->addWidget(widget, pos / 8, pos % 8);
        pos++;
      }
    } else if (event == FileEvent::modified) {
      // Idk what this would be used for
    }

    });

}

GridItemView::~GridItemView( ) { }
