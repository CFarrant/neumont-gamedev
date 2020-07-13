#pragma once
#include "../Graphics/Shape.h"
#include "../Math/Transform.h"

namespace nc
{
	class Actor
	{
	public:
		Actor();
		Actor(const Transform& transform, const Shape& shape); //make sure to initalize m_transform and m_shape
		virtual ~Actor() {}

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		Transform& GetTransform(); //return the transform
		Shape& GetShape(); //return the shape

	protected:
		Transform m_transform;
		Shape m_shape;
	};
}