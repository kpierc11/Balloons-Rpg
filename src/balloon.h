#pragma once
#include <godot_cpp/classes/sprite2d.hpp>
#include <godot_cpp/classes/area2D.hpp>

namespace godot {

class Balloon : public Sprite2D {
	GDCLASS(Balloon, Sprite2D)

private:
	float floatSpeed;

protected:
	static void _bind_methods();

public:
	Balloon();
	~Balloon();

	void _process(double delta) override;
	void _ready() override;

	float getSpeed();
	void setSpeed(float speed);
};
};