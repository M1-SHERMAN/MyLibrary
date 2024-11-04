#ifndef POTION_TYPE_H
#define POTION_TYPE_H

#include <string>

enum class potion_type
{
	mp_potion,
	hp_potion,
};
inline std::string potion_type_to_string(potion_type type)
{
	switch (type)
	{
	case potion_type::mp_potion:
		return "mp_potion";
	case potion_type::hp_potion:
		return "hp_potion";
	default:
		return "unknown";
	}
}
#endif // POTION_TYPE_H