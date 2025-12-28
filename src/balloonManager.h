
#pragma once
#include "balloon.h"
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class BalloonManager : public Node2D {
	GDCLASS(BalloonManager, Node2D)

private:
	godot::TypedArray<Balloon> mBalloons;
	double time_passed;
	Ref<RandomNumberGenerator> mRng;
	int balloonAmount;
	Area2D *mouseArea;
	CollisionShape2D *shape;
	int score;
	Array balloonSprites; 

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
	void setBalloonSprites(const Array &p_array);
	Array getBalloonSprites() const;
};
}; //namespace godot
