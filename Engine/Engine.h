#ifndef GLOOM_ENGINE_H
#define GLOOM_ENGINE_H

#include <iostream>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Nodes/Node.h"
#include "Graphics/Graphics.h"

namespace GloomEngine {


	const int FPS = 60;
	const float DISPLAY_WIDTH = 740;
	const float DISPLAY_HEIGHT = 480;
	bool notExitGame = true;
	BaseNodes::Scene currentScene = BaseNodes::Scene();

	void Init();
	int RunGame();
	//int RunGame(int argc, char** argv);


};

#endif