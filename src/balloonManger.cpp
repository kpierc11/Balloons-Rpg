#include "balloonManager.h"
#include <godot_cpp/classes/circle_shape2d.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/display_server.hpp>
#include <godot_cpp/classes/resource_loader.hpp>
#include <godot_cpp/classes/viewport.hpp>

using namespace godot;

void godot::BalloonManager::_bind_methods() {
	ClassDB::bind_method(D_METHOD("setBalloonAmount", "balloonAmount"), &BalloonManager::setBalloonAmount);
	ClassDB::bind_method(D_METHOD("popAllBalloons"), &BalloonManager::popAllBalloons);
	ClassDB::bind_method(D_METHOD("getBalloonAmount"), &BalloonManager::getBalloonAmount);
	ClassDB::bind_method(D_METHOD("setBalloonData"), &BalloonManager::setBalloonData);
	ClassDB::bind_method(D_METHOD("getBalloonData"), &BalloonManager::getBalloonData);
	ClassDB::bind_method(D_METHOD("handleBalloonPopped"), &BalloonManager::handleBalloonPopped);

	// Register property so it shows in the inspector & scripts
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Amount of Balloons"), "setBalloonAmount", "getBalloonAmount");
	ADD_PROPERTY(
			PropertyInfo(
					Variant::ARRAY,
					"balloonData",
					PROPERTY_HINT_TYPE_STRING,
					String::num(Variant::OBJECT) + "/" + String::num(PROPERTY_HINT_RESOURCE_TYPE) + ":BalloonData"),
			"setBalloonData",
			"getBalloonData");

	ADD_SIGNAL(MethodInfo("balloon_popped", PropertyInfo(Variant::INT, "points")));
}

godot::BalloonManager::BalloonManager() {
	balloonAmount = 10;
	numBalloonsPopped = 0;
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
		float ranBalloonPos = mRng->randf_range(0.0f, vpRect.size.x);
		float ranBalloonFloatSpeed = mRng->randf_range(20.0f, 100.0f);
		float speed = ranBalloonFloatSpeed;
		Ref<BalloonData> data = balloonData[mRng->randi_range(0, balloonData.size() - 1)];
		Ref<SpriteFrames> frames = data->getSpriteFrames();

		Balloon *balloon = memnew(Balloon);
		balloon->set_position(Vector2(ranBalloonPos, vpRect.size.y + 100.0f));
		balloon->setSpeed(ranBalloonFloatSpeed);
		balloon->set_sprite_frames(frames);
		balloon->connect("popped", Callable(this, "handleBalloonPopped"));
		//balloon->setAnimationName(data->getAnimName());
		//balloon->set_visible(false);

		add_child(balloon);
		mBalloons.push_back(balloon);
	}

	//Setup level manager
	lvlManager = get_node<LevelManager>("/root/Main/CanvasLayer/LevelManager");

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

void godot::BalloonManager::setBalloonData(const godot::TypedArray<BalloonData> &p_array) {
	balloonData = p_array;
}

godot::TypedArray<BalloonData> godot::BalloonManager::getBalloonData() const {
	return godot::TypedArray<BalloonData>();
}

void godot::BalloonManager::popAllBalloons() {
	for (int i = 0; i < mBalloons.size(); i++) {
		Balloon *balloon = Object::cast_to<Balloon>(mBalloons[i]);
		balloon->play("pop");
		balloon->getSound()->play();
	}
}

void godot::BalloonManager::handleBalloonPopped(int points) {
	emit_signal("balloon_popped", points);
	numBalloonsPopped += 1;

	if (numBalloonsPopped == lvlManager->get_current_level() * 10) {
		int level = lvlManager->get_current_level();
		lvlManager->set_current_level(level += 1);
		lvlManager->emit_signal("level_updated");
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

	Viewport *vp = get_viewport();
	Rect2 vpRect = vp->get_visible_rect();
	Vector2 vpSize = vpRect.size;

	for (int i = 0; i < lvlManager->get_current_level() * 10; i++) {
		Balloon *balloon = Object::cast_to<Balloon>(mBalloons[i]);

		if (balloon->is_visible()) {
			//print_line("balloon rendered");
			//balloon->set_visible(true);
			Vector2 newPosition;
			newPosition.x = balloon->get_position().x + cos(time_passed * frequency);
			newPosition.y = balloon->get_position().y + (balloon->getSpeed() * delta) * -1;

			if (newPosition.x > vpRect.size.x - 10 || newPosition.x < 10) 
			{
				newPosition.x = balloon->get_position().x - cos((time_passed * frequency) * -1);
			}

			balloon->set_position(newPosition);
		}
	}
}
