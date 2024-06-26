#pragma once

#include <QWidget>
#include <QLabel>

class Path : public QWidget {
	Q_OBJECT
private:
	QLabel* pathLabel_m;
	QString path_m;
public:
	Path(QWidget* parent = nullptr);
	~Path( );

	QString path( ) { return path_m; }
	void setPath(QString path) {
		if (path == this->path_m) { return; }

		path_m = path;
		pathLabel_m->setText(path_m);
	}
};

