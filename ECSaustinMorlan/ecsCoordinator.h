//
// Created by qiaojun on 10/02/24.
//

#ifndef ECSCOORDINATOR_H
#define ECSCOORDINATOR_H

#include "entity.h"
#include "components.h"
#include "system.h"
#include "event.h"

class Coordinator
{
public:
    void Init();
    Entity CreateEntity();
    void DestroyEntity(Entity e);

    template<typename T>
    void AddComponent(Entity e, T component);
    template<typename T>
    void RemoveComponent(Entity e);
    template<typename T>
    T& GetComponent(Entity e);
    template<typename T>
    ComponentType GetComponentType();

    void AddEventListener(EventID ev_id, std::function<void(Event&)> const& listener);
    void SendEvent(Event& ev);
    void SendEvent(EventID evID);
    template<typename T>
    std::shared_ptr<T> RegisterSystem();
    template<typename T>
    void SetSystemSignature(Signature sig);
private:
    std::unique_ptr<ComponentManager> mCM;
    std::unique_ptr<EntityManager> mEM;
    std::unique_ptr<SystemManager> mSM;
    std::unique_ptr<EventManager> mEvM;
};


#endif //ECSCOORDINATOR_H
