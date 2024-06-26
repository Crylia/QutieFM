#pragma once

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>

#include "../../Controller/FileController/FileController.hpp"

class Path : public QWidget {
	Q_OBJECT
private:
	QLabel* m_pathLabel;
	QString m_path;

	FileController* m_fileController;

public:
	Path(QWidget* parent = nullptr);
	~Path( );

	QString path( ) { return m_path; }
	void setPath(QString path) {
		if (path == this->m_path) { return; }

		m_path = path;
		m_pathLabel->setText(m_path);
	}
};

