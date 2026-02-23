#pragma once
#include "levelManager.h"
#include <godot_cpp/classes/animated_sprite2d.hpp>
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>

namespace godot {

class Balloon : public AnimatedSprite2D {
	GDCLASS(Balloon, AnimatedSprite2D)

private:
	float floatSpeed;
	Area2D *area = nullptr;
	CollisionShape2D *shape = nullptr;
	AudioStreamPlayer *sound = nullptr;
	Ref<RandomNumberGenerator> mRng;
	Ref<Texture2D> tex = nullptr;
	bool isPopped = false;

protected:
	static void _bind_methods();

public:
	Balloon();
	~Balloon();

	void _process(double delta) override;
	void _ready() override;
	void _input(const Ref<InputEvent> &p_event) override;

	float getSpeed();
	void setSpeed(float speed);
	void setPopped(bool hasPopped);
	bool hasPopped();
	AudioStreamPlayer *getSound();
	void onAnimationFinished();
	void handleMouseEntered(Area2D *other_area);
	void handleBalloonClicked(Node *viewport, Ref<InputEvent> event, int shape_idx);
};
}; //namespace godot