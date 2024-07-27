#pragma once

#include <QWidget>
#include <unordered_map>

#include "GridItem.hpp"

class GridView : public QWidget {
	Q_OBJECT
private:
	int m_rows;
	int m_cols;
	int m_spacing;

	QList<GridItem> m_gridItemList;

	unordered_map<fs::path, QWidget*> m_gridMap;

	QGridLayout* m_gridLayout;

public:
	/**
	 * @brief Construct a new Grid View object
	 * Widgets are managed by a seperate unordered gridMap since its easier
	 * than to traverse the Qt widget tree to find a specific widget
	 *
	 * @param parent
	 */
	explicit GridView(QWidget* parent = nullptr);
	~GridView( ) = default;
	GridView& operator= (const GridView& other) = delete;
	GridView(GridView&& other) = delete;
	GridView& operator=(GridView&& other) noexcept = default;

	QGridLayout* getGridLayout( );

	/**
	 * @brief Add a widget to the gridLayout, position is determined automatically
	 *
	 * @param widget
	 */
	const void addWidget(GridItem* widget);

	/**
	 * @brief Remove a widget by a given path
	 *
	 * @param path
	 */
	const void removeWidgetByPath(const fs::path& path);

	/**
	 * @brief Get the Grid Map object
	 *
	 * @return unordered_map<fs::path, QWidget*>*
	 */
	unordered_map<fs::path, QWidget*>& getGridMap( );

	/**
	 * @brief Clear the gridLayout and the gridMap
	 *
	 */
	void clear( );
};
