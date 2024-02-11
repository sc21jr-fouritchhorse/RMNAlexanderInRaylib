//
// Created by qiaojun on 10/02/24.
//

#include "system.h"


template <typename T>
std::shared_ptr<T> SystemManager::RegisterSystem()
{
    const char* tName = typeid(T).name();

    assert(mSystems.find(tName) == mSystems.end() && "System already registered");
    auto sys = std::make_shared<T>();
    mSystems.insert({tName, sys});
    return sys;
}

template <typename T>
void SystemManager::SetSignature(Signature sig)
{
    const char* typeName = typeid(T).name();

    assert(mSystems.find(typeName) != mSystems.end() && "System used before registration.");

    // Set the signature for this system
    mSignatures.insert({typeName, sig});

}

void SystemManager::EntityDestroyed(Entity ent)
{
    for (auto const& pair : mSystems)
    {
        auto const& system = pair.second;

        system->mEntities.erase(ent);
    }
}

void SystemManager::EntitySigChanged(Entity e, Signature e_sig)
{
    for(auto const& pair : mSystems)
    {
        auto const& type = pair.first;
        auto const& sys = pair.second;
        auto const& sysSig = mSignatures[type];

        if((e_sig & sysSig) == sysSig)
            sys->mEntities.insert(e);
        else
            sys->mEntities.erase(e);
    }
}
