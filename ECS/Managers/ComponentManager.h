#ifndef COMPONENT_MANAGER_H
#define COMPONENT_MANAGER_H

#include "../ecsDefinitions.h"
#include "../Core/ComponentArray.h"
#include <unordered_map>
#include <memory>
#include <string>


class ComponentManager {
public:
    template<typename T>
    void RegisterComponent(ComponentType componentType) 
    {
        const std::string& componentName = typeid(T).name();
        componentTypes[componentName] = componentType;
        componentArrays[componentName] = std::make_shared<ComponentArray<T>>();
    }
    ComponentType GetComponentType(const std::string& componentName);
    template<typename T>
    void AddComponent(Entity entity, T component)
    {
        GetComponentArray<T>()->InsertData(entity, component);
    }
    template<typename T>
    void RemoveComponent(Entity entity)
    {
        GetComponentArray<T>()->RemoveData(entity);
    }
    template<typename T>
    T& GetComponent(Entity entity)
    {
        return GetComponentArray<T>()->GetData(entity);
    }
    void EntityDestroyed(Entity entity);
private:
	std::unordered_map<std::string, ComponentType> componentTypes;
	std::unordered_map<std::string, std::shared_ptr<IComponentArray>> componentArrays;
	ComponentType mNextComponentType{};
    template<typename T>
    std::shared_ptr<ComponentArray<T>> GetComponentArray()
    {
        const char* typeName = typeid(T).name();

        return std::static_pointer_cast<ComponentArray<T>>(componentArrays[typeName]);
    }
};

#endif // COMPONENT_MANAGER_H
