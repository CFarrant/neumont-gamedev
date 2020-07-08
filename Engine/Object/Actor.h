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
		~Actor() {}

		bool Load(const std::string& filename);

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		Transform& GetTransform(); //return the transform
		Shape& GetShape(); //return the shape
	private:
		Transform m_transform;
		Shape m_shape;
	};
}