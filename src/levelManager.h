#pragma once

#include <godot_cpp/classes/node.hpp>

namespace godot {

class LevelManager : public Node {
	GDCLASS(LevelManager, Node)

private:
	int score;
	int currentLevel;
	enum class LevelType {
		NORMAL,
		BONUS,
		CRAZY,
	};
	enum class BalloonType {
		NORMAL,
		FIRE,
		ICE,
		GOLD,
	};

protected:
	static void
	_bind_methods();

public:
	LevelManager();
	~LevelManager();
	void _ready();

	void set_score(int balloonScore);
	int get_score();

	void set_current_level(int balloonScore);
	int get_current_level();
};

} // namespace godot