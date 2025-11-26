
#pragma once
#include <godot_cpp/classes/node2d.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/sprite2d.hpp>
#include "balloon.h"

namespace godot {

class BalloonManager : public Node2D {
	GDCLASS(BalloonManager, Node2D)

private:
	godot::TypedArray<Balloon> mBalloons;
	double time_passed;
	Ref<RandomNumberGenerator> mRng;

protected:
	static void _bind_methods();

public:
	BalloonManager();
	~BalloonManager();

	void _process(double delta) override;
	void _ready() override;
};
}; //namespace godot
