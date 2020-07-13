#include "pch.h"
#include "Transform.h"

namespace nc
{
	std::istream & nc::operator>>(std::istream & stream, Transform & t)
	{
		stream >> t.position;

		std::string line;
		std::getline(stream, line);
		t.scale = stof(line);

		std::getline(stream, line);
		t.angle = stof(line);

		return stream;
	}
}
