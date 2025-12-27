#pragma once
#include <godot_cpp/classes/area2d.hpp>
#include <godot_cpp/classes/audio_stream_player.hpp>
#include <godot_cpp/classes/collision_shape2d.hpp>
#include <godot_cpp/classes/input_event.hpp>
#include <godot_cpp/classes/random_number_generator.hpp>
#include <godot_cpp/classes/sprite2d.hpp>

namespace godot {

class Balloon : public Sprite2D {
	GDCLASS(Balloon, Sprite2D)

private:
	float floatSpeed;
	Area2D *area = nullptr;
	CollisionShape2D *shape = nullptr;
	AudioStreamPlayer *sound = nullptr;
	Ref<RandomNumberGenerator> mRng;
	Ref<Texture2D> tex = nullptr;

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
	void handleMouseEntered(Area2D *other_area);
	void handleBalloonClicked(Node *viewport, Ref<InputEvent> event, int shape_idx);
};
}; //namespace godot