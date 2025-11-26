#include "balloonManager.h"
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

using namespace godot;

void godot::BalloonManager::_bind_methods() {
}

godot::BalloonManager::BalloonManager() {
}

godot::BalloonManager::~BalloonManager() {
}

void godot::BalloonManager::_ready() {
	mRng.instantiate();
	mRng->randomize();

	Vector2 window_size = DisplayServer::get_singleton()->window_get_size();

	for (int i = 0; i < 10; i++) {
		Ref<Texture2D> tex = ResourceLoader::get_singleton()->load("res://red-balloon.png");
		Vector2 scale = Vector2(100 / tex->get_size().x, 100 / tex->get_size().y);

		print_line(window_size.width);
		float ranBalloonPos = mRng->randf_range(0.0f, window_size.width);
		//float ranBalloonPosY = mRng->randf_range(0.0f, window_size.width);

		float ranBalloonFloatSpeed = mRng->randf_range(80.0f, 300.0f);
		float speed = ranBalloonFloatSpeed;

		Balloon *balloon = memnew(Balloon);
		balloon->set_position(Vector2(ranBalloonPos, window_size.height + 300.0f));
		balloon->set_scale(scale);
		balloon->set_texture(tex);

		balloon->setSpeed(ranBalloonFloatSpeed);

		add_child(balloon);

		mBalloons.push_back(balloon);
	}
}

void godot::BalloonManager::_process(double delta) {
	time_passed += delta;

	float amplitude = 2.0f;
	float frequency = 2.0f;

	for (int i = 0; i < mBalloons.size(); i++) {
		Balloon *balloon = Object::cast_to<Balloon>(mBalloons[i]);

		// Compute new position relative to start
		Vector2 newPosition;
		newPosition.x = balloon->get_position().x + cos(time_passed * frequency);

		newPosition.y = balloon->get_position().y + (balloon->getSpeed() * delta) * - 1;

		// Apply new position to the sprite
		balloon->set_position(newPosition);
	}
}
