#include "Path.hpp"


Path::Path(QWidget* parent)
	:QWidget(parent),
#ifdef _WIN32
	pathLabel_m(new QLabel(std::getenv("USERPROFILE"))) {
#else
	pathLabel_m(new QLabel(std::getenv("HOME"))) {
#endif

}

Path::~Path( ) { }
