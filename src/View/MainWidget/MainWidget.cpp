#include "MainWidget.hpp"

MainWidget::MainWidget(QWidget* parent) {

	auto path_mainContentLayout = std::make_shared<QHBoxLayout>(this);
	auto fileTree_fileGridLayout = std::make_shared<QVBoxLayout>(this);

	path_mainContentLayout->addLayout(fileTree_fileGridLayout.get( ));

	setLayout(path_mainContentLayout.get( ));

	auto fmc = new FileController( );
}

MainWidget::~MainWidget( ) { }
