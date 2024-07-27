#pragma once

#include <QObject>
#include <QString>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

enum class PlaceType { MyComputer, Device };

class Place : public QObject {
	Q_OBJECT
private:
	QString m_name;
	fs::path m_path;
	PlaceType m_type;
	QString m_iconPath;

public:
	Place(QString name, fs::path path, QString iconPath, PlaceType type);
	~Place( ) = default;
	Place& operator=(const Place& other) = delete;
	Place(Place&& other) noexcept = delete;
	Place& operator=(Place&& other) noexcept = default;

	const QString& getName( ) const;
	const fs::path& getPath( ) const;
	const PlaceType& getType( ) const;
	const QString& getIconPath( ) const;
};
