//
// Created by qiaojun on 10/02/24.
//

#ifndef ENTITY_H
#define ENTITY_H

#include "ECSDefs.h"

class EntityManager
{
public:
    //Inits all possible IDs for entities
    EntityManager();
    //Checks if we have entities left and assigns an ID if not
    Entity CreateEntity();
    //Frees ID from e by invalidating its signature and adding it
    //to the pool of available entityIDs
    void DestroyEntity(Entity e);
    //Assgins s to e as a signature
    void SetSignature(Entity e, Signature s);
    //Selects the signature from e
    Signature GetSignature(Entity e);
private:
    //Unused Entity IDs we can pick from when creating
    std::queue<Entity> mAvailableEntIDs{};
    //What sig corresponds to what ent
    std::array<Signature, MAX_ENTITIES> mSignatures{};
    //How many entities currently exist in the program
    uint32_t numLivingEntities{};
};

#endif //ENTITY_H
