#ifndef ENTITY_MANAGER_H
#define ENTITY_MANAGER_H

#include "../ecsDefinitions.h"
#include <queue>
#include <array>
#include <stdexcept>

class EntityManager
{
public:
    EntityManager();
    ~EntityManager();

    void DestroyEntity(Entity entity);
    void SetSignature(Entity entity, Signature signature);
    Signature GetSignature(Entity entity);
    Entity CreateEntity();

private:
    std::queue<Entity> availableEntities{};
    std::array<Signature, MAX_ENTITIES> entitySignatures{};
    uint32_t livingEntityCount;
};

#endif // ENTITY_MANAGER_H
