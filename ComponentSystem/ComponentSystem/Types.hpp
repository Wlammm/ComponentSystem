#pragma once

#include <bitset>

// Max components of one type.
constexpr size_t MAX_COMPONENTS = 1000;
// Max number of gameobjects at once.
constexpr size_t MAX_GAMEOBJECTS = 10000;

using GameObjectID = unsigned int;

using ComponentType = size_t;
using Signature = std::bitset<MAX_COMPONENTS>;