#include "../ecsDefinitions.h"
#include "ComponentManager.h"


ComponentType ComponentManager::GetComponentType(const std::string& componentName)
{
    return componentTypes[componentName];
}

void ComponentManager::EntityDestroyed(Entity entity)
{
    for (auto const& pair : componentArrays)
    {
        auto const& component = pair.second;

        component->EntityDestroyed(entity); // Notify each ComponentArray that an entity has been destroyed
    }
}

