#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Graphics/Shape.h"
#include <string>
#include <list>

void Game::Startup()
{
	//g_audioSystem.Startup();
	g_particleSystem.Startup();
	m_scene.Startup();
	m_scene.SetGame(this);
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
	//g_audioSystem.Shutdown();
}

bool Game::Update(float dt)
{
	m_frameTime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::START_GAME:
		{
			nc::Actor* player = new Player();
			player->Load("player.actor");
			m_scene.AddActor(player);

			for (int i = 0; i < 5; i++)
			{
				nc::Actor* enemy = new Enemy();
				enemy->Load("enemy.actor");
				dynamic_cast<Enemy*>(enemy)->SetTarget(player);
				dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
				enemy->GetTransform().position = nc::Vector2D{ nc::Random(0,800), nc::Random(0,600) };
				m_scene.AddActor(enemy);
			}
			m_state = eState::GAME;
		}
		break;
	case Game::eState::GAME:
		m_spawnTimer += dt;
		if (m_spawnTimer >= 3)
		{
			m_spawnTimer = 0.0f;
			nc::Actor* enemy = new Enemy();
			enemy->Load("enemy.actor");
			dynamic_cast<Enemy*>(enemy)->SetTarget(m_scene.GetActor<Player>());
			dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
			enemy->GetTransform().position = nc::Vector2D{ nc::Random(0,800), nc::Random(0,600) };
			m_scene.AddActor(enemy);
		}
		m_scene.Update(dt);
		break;
	case Game::eState::GAME_OVER:
		break;
	default:
		break;
	}

	if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::yellow, nc::Color::orange };
		nc::Color color = colors[rand() % 4];

		g_particleSystem.Create(nc::Vector2D{x, y}, 0, 180, 30, color, 1, 100, 200);
	}

	g_particleSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics & graphics)
{

	graphics.SetColor(nc::Color{ 1,1,1 });
	graphics.DrawString(10, 10, std::to_string(m_frameTime).c_str());
	graphics.DrawString(10, 20, std::to_string(1.0f / m_frameTime).c_str());

	g_particleSystem.Draw(graphics);

	switch (m_state)
	{
	case Game::eState::INIT:
		break;
	case Game::eState::TITLE:
		{
			nc::Color colors[] = { nc::Color::red, nc::Color::yellow, nc::Color::orange };
			nc::Color color = colors[rand() % 3];
			graphics.SetColor(color);
			graphics.DrawString(375, 275, "VECTOROIDS");
		}
		break;
	case Game::eState::START_GAME:
		break;
	case Game::eState::GAME:
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 10, std::to_string(m_score).c_str());
		m_scene.Draw(graphics);
		break;
	case Game::eState::GAME_OVER:
		{
			nc::Color colors[] = { nc::Color::red, nc::Color::yellow, nc::Color::orange };
			nc::Color color = colors[rand() % 3];
			graphics.SetColor(color);
			graphics.DrawString(375, 275, "GAME OVER!");
		}
		break;
	default:
		break;
	}
}
