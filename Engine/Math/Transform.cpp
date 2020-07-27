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

	void Transform::Update()
	{
		Matrix3D mxs; mxs.Scale(scale); //Scale
		Matrix3D mxr; mxr.Rotate(angle); //Rotate
		Matrix3D mxt; mxt.Translate(position); //Translate

		matrix = mxs * mxr * mxt; //Scale & Rotate
	}

	void Transform::Update(const Matrix3D pmx)
	{
		Update();
		matrix = matrix * pmx;
	}
}
