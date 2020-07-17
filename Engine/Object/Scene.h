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
		Actor* GetActor() {
			nc::Actor* result{ nullptr };

			for (nc::Actor* actor : m_actors)
			{
				result = dynamic_cast<T*>(actor);
				if (result) { break; }
			}

			return result;
		}

		template <typename T>
		std::vector<Actor*> GetActors() {
			std::vector<nc::Actor*> results;

			for (nc::Actor* actor : m_actors)
			{
				T* result = dynamic_cast<T*>(actor);
				if (result) { results.push_back(result); }
			}

			return results;
		}

	private:
		std::list<class Actor*> m_actors;
	};
}