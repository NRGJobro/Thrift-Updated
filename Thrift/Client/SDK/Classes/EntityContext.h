#pragma once
#include <cstdint>


class EntityId;

struct EntityIdTraits {
	using value_type = EntityId;

	using entity_type = uint32_t;
	using version_type = uint16_t;

	static constexpr entity_type entity_mask = 0x3FFFF;
	static constexpr version_type version_mask = 0x3FFF;
};
