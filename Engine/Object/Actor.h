#pragma once
#include "../Graphics/Shape.h"
#include "../Math/Transform.h"

namespace nc
{
	class Scene;

	class Actor
	{
	public:
		enum class eType
		{
			PLAYER,
			ENEMY,
			PROJECTILE,
			LOCATOR
		};

	public:
		Actor();
		Actor(const Transform& transform, const Shape& shape); //make sure to initalize m_transform and m_shape
		virtual ~Actor() {}

		virtual void Destroy();

		virtual eType GetType() = 0;

		virtual bool Load(const std::string& filename);
		virtual void Load(std::istream& stream);

		virtual void Update(float dt);
		virtual void Draw(Core::Graphics& graphics);

		virtual void OnCollision(Actor* actor) {}

		float GetRadius();

		void SetScene(Scene* scene) { m_scene = scene; }
		Transform& GetTransform(); //return the transform
		Shape& GetShape(); //return the shape
		void SetDestroy(bool destroy = true) { m_destroy = destroy; };
		bool IsDestroyed() { return m_destroy; }

		void AddChild(Actor* child);
		Actor* GetParent() { return m_parent; }

	protected:
		bool m_destroy{ false };
		Scene* m_scene { nullptr };
		Transform m_transform;
		Shape m_shape;

		std::vector<Actor*> m_children;
		Actor* m_parent{ nullptr };
	};
}