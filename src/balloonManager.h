
#pragma once
#include "balloon.h"
#include "balloonData.h"
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class BalloonManager : public Node2D {
	GDCLASS(BalloonManager, Node2D)

private:
	godot::TypedArray<Balloon> mBalloons;
	Ref<RandomNumberGenerator> mRng;
	Area2D *mouseArea;
	CollisionShape2D *shape;
	godot::TypedArray<BalloonData> balloonData;
	double time_passed;
	int balloonAmount;
	int numBalloonsPopped;
	LevelManager *lvlManager;

protected:
	static void _bind_methods();

public:
	BalloonManager();
	~BalloonManager();

	void _process(double delta) override;
	void _ready() override;
	int getBalloonAmount();
	void setBalloonAmount(int balloonCount);
	void createBalloon();
	void setBalloonData(const godot::TypedArray<BalloonData> &p_array);
	godot::TypedArray<BalloonData> getBalloonData() const;
	void popAllBalloons();
	void handleBalloonPopped(int points);
};
}; //namespace godot
