#include "Place.hpp"

Place::Place(QString name, fs::path path, QString iconPath, PlaceType type) :
	m_name(name),
	m_iconPath(iconPath),
	m_path(path),
	m_type(type) { }

const QString& Place::getName( ) const { return m_name; }
const fs::path& Place::getPath( ) const { return m_path; }
const PlaceType& Place::getType( ) const { return m_type; }
const QString& Place::getIconPath( ) const { return m_iconPath; }
