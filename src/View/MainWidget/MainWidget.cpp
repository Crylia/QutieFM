#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget* parent) {

	auto path_mainContentLayout = new QHBoxLayout(this);
	auto fileTree_fileGridLayout = new QVBoxLayout(this);

	auto gridLayout = new GridItemView(this);

	fileTree_fileGridLayout->addWidget(gridLayout);

	path_mainContentLayout->addLayout(fileTree_fileGridLayout);

	setLayout(path_mainContentLayout);
}

MainWidget::~MainWidget( ) { }
