//
// Created by qiaojun on 10/02/24.
//

#include "ecsCoordinator.h"


template <typename T>
void Coordinator::AddComponent(Entity e, T component)
{
    mCM->AddComponent<T>(e, component);
    auto sig = mEM->GetSignature(e);
    sig.set(mCM->GetComponentType<T>(), true);
    mEM->SetSignature(e, sig);
    mSM->EntitySigChanged(e, sig);
}

template <typename T>
void Coordinator::RemoveComponent(Entity e)
{
    mCM->RemoveComponent<T>(e);
    auto sig = mEM->GetSignature(e);
    sig.set(mCM->GetComponentType<T>(), false);
    mEM->SetSignature(e, sig);
    mSM->EntitySigChanged(e, sig);

}

template <typename T>
T& Coordinator::GetComponent(Entity e)
{
    return mCM->GetComponent<T>(e);
}

template <typename T>
ComponentType Coordinator::GetComponentType()
{
    return mCM->GetComponentType<T>();
}

template <typename T>
std::shared_ptr<T> Coordinator::RegisterSystem()
{
    return mSM->RegisterSystem<T>();
}

template <typename T>
void Coordinator::SetSystemSignature(Signature sig)
{
}


template <typename T>
void ComponentManager::AddComponent(Entity e, T compoenent)
{
    GetComponentArray<T>()->InsertData(e, compoenent);
}

template <typename T>
void ComponentManager::RemoveComponent(Entity e)
{
    GetComponentArray<T>()->RemoveData(e);
}

template <typename T>
T& ComponentManager::GetComponent(Entity e)
{
    return GetComponentArray<T>()->GetData(e);
}

void ComponentManager::EntitiyDestroyed(Entity e)
{
    for (auto const& pair : mComponentArrays)
    {
        auto const& component = pair.second;
        component->EntityDestroyed(e);
    }
}


void Coordinator::Init()
{
    mCM = std::make_unique<ComponentManager>();

    mEM = std::make_unique<EntityManager>();

    mSM = std::make_unique<SystemManager>();
}

Entity Coordinator::CreateEntity()
{
    return mEM->CreateEntity();
}

void Coordinator::DestroyEntity(Entity e)
{
    mEM->DestroyEntity(e);
    mCM->EntitiyDestroyed(e);
    mSM->EntityDestroyed(e);
}

void Coordinator::SendEvent(Event& ev)
{
    mEvM->SendEvent(ev);
}

void Coordinator::AddEventListener(EventID ev_id, std::function<void(Event&)> const& listener)
{
    mEvM->AddListener(ev_id, listener);
}

void Coordinator::SendEvent(EventID evID)
{
    mEvM->SendEvent(evID);
}



