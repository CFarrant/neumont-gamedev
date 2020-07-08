#include "pch.h"
#include "Color.h"

std::istream & nc::operator>>(std::istream & stream, Color & c)
{
	std::string line;
	std::getline(stream, line);

	if (line.find("{") != std::string::npos)
	{
		// {1, 1, 1}
		std::string cr = line.substr(line.find("{") + 1, line.find(",") - line.find("{") - 1);
		c.r = std::stof(cr);

		std::string cg = line.substr(line.find(",") + 1, line.find(",") - line.find(",") - 1);
		c.g = std::stof(cg);

		std::string cb = line.substr(line.find(",") + 1, line.find("}") - line.find(",") - 1);
		c.b = std::stof(cb);
	}

	return stream;
}
