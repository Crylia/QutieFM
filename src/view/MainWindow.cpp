#include "MainWindow.hpp"

MainWindow::MainWindow(QWidget* parent)
	: QMainWindow(parent) {
	setWindowTitle("QutieFM");

	setObjectName("MainWindow");
	setStyleSheet(R"(
		#MainWindow{
			background-color: #212121;
		}
	)");
	shared_ptr<FileMonitor> fileMonitor = make_shared<FileMonitor>(chrono::milliseconds(1000));
	auto gridView = new GridView( );
	m_fileMonitorController = make_shared<FileMonitorController>(fileMonitor, gridView);

	auto mainLayout = new QVBoxLayout( );
	auto fileTree_fileGridLayout = new QHBoxLayout( );
	auto placesSideBar = new PlacesSidebar( );

	m_placesController = make_unique<PlacesController>(placesSideBar, m_fileMonitorController);

	auto pathWidget = new QLabel(
		QString::fromStdString(
			m_fileMonitorController->getPath( ).string( )
		)
	);
	pathWidget->setStyleSheet(R"(
		background-color: #313131;
		border: 2px solid #414141;
		border-radius: 6px;
		color: #D8D8D8;
		font-size: 16px;
	)");
	pathWidget->setFixedHeight(32);
	connect(fileMonitor.get( ), &FileMonitor::pathChanged, this, [pathWidget](fs::path path) {
		pathWidget->setText(QString::fromStdString(
			path.string( )
		));
		});

	QSvgRenderer renderer(QString(":/icons/chevron-left.svg"));
	QPixmap pixmap(36, 36);
	pixmap.fill(Qt::transparent);
	QPainter painter(&pixmap);
	renderer.render(&painter);
	auto backButton = new NavigationButton(pixmap);
	backButton->setStyleSheet(R"(
			QPushButton{
				background-color: #212121;
				border: 2px solid #414141;
				font-size: 26px;
				font-weight: 900;
				color: #F48FB1;
				border-radius: 8;
			}
		)");
	backButton->setFixedSize(32, 32);
	auto pathBackLayout = new QHBoxLayout( );
	pathBackLayout->addWidget(backButton);
	pathBackLayout->addWidget(pathWidget);

	fileTree_fileGridLayout->addWidget(placesSideBar);
	fileTree_fileGridLayout->addWidget(gridView);

	mainLayout->addLayout(pathBackLayout);
	mainLayout->addLayout(fileTree_fileGridLayout);

	auto centralWidget = new QWidget(this);
	centralWidget->setLayout(mainLayout);

	setCentralWidget(centralWidget);
}
