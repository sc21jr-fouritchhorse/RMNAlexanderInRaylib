#include "EntityManager.h"

// Implementation of EntityManager member functions

EntityManager::EntityManager() {
    for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
        availableEntities.push(entity);
    }
}

EntityManager::~EntityManager() {
    // Nothing to do here
}

Entity EntityManager::CreateEntity() {
    if (livingEntityCount >= MAX_ENTITIES) {
        throw std::runtime_error("Too many entities in existence.");
    }

    Entity id = availableEntities.front();
    availableEntities.pop();
    livingEntityCount++;
    return id;
}


void EntityManager::DestroyEntity(Entity entity) {
    if (entity >= MAX_ENTITIES) {
        throw std::out_of_range("Entity out of range.");
    }

    entitySignatures[entity].reset();
    availableEntities.push(entity);
    livingEntityCount--;
}


