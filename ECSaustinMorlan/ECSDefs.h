//
// Created by qiaojun on 10/02/24.
//

#ifndef THE_ECS_H
#define THE_ECS_H
#include <cassert>
#include <memory>
#include <unordered_map>
#include <array>
#include <any>
#include <functional>
#include <list>
#include <cstdint>
#include <set>
#include <queue>
#include <bitset>

//https://austinmorlan.com/posts/entity_component_system
#define METHOD_LISTENER(EventType, Listener) EventType, std::bind(&Listener, this, std::placeholders::_1)
#define FUNCTION_LISTENER(EventType, Listener) EventType, std::bind(&Listener, std::placeholders::_1)

using Entity = uint32_t;
using EventID = uint32_t;
using ParamID = uint32_t;
using ComponentType = uint8_t;

constexpr Entity MAX_ENTITIES = 5000;
constexpr ComponentType MAX_COMPONENTS = 32;

using Signature = std::bitset<MAX_COMPONENTS>;

// Source: https://gist.github.com/Lee-R/3839813
constexpr std::uint32_t fnv1a_32(char const* s, std::size_t count)
{
    return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u; // NOLINT (hicpp-signed-bitwise)
}

constexpr std::uint32_t operator "" _hash(char const* s, std::size_t count)
{
    return fnv1a_32(s, count);
}



#endif //ENTITYMANAGER_H
