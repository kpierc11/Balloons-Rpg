#include "balloonManager.h"
#include <godot_cpp/classes/circle_shape2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/viewport.hpp>

using namespace godot;

void godot::BalloonManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setBalloonAmount", "balloonAmount"), &BalloonManager::setBalloonAmount);
	ClassDB::bind_method(D_METHOD("getBalloonAmount"), &BalloonManager::getBalloonAmount);

	// Register property so it shows in the inspector & scripts
	ADD_PROPERTY(PropertyInfo(Variant::INT, "balloonAmount"), "setBalloonAmount", "getBalloonAmount");
}

godot::BalloonManager::BalloonManager() {
	balloonAmount = 10;
}

godot::BalloonManager::~BalloonManager() {
}

void godot::BalloonManager::_ready() {
	//Add mouse area
	mouseArea = memnew(Area2D);
	mouseArea->set_name("mouseArea");
	add_child(mouseArea);

	mouseArea->set_collision_layer(5);
	mouseArea->set_collision_mask(5);
	mouseArea->set_pickable(1);
	mouseArea->set_process_input(1);

	shape = memnew(CollisionShape2D);
	shape->set_name("CollisionShape2D");
	mouseArea->add_child(shape);

	//set signal for mouse enter
	//mouseArea->connect("mouse_entered", Callable(this, "handleMouseEntered"));

	// Create default shape so it's visible
	Ref<CircleShape2D> circle;
	circle.instantiate();
	circle->set_radius(20);
	shape->set_shape(circle);
	shape->set_position({ 0.0f, -5.0f });

	mRng.instantiate();
	mRng->randomize();

	Vector2 windowSize = DisplayServer::get_singleton()->window_get_size();
	Viewport *vp = get_viewport();
	Rect2 vpRect = vp->get_visible_rect();
	Vector2 vpSize = vpRect.size;

	for (int i = 0; i < balloonAmount; i++) {
		float ranBalloonPos = mRng->randf_range(0.0f ,500.0f);
		float ranBalloonFloatSpeed = mRng->randf_range(20.0f, 100.0f);
		float speed = ranBalloonFloatSpeed;

		Balloon *balloon = memnew(Balloon);
		balloon->set_position(Vector2(ranBalloonPos, windowSize.height + 10.0f));
		balloon->setSpeed(ranBalloonFloatSpeed);
		//balloon->set_visible(false);

		add_child(balloon);
		mBalloons.push_back(balloon);
	}
}

int godot::BalloonManager::getBalloonAmount() {
	return balloonAmount;
}

void godot::BalloonManager::setBalloonAmount(int balloonCount) {
	balloonAmount = balloonCount;
}

void godot::BalloonManager::createBalloon() {
	Vector2 windowSize = DisplayServer::get_singleton()->window_get_size();

	for (int i = 0; i < 10; i++) {
		Balloon *balloon = Object::cast_to<Balloon>(mBalloons[i]);

		if (!balloon->is_visible()) {
			float ranBalloonPos = mRng->randf_range(-300.0f, 250.0f);
			float ranBalloonFloatSpeed = mRng->randf_range(20.0f, 100.0f);
			float speed = ranBalloonFloatSpeed;

			balloon->set_position(Vector2(ranBalloonPos, windowSize.height + 10.0f));
			balloon->setSpeed(ranBalloonFloatSpeed);
			balloon->set_visible(1);
		}
	}
}

void godot::BalloonManager::_process(double delta) {
	//set mouse area position to the mouse location
	float mouseX = get_local_mouse_position().x;
	float mouseY = get_local_mouse_position().y;
	shape->set_position({ mouseX, mouseY });

	time_passed += delta;

	float amplitude = 50.0f;
	float frequency = 1.5f;

	for (int i = 0; i < mBalloons.size(); i++) {
		Balloon *balloon = Object::cast_to<Balloon>(mBalloons[i]);

		
			//print_line("balloon rendered");
			//balloon->set_visible(true);
			Vector2 newPosition;
			newPosition.x = balloon->get_position().x + cos(time_passed * frequency);
			newPosition.y = balloon->get_position().y + (balloon->getSpeed() * delta) * -1;
			balloon->set_position(newPosition);
		
	}
}
