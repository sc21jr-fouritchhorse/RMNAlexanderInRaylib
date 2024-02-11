//
// Created by qiaojun on 10/02/24.
//

#ifndef SYSTEM_H
#define SYSTEM_H

#include "ECSDefs.h"
#include "entity.h"
#include "components.h"

class System
{
public:
    std::set<Entity> mEntities;
};
class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem();

    template<typename T>
    void SetSignature(Signature sig);

    void EntityDestroyed(Entity ent);

    void EntitySigChanged(Entity e, Signature e_sig);

private:
    std::unordered_map<const char*, Signature> mSignatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> mSystems{};
};


#endif //SYSTEM_H
