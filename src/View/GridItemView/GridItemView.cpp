#include "GridItemView.hpp"
#include <iostream>

GridItemView::GridItemView(QWidget* parent)
  : QFrame(parent), fileController(std::make_shared<FileController>( )) {

  QGridLayout* mainLayout = new QGridLayout( );

  this->setLayout(mainLayout);

  connect(fileController.get( ), &FileController::pathChanged, this,
    [this, mainLayout](const std::unordered_map<std::filesystem::path, std::filesystem::file_time_type> paths) {

      /* int r{ 0 }, c{ 0 };
      for (auto path : paths) {
        auto w = new GridItem(path.first);
        gridMap[path.first] = w;
        mainLayout->addWidget(w, r, c);
        w->show( );
        ++r;
        if ((r % 8) == 0) {
          ++c;
          r = 0;
        }
      } */
    });

  fileController.get( )->updatePath("/home/crylia/Dokumente");

  connect(fileController.get( ), &FileController::contentChanged, this, [this, mainLayout](std::filesystem::path path, FileEvent event) {
    if (event == FileEvent::created) {
      auto w = new GridItem(path);
      gridMap[path] = w;
      int pos = gridMap.size( ) - 1;
      mainLayout->addWidget(w, pos / 8, pos % 8);
      w->show( );
    } else if (event == FileEvent::erased) {
      mainLayout->removeWidget(gridMap[path]);
      delete gridMap[path];
      gridMap.erase(path);

      // Re-layout the remaining widgets
      int pos = 0;
      for (const auto& [key, widget] : gridMap) {
        mainLayout->addWidget(widget, pos / 8, pos % 8);
        pos++;
      }
    } else if (event == FileEvent::modified) {
      std::cout << "modified" << std::endl;
      // Do nothing ig? In theory nothing has to update unless we show the time
    }

    });

}

GridItemView::~GridItemView( ) { }
