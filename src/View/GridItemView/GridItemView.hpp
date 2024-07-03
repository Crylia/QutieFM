#pragma once

#include <QFrame>
#include <QScrollArea>
#include <cstdlib>

#include "../Widgets/GridItem/GridItem.hpp"
#include "../../Controller/FileController/FileController.hpp"

class GridItemView : public QFrame {
	Q_OBJECT
private:
	int m_rows;
	int m_cols;
	int m_spacing;

	QList<GridItem> m_gridItemList;

	FileController* fileController;

	//Grid map to keep track of the widgets, and delete them easily as QT doesnt
	//provide an easy way to find children by a property
	std::unordered_map<std::filesystem::path, QWidget*> gridMap;

public:
	GridItemView(QWidget* parent = nullptr);
	~GridItemView( );

private slots:
	//void onSizeChanged( );
};
