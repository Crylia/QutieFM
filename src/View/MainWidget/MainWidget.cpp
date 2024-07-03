#include "MainWidget.hpp"
#include <iostream>

MainWidget::MainWidget(QWidget* parent) {

	auto path_mainContentLayout = new QVBoxLayout(this);
	auto fileTree_fileGridLayout = new QHBoxLayout( );
	auto gridLayout = new GridItemView( );

	auto path = new Path( );
	auto backButton = new QPushButton("<");
	backButton->setFixedSize(40, 40);
	auto pathBackLayout = new QHBoxLayout( );
	pathBackLayout->addWidget(backButton);
	pathBackLayout->addWidget(path);


	auto fileController = FileController::instance( );
	connect(backButton, &QPushButton::clicked, this, [fileController]( ) {
		emit fileController->previousPath( );
		});


	fileTree_fileGridLayout->addWidget(gridLayout);

	path_mainContentLayout->addLayout(pathBackLayout);
	path_mainContentLayout->addLayout(fileTree_fileGridLayout);

	setLayout(path_mainContentLayout);
}

MainWidget::~MainWidget( ) { }
