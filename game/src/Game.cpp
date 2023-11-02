#include <zpch.h>
#include "Game.h"

namespace Game
{
#define BIND_EVENT_FN(x) std::bind(&Game::Game::x, this, std::placeholders::_1)

	Game::Game(const ApplicationSpecs& settings)
		: Application(settings), m_gameLayer(new GameLayer(this))
	{
		PushLayer(m_gameLayer);
		m_gameLayer->SetEventCallback(BIND_EVENT_FN(OnEvent));
	}
}