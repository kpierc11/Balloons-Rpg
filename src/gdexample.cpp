#include "gdexample.h"
#include <godot_cpp/core/class_db.hpp>

using namespace godot;

void GDExample::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &GDExample::get_speed);
	ClassDB::bind_method(D_METHOD("set_speed", "p_speed"), &GDExample::set_speed);
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed", PROPERTY_HINT_RANGE, "0,20,0.01"), "set_speed", "get_speed");
}

GDExample::GDExample() {
	// Initialize any variables here.
	time_passed = 0.0;

	// for (int i = 0; i < 10; i++) {
	// 	Sprite2D sprite;
	// 	mBalloons.push_back(&sprite);
	// }
}

GDExample::~GDExample() {
	// Add your cleanup here.
}

void GDExample::_process(double delta) {
	time_passed += delta;

	float amplitude = 20.0f;
	float speed = 10.0f;

	Vector2 newPosition = Vector2(10.0f + cos(time_passed * speed) * amplitude, (-10.0f * time_passed) * 30.0f);

	set_position(newPosition);
}

void godot::GDExample::set_speed(const double p_speed) {
	speed = p_speed;
}

double godot::GDExample::get_speed() const {
	return speed;
}
