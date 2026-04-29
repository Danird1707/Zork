#include "Entity.h"

Entity::Entity(EntityType type, std::string& name, std::string& description) {

	m_type = type;
	m_name = name;
	m_description = description;
}

Entity::~Entity()
{

}

EntityType Entity::getType() const {
	return m_type;
}

std::string Entity::getName() const {
	return m_name;
}

void Entity::setName(const std::string name) {
	m_name = name;
}

std::string Entity::getDescription() const {
	return m_description;
}

void Entity::setDescription(const std::string description) {
	m_description = description;
}

void Entity::Update() {

}