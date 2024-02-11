#pragma once
#include <bitset>
#include <cstdint>

// ECS vaiable aliases
using Entity = std::uint32_t;
using ComponentType = std::uint8_t;
using EventID = std::uint32_t;
const Entity MAX_ENTITIES = 5000;
const ComponentType MAX_COMPONENTS = 32;
using Signature = std::bitset<MAX_COMPONENTS>;

