#include "Entity.h"

//Constructor
Entity::Entity(EntityType type, const std::string& name, const std::string& description) {

	m_type = type;
	m_name = name;
	m_description = description;
}

//Destructor
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

//Adds a entity inside other entity
void Entity::Add(Entity* entity)
{
	if (entity != nullptr) {
		m_contains.push_back(entity);
	}
}

//Removes an entity from other
void Entity::Remove(Entity* entity)
{
	m_contains.remove(entity);
}

//Find an object
Entity* Entity::Find(const std::string& name) const
{
	for (Entity* entity : m_contains) {
		if (entity != nullptr && entity->getName() == name) {
			return entity;
		}
	}

	return nullptr;
}

//Shows the elements that are inside other entity
const std::list<Entity*>& Entity::GetContains() const
{
	return m_contains;
}

void Entity::Update() {

}