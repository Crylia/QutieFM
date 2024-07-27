#include "GridView.hpp"

GridView::GridView(QWidget* parent) :
	QWidget(parent) {
	m_gridLayout = new QGridLayout( );

	m_gridLayout->setAlignment(Qt::AlignTop);
	setLayout(m_gridLayout);
}

QGridLayout* GridView::getGridLayout( ) {
	return m_gridLayout;
}

const void GridView::addWidget(GridItem* widget) {
	m_gridMap[widget->getPath( )] = widget;
	int pos = m_gridMap.size( ) - 1;
	m_gridLayout->addWidget(widget, pos / 8, pos % 8);
	widget->show( );
}

const void GridView::removeWidgetByPath(const fs::path& path) {
	m_gridLayout->removeWidget(m_gridMap.at(path));
	delete m_gridMap[path];
	m_gridMap.erase(path);

	// Rearrange the widgets so there is no random hole in the grid
	int pos = 0;
	for (const auto& [key, widget] : m_gridMap) {
		m_gridLayout->addWidget(widget, pos / 8, pos % 8);
		pos++;
	}
}

unordered_map<fs::path, QWidget*>& GridView::getGridMap( ) {
	return m_gridMap;
}

void GridView::clear( ) {
	QLayoutItem* wItem;
	while ((wItem = m_gridLayout->takeAt(0)) != 0) {
		if (wItem->widget( ))
			wItem->widget( )->setParent(nullptr);
		delete wItem;
	}
	m_gridMap.clear( );
}
