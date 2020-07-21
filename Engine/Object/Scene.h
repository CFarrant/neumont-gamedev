#pragma once
#include "core.h"
#include <list>

namespace nc
{
	class Scene
	{
	public:
		void Startup();
		void Shutdown();

		void Update(float dt);
		void Draw(Core::Graphics& graphics);

		void AddActor(class Actor* actor);
		void RemoveActor(class Actor* actor);

		template <typename T>


	private:
		std::list<class Actor*> m_actors;
	};
}