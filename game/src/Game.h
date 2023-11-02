#pragma once

#include <Zewada.h>
#include "Gamelayer.h"

using namespace Zewada;

namespace Game {
	class Game : public Zewada::Application
	{
	private:
		GameLayer* m_gameLayer;
	public:
		Game(const ApplicationSpecs& settings);
	};
}

