#include "balloon.h"
#include <godot_cpp/classes/audio_stream.hpp>
#include <godot_cpp/classes/circle_shape2d.hpp>
#include <godot_cpp/classes/input.hpp>
#include <godot_cpp/classes/input_event_mouse.hpp>
#include <godot_cpp/classes/input_event_mouse_button.hpp>
#include <godot_cpp/classes/resource_loader.hpp>

void godot::Balloon::_bind_methods() {
	ClassDB::bind_method(D_METHOD("getSpeed"), &Balloon::getSpeed);
	ClassDB::bind_method(D_METHOD("setSpeed", "speed"), &Balloon::setSpeed);
	ClassDB::bind_method(D_METHOD("handleMouseEntered"), &Balloon::handleMouseEntered);
	ClassDB::bind_method(D_METHOD("handleBalloonClicked", "viewport", "event", "shape_idx"), &Balloon::handleBalloonClicked);

	// Register property so it shows in the inspector & scripts
	ADD_PROPERTY(PropertyInfo(Variant::FLOAT, "speed"), "setSpeed", "getSpeed");
}

godot::Balloon::Balloon() {
	
}

godot::Balloon::~Balloon() {
}

void godot::Balloon::_process(double delta) {
}

void godot::Balloon::_ready() {
	mRng.instantiate();
	mRng->randomize();

	//setup audio
	// --- SETUP AUDIO ---
	sound = memnew(AudioStreamPlayer);
	sound->set_name("PopSound");
	add_child(sound);

	//Load a sound file (.ogg, .wav, etc.)
	Ref<AudioStream> stream = ResourceLoader::get_singleton()->load("res://assets/sounds/balloonPop.mp3");

	if (stream->get_length() > 0) {
		sound->set_stream(stream);
	} else {
		print_line("couldn't load sound file");
	}

	// Optional: volume or pitch
	sound->set_volume_db(-15.0f);

	float randomPitch = mRng->randf_range(1.0f, 2.0f);
	sound->set_pitch_scale(randomPitch);

	area = memnew(Area2D);
	area->set_name("Area2D");
	add_child(area);

	area->set_collision_layer(5);
	area->set_collision_mask(5);
	area->set_pickable(1);
	area->set_process_input(1);
	area->set_monitoring(1);
	area->set_monitorable(1);

	//set signal for mouse enter
	area->connect("area_entered", Callable(this, "handleMouseEntered"));
	//area->connect("input_event", Callable(this, "handleBalloonClicked"));

	shape = memnew(CollisionShape2D);
	shape->set_name("CollisionShape2D");
	area->add_child(shape);

	// Create default shape so it's visible
	Ref<CircleShape2D> circle;
	circle.instantiate();
	circle->set_radius(12);
	shape->set_shape(circle);
	shape->set_position({ 0.0f, -5.0f });

	//set texture for balloon
	tex = ResourceLoader::get_singleton()->load("res://assets/sprites/blue-balloon.png");
	set_texture(tex);
}

void godot::Balloon::_input(const Ref<InputEvent> &p_event) {
}

float godot::Balloon::getSpeed() {
	return floatSpeed;
}

void godot::Balloon::setSpeed(float speed) {
	floatSpeed = speed;
}

void godot::Balloon::handleMouseEntered(Area2D *other_area) {
	if (other_area->get_name().contains("mouseArea") && is_visible()) {
		set_visible(false);
		area->set_deferred("monitoring", false);
		sound->play();
	}
}

void godot::Balloon::handleBalloonClicked(Node *viewport, Ref<InputEvent> event, int shape_idx) {
	if (event.is_valid() && event->is_class("InputEventMouseButton")) {
		Ref<InputEventMouseButton> mb = event;
		if (mb->is_pressed() && mb->get_button_index() == MouseButton::MOUSE_BUTTON_LEFT) {
			sound->play();
			set_visible(false);
		}
	}
}
