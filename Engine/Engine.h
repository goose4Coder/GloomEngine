#ifndef GLOOM_ENGINE_H
#define GLOOM_ENGINE_H

#include <iostream>
#include <map>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include "Nodes/Node.h"
#include "Graphics/Graphics.h"

class GloomEngine {
	public:
	GloomEngine(int fps, float displayWidth,float displayHeight){
		this->FPS=fps;
		this->DISPLAY_HEIGHT=displayHeight;
		this->DISPLAY_WIDTH=displayWidth;
	};
	void Init();
	int RunGame();
	inline void ChangeScene(int sceneNum){
		this->sceneToChange=sceneNum;
	};
	inline void RegisterScene(BaseNodes::Scene scene){
		scene.SetCamera(BaseNodes::Camera(0, 0, 1000, 1.2,740));
		this->scenes.push_back(scene);
	};

	protected:

	int FPS = 60;
	float DISPLAY_WIDTH = 740;
	float DISPLAY_HEIGHT = 480;
	bool notExitGame = true;
	int sceneToChange=-2;
	std::vector<BaseNodes::Scene> scenes = std::vector<BaseNodes::Scene>();
	
	BaseNodes::Scene currentScene = BaseNodes::Scene();
	
	//int RunGame(int argc, char** argv);


};

void OnGameStart(GloomEngine &game);

#endif