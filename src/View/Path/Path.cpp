#include "Path.hpp"


Path::Path(QWidget* parent)
	:QWidget(parent),
	m_fileController(FileController::instance( )),
#ifdef _WIN32
	m_pathLabel(new QLabel(std::getenv("USERPROFILE"))) {
#else
	m_pathLabel(new QLabel(std::getenv("HOME"))) {
#endif

	auto layout = new QHBoxLayout(this);

	m_pathLabel->setStyleSheet(R"(
	
		background-color: #313131;
		border: 2px solid #414141;
		border-radius: 6px;
		color: #D8D8D8;
		font-size: 22px;
	)");

	setFixedHeight(48);

	connect(m_fileController, &FileController::pathChanged, this,
		[this](const std::filesystem::path path) {
			setPath(QString::fromStdString(path.string( )));
		});
	layout->addWidget(m_pathLabel);
}

Path::~Path( ) { }
