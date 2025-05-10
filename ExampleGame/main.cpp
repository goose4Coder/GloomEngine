#include "../Engine/Engine.h"
const int FPS = 60;
const float DISPLAY_WIDTH = 740;
const float DISPLAY_HEIGHT = 480;





class Player: public BaseNodes::Entity {
public:
	Player(float x, float y) : BaseNodes::Entity(x, y) {
		
	};
	Player() : BaseNodes::Entity(6,6) {

	};
protected:
	void Update(ALLEGRO_KEYBOARD_STATE keyState, std::vector<std::shared_ptr<Entity>> entities, Entity& camera, std::vector<std::shared_ptr<Entity>> env) override{
		if (al_key_down(&keyState, ALLEGRO_KEY_W)) {
			this->MoveBy(0.1,0);
			std::cout << "wwwwwwwwwww" << std::endl;
		}
		else if (al_key_down(&keyState, ALLEGRO_KEY_S)) {
			this->MoveBy(-0.1, 0);
		}
		else {
			std::cout << "no butt" << std::endl;
		}
		camera.Move(this->coordinates.x, this->coordinates.y);
	};
};

void OnGameStart(GloomEngine &game){
	auto scene = BaseNodes::Scene(std::string("main"),
	std::array<std::array<int,11>,11>{
		std::array<int,11>{0,0,0,0,0,0,0,0,0,0,0},
		std::array<int,11>{0,0,0,0,0,0,0,0,0,0,0},
		std::array<int,11>{0,0,0,0,0,0,0,0,0,0,0},
		std::array<int,11>{0,1,0,1,1,1,1,1,1,0,0},
		std::array<int,11>{0,1,0,0,0,0,0,0,1,0,0},
		std::array<int,11>{0,1,0,0,0,0,0,0,1,0,0},
		std::array<int,11>{0,1,0,0,0,0,0,0,1,0,0},
		std::array<int,11>{0,1,1,1,1,1,1,1,1,0,0},
		std::array<int,11>{0,0,0,0,0,0,0,0,0,0,0},
		std::array<int,11>{0,0,0,0,0,0,0,0,0,0,0},
		std::array<int,11>{0,0,0,0,0,0,0,0,0,0,0},
	}
	);
	auto a = std::shared_ptr<BaseNodes::Entity>(new Graphics::BaseWallDrawer());
	auto p = std::shared_ptr<BaseNodes::Entity>(new Player(6, 6));
	scene.AppendEnv(a);
	scene.AppendEntity(p);
	scene.SetCamera(BaseNodes::Camera(0, 0, 7, 1.35, DISPLAY_WIDTH));
	game.RegisterScene(scene);
}

int main(int argc, char** argv) {
	auto engine = GloomEngine(FPS,DISPLAY_WIDTH,DISPLAY_HEIGHT);
	return engine.RunGame();
}