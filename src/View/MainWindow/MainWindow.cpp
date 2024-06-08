#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), m_mainWidget(std::make_shared<MainWidget>( )) {
	setWindowTitle("QutieFM");

	setObjectName("MainWindow");

	this->setCentralWidget(m_mainWidget.get( ));
}

MainWindow::~MainWindow( ) { }
