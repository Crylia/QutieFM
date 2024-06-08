#pragma once

#include <QFrame>

#include "../Widgets/GridItem/GridItem.hpp"
#include "../../Controller/FileController/FileController.hpp"

class GridItemView : public QFrame {
	Q_OBJECT
private:
	int m_rows;
	int m_cols;
	int m_spacing;

	QList<GridItem> m_gridItemList;

	std::shared_ptr<FileController> fileController;

public:
	GridItemView(QWidget* parent = nullptr);
	~GridItemView( );

private slots:
	//void onSizeChanged( );
};
