#ifndef SYSTEM_MANAGER_H
#define SYSTEM_MANAGER_H

#include "../Core/System.h"
#include <memory>
#include <unordered_map>
#include <stdexcept>

class SystemManager
{
public:
    template<typename T>
    std::shared_ptr<T> RegisterSystem()
    {
        const char* typeName = typeid(T).name();

        if (systems.find(typeName) != systems.end())
        {
            throw std::runtime_error("Registering system more than once.");
        }

        auto system = std::make_shared<T>();
        systems.insert({typeName, system});

        return system;
    }

    template<typename T>
    void SetSignature(Signature signature)
    {
        const char* typeName = typeid(T).name();

        if (systems.find(typeName) == systems.end())
        {
            throw std::runtime_error("System used before registered.");
        }

        systemSignatures.insert({typeName, signature});
    }

    void EntityDestroyed(Entity entity);
    void EntitySignatureChanged(Entity entity, Signature entitySignature);
private:
    std::unordered_map<const char*, Signature> systemSignatures{};
    std::unordered_map<const char*, std::shared_ptr<System>> systems{};
};

#endif // SYSTEM_MANAGER_H