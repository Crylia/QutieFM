#include "GridItemView.hpp"
#include <iostream>

GridItemView::GridItemView(QWidget *parent)
    : QFrame(parent), fileController(std::make_shared<FileController>()) {

  QGridLayout *mainLayout = new QGridLayout();

  connect(fileController.get(), &FileController::pathChanged, this,
          [this,
           mainLayout](const std::unordered_map<std::filesystem::path,
                                                std::filesystem::file_time_type>
                           paths) {
            std::cout << "path.first" << std::endl;

            for (auto path : paths) {
              mainLayout->addWidget(new GridItem(path.first, this));
            }
          });
}

GridItemView::~GridItemView() {}
