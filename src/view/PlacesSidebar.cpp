#include "PlacesSidebar.hpp"

PlacesSidebar::PlacesSidebar(QWidget* parent) :
	QFrame(parent),
	m_mainLayout(new QVBoxLayout(this)),
	m_mycomputerLayout(new QVBoxLayout( )),
	m_devicesLayout(new QVBoxLayout( )) {

	auto myComputerLabel = new QLabel("Mein Computer");
	auto devicesLabel = new QLabel("Geräte");

	myComputerLabel->setObjectName("mycomputerLabel");
	myComputerLabel->setContentsMargins(QMargins(10, 5, 10, 5));
	devicesLabel->setObjectName("devicesLabel");
	devicesLabel->setContentsMargins(QMargins(10, 5, 10, 5));

	setStyleSheet(R"(
		#devicesLabel{
			background-color: #9FA8DA;
			color: #212121;
			font-weight: bold;
			font-size: 18px;
			border-radius: 4;
		}
		#mycomputerLabel{
			background-color: #81D4FA;
			color: #212121;
			font-weight: bold;
			font-size: 18px;
			border-radius: 4;
		}
	)");

	m_mycomputerLayout->addWidget(myComputerLabel, 0, Qt::AlignTop);
	m_devicesLayout->addWidget(devicesLabel, 0, Qt::AlignTop);

	m_mainLayout->addLayout(m_mycomputerLayout);
	m_mainLayout->addLayout(m_devicesLayout);
}

const QList<PlacesButton*>& PlacesSidebar::getComputerList( ) const {
	return m_computerList;
}
const QList<PlacesButton*>& PlacesSidebar::getDevicesList( ) const {
	return m_devicesList;
}

const void PlacesSidebar::addComputerToList(PlacesButton* place) {
	m_computerList.append(place);
	m_mycomputerLayout->addWidget(place);
	place->show( );
}
const void PlacesSidebar::addDeviceToList(PlacesButton* place) {
	m_devicesList.append(place);
	m_devicesLayout->addWidget(place);
	place->show( );
}

