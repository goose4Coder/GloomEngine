#include "../Engine/Engine.h"

const int FPS = 60;
const float DISPLAY_WIDTH = 740;
const float DISPLAY_HEIGHT = 480;

class MovingCircle: public Graphics::CircleDrawer{
	public:
	MovingCircle(float x,float y): CircleDrawer(x,y){}
	void Update() override{
		if (forward){
			this->MoveBy(0, -0.5);
		}else{
			this->MoveBy(0, 0.5);
		}
		
		if (this->coordinates.y>100){
			forward=true;
		}
		if (this->coordinates.y<5){
			forward=false;
		}
	}
	protected:
	bool forward=true;
};

class MovingRect : public Graphics::RectangleDrawer {
public:
	MovingRect(float x, float y) : RectangleDrawer(x, y) {}
	void Update() override {
		if (forward) {
			this->MoveBy(0, -0.5);
		}
		else {
			this->MoveBy(0, 0.5);
		}

		if (this->coordinates.y > 100) {
			forward = true;
		}
		if (this->coordinates.y < 5) {
			forward = false;
		}
	}
protected:
	bool forward = true;
};

void OnGameStart(GloomEngine &game){
	auto scene = BaseNodes::Scene("main");
	/*auto a = std::shared_ptr<BaseNodes::Node>(new MovingCircle(0.1,70));*/
	auto a = std::shared_ptr<BaseNodes::Node>(new MovingRect(0.1, 55));
	auto b = std::shared_ptr<BaseNodes::Node>(new MovingRect(20, 70));
	auto c = std::shared_ptr<BaseNodes::Node>(new MovingRect(-20,70));
	scene.AppendChild(a);
	scene.AppendChild(b);
	scene.AppendChild(c);
	game.RegisterScene(scene);
}

int main(int argc, char** argv) {
	auto engine = GloomEngine(FPS,DISPLAY_WIDTH,DISPLAY_HEIGHT);
	return engine.RunGame();
}