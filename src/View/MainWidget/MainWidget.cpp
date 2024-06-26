#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget* parent) {

	auto path_mainContentLayout = new QVBoxLayout(this);
	auto fileTree_fileGridLayout = new QHBoxLayout(this);

	auto gridLayout = new GridItemView(this);
	auto path = new Path(this);

	fileTree_fileGridLayout->addWidget(gridLayout);

	path_mainContentLayout->addWidget(path);
	path_mainContentLayout->addLayout(fileTree_fileGridLayout);

	setLayout(path_mainContentLayout);
}

MainWidget::~MainWidget( ) { }
