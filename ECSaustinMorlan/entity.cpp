//
// Created by qiaojun on 10/02/24.
//
#include "entity.h"

EntityManager::EntityManager()
{
    for (Entity e = 0; e < MAX_ENTITIES; ++e)
        mAvailableEntIDs.push(e);
}

Entity EntityManager::CreateEntity()
{
    assert(numLivingEntities < MAX_ENTITIES && "Can't create more entities");

    Entity ID = mAvailableEntIDs.front();
    mAvailableEntIDs.pop();
    ++numLivingEntities;

    return ID;
}

void EntityManager::DestroyEntity(Entity e)
{
    assert(numLivingEntities < MAX_ENTITIES && "Destroying an out of range entity ");
    mSignatures[e].reset();
    mAvailableEntIDs.push(e);
    --numLivingEntities;
}

void EntityManager::SetSignature(Entity e, Signature s)
{
    assert(numLivingEntities < MAX_ENTITIES && "Setting signatures for an out of range entity");
    mSignatures[e] = s;
}

Signature EntityManager::GetSignature(Entity e)
{
    assert(numLivingEntities < MAX_ENTITIES && "Getting signature of an out of range entity");
    return mSignatures[e];
}