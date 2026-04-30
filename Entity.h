#ifndef ENTITY_H
#define ENTITY_H

#include<string>
#include<list>

enum class EntityType {
    Entity,
    Room,
    Exit,
    Item,
    Creature,
    Player,
    NPC
};

class Entity {

public:

    Entity(EntityType type, const std::string& name, const std::string& description);
    ~Entity();
    EntityType getType() const;

    std::string getName() const;
    void setName(const std::string name);

    std::string getDescription() const;
    void setDescription(const std::string description);

    void Add(Entity* entity);
    void Remove(Entity* entity);

    Entity* Find(const std::string& name) const;
    const std::list<Entity*>& GetContains() const;



	virtual void Update();
protected:
    EntityType m_type;
    std::string m_name;
    std::string m_description;
    std::list<Entity*> m_contains;
};

#endif
