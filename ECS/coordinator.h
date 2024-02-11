#ifndef COORDINATOR_H 
#define COORDINATOR_H

#include "ecsDefinitions.h"
#include "Managers/ComponentManager.h"
#include "Managers/SystemManager.h"
#include "Managers/EntityManager.h"

class Coordinator
{
public:
    void Init()
    {
        componentManager = std::make_unique<ComponentManager>();
        systemManager = std::make_unique<SystemManager>();
        entityManager = std::make_unique<EntityManager>();
    }

    Entity CreateEntity()
    {
        return entityManager->CreateEntity();
    }

    void DestroyEntity(Entity entity)
    {
        entityManager->DestroyEntity(entity);

        componentManager->EntityDestroyed(entity);
        systemManager->EntityDestroyed(entity);
    }

    template<typename T>
    void RegisterComponent()
    {
        componentManager->RegisterComponent<T>();
    }

    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        componentManager->AddComponent<T>(entity, component);

        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType( 
            std::string(typeid(T).name())
        ), true);
        entityManager->SetSignature(entity, signature);

        systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    void RemoveComponent(Entity entity)
    {
        componentManager->RemoveComponent<T>(entity);

        auto signature = entityManager->GetSignature(entity);
        signature.set(componentManager->GetComponentType(
            std::string(typeid(T).name())
        ), false);
        entityManager->SetSignature(entity, signature);

        systemManager->EntitySignatureChanged(entity, signature);
    }

    template<typename T>
    T& GetComponent(Entity entity)
    {
        return componentManager->GetComponent<T>(entity);
    }

    template<typename T>
    ComponentType GetComponentType()
    {
        return componentManager->GetComponentType(std::string(typeid(T).name()));
    }

    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        return systemManager->RegisterSystem<T>();
    }

    template<typename T>
    void SetSystemSignature(Signature signature)
    {
        systemManager->SetSignature<T>(signature);
    }
    private:
        std::unique_ptr<ComponentManager> componentManager;
        std::unique_ptr<SystemManager> systemManager;
        std::unique_ptr<EntityManager> entityManager;
};

#endif // COORDINATOR_H