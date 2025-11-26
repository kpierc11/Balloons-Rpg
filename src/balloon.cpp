#include "balloon.h"

void godot::Balloon::_bind_methods() {
	ClassDB::bind_method(D_METHOD("get_speed"), &Balloon::getSpeed);
	ClassDB::bind_method(D_METHOD("set_speed", "speed"), &Balloon::setSpeed);

	// Register property so it shows in the inspector & scripts
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "set_speed", "get_speed");
}

godot::Balloon::Balloon() {
}

godot::Balloon::~Balloon() {
}

void godot::Balloon::_process(double delta) {
}

void godot::Balloon::_ready() {
}

float godot::Balloon::getSpeed() {
	return floatSpeed;
}

void godot::Balloon::setSpeed(float speed) {
	floatSpeed = speed;
}
