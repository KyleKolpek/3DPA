#include "Key.h"

#include <sstream>

namespace Luatable
{
	Key::Key(int i)
	{
		std::stringstream s;
		s << i;
		key = s.str();
	}

	Key::Key(const std::string& s)
	{
		key = s;
	}

	Key::Key(const char* s)
	{
		key = s;
	}

	bool
	Key::operator<(const Key& other) const
	{
		return key < other.key;
	}

	bool
	Key::operator==(const Key& other) const
	{
		return key == other.key;
	}

	std::ostream&
	operator<<(std::ostream& stream, const Key& key)
	{
		stream << key.key;
		return stream;
	}
}	//	Luatable
