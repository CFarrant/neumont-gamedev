#include "Game.h"
#include "Actors/Player.h"
#include "Actors/Enemy.h"
#include "Actors/Locator.h"
#include "Actors/Projectile.h"
#include "Graphics/ParticleSystem.h"
#include "Audio/AudioSystem.h"
#include "Math/Random.h"
#include "Math/Transform.h"
#include "Math/Color.h"
#include "Math/Math.h"
#include "Graphics/Shape.h"
#include <string>
#include <list>

void Game::Startup()
{
	g_audioSystem.Startup();
	g_particleSystem.Startup();
	m_scene.Startup();
	m_scene.SetGame(this);
}

void Game::Shutdown()
{
	m_scene.Shutdown();
	g_particleSystem.Shutdown();
	g_audioSystem.Shutdown();
}

bool Game::Update(float dt)
{
	m_frameTime = dt;

	bool quit = Core::Input::IsPressed(Core::Input::KEY_ESCAPE);

	switch (m_state)
	{
	case Game::eState::INIT:
		g_audioSystem.AddAudio("Laser", "Laser.wav");
		g_audioSystem.AddAudio("Explosion", "Explosion.wav");
		g_audioSystem.AddAudio("Coin", "Coin.wav");
		g_audioSystem.AddAudio("GameOver", "GameOver.wav");
		m_state = eState::TITLE;
		break;
	case Game::eState::TITLE:
		if (Core::Input::IsPressed(VK_SPACE))
		{
			g_audioSystem.PlayAudio("Coin");
			m_state = eState::START_GAME;
			m_score = 0;
			m_lives = 3;
		}
		break;
	case Game::eState::START_GAME:
		{
			nc::Actor* player = new Player();
			player->Load("player.actor");

			Locator* locator = new Locator();
			locator->GetTransform().position = nc::Vector2D{ 0, 2 };
			player->AddChild(locator);

			m_scene.AddActor(player);

			for (int i = 0; i < 5; i++)
			{
				nc::Actor* enemy = new Enemy();

				std::vector<std::string> enemies = { "enemy_one.actor", "enemy_two.actor" };
				std::string randEnemy = enemies[rand() % 2];

				enemy->Load(randEnemy);

				dynamic_cast<Enemy*>(enemy)->SetTarget(player);

				float distance = nc::Random(300, 600);
				float angle = nc::Random(0, nc::TWO_PI);
				nc::Vector2D position = nc::Vector2D::Rotate(nc::Vector2D{ distance, 0.0f }, angle);

				dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
				enemy->GetTransform().position = nc::Vector2D{400, 300} + position;
				m_scene.AddActor(enemy);
			}
			m_state = eState::GAME;
		}
		break;
	case Game::eState::PLAYER_DEAD:
		{
			m_lives -= 1;
			m_state = (m_lives == 0) ? eState::GAME_OVER : eState::GAME_WAIT;
			m_stateTimer = 3.0f;
		}
		if (m_state == eState::GAME_OVER) {
			g_audioSystem.PlayAudio("GameOver");
		}
		break;
	case Game::eState::GAME:
		m_spawnTimer += dt;
		if (m_spawnTimer >= 3)
		{
			m_spawnTimer = 0.0f;
			nc::Actor* enemy = new Enemy();

			std::vector<std::string> enemies = { "enemy_one.actor", "enemy_two.actor" };
			std::string randEnemy = enemies[rand() % 2];

			enemy->Load(randEnemy);
			dynamic_cast<Enemy*>(enemy)->SetTarget(m_scene.GetActor<Player>());
			dynamic_cast<Enemy*>(enemy)->SetThrust(nc::Random(50, 100));
			enemy->GetTransform().position = nc::Vector2D{ nc::Random(0,800), nc::Random(0,600) };
			m_scene.AddActor(enemy);
		}
		if (Core::Input::IsPressed('P')) {
			m_state = eState::GAME_PAUSED;
		}
		break;
	case Game::eState::GAME_PAUSED:
		if (Core::Input::IsPressed('P')) {
			m_state = eState::GAME;
		}
		break;
	case Game::eState::GAME_WAIT:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::START_GAME;
		}
		break;
	case Game::eState::GAME_OVER:
		m_stateTimer -= dt;
		if (m_stateTimer <= 0)
		{
			m_scene.RemoveAllActors();
			m_state = eState::TITLE;
		}
		if (m_score > m_highScore) {
			m_highScore = m_score;
		}
		break;
	default:
		break;
	}

	/*if (Core::Input::IsPressed(Core::Input::BUTTON_LEFT))
	{
		int x, y;
		Core::Input::GetMousePos(x, y);

		nc::Color colors[] = { nc::Color::white, nc::Color::red, nc::Color::yellow, nc::Color::orange };
		nc::Color color = colors[rand() % 4];

		g_particleSystem.Create(nc::Vector2D{x, y}, 0, 180, 30, color, 1, 100, 200);
	}*/

	if (m_state != eState::GAME_PAUSED) {
		m_scene.Update(dt);
	}
	g_particleSystem.Update(dt);
	g_audioSystem.Update(dt);

	return quit;
}

void Game::Draw(Core::Graphics & graphics)
{

	graphics.SetColor(nc::Color::white);
	graphics.DrawString(10, 10, std::to_string(static_cast<unsigned int>(1.0f / m_frameTime)).c_str());

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
	case Game::eState::PLAYER_DEAD:
		break;
	case Game::eState::GAME:
		break;
	case Game::eState::GAME_WAIT:
		break;
	case Game::eState::GAME_PAUSED:
		{
			nc::Color colors[] = { nc::Color::red, nc::Color::yellow, nc::Color::orange };
			nc::Color color = colors[rand() % 3];
			graphics.SetColor(color);
			graphics.DrawString(375, 275, "PAUSED!");
		}
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

	if (m_state != eState::TITLE && m_state != eState::INIT)
	{
		graphics.SetColor(nc::Color::white);
		graphics.DrawString(700, 10, std::to_string(m_score).c_str());
		graphics.DrawString(700, 20, ("LIVES: " + std::to_string(m_lives)).c_str());
		if (m_highScore > 0) {
			graphics.DrawString(360, 10, ("HIGH SCORE: " + std::to_string(m_highScore)).c_str());
		}
	}

	m_scene.Draw(graphics);
}
