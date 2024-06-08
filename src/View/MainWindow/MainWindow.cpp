#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent), m_mainWidget(new MainWidget( )) {
	setWindowTitle("QutieFM");

	setObjectName("MainWindow");

	this->setCentralWidget(m_mainWidget);
}

MainWindow::~MainWindow( ) { }
