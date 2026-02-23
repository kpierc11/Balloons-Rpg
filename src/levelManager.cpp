#include "levelManager.h"

void godot::LevelManager::_bind_methods() {
	// Bind setters/getters
	ClassDB::bind_method(D_METHOD("set_score", "balloonScore"), &LevelManager::set_score);
	ClassDB::bind_method(D_METHOD("get_score"), &LevelManager::get_score);
	ClassDB::bind_method(D_METHOD("set_current_level", "level"), &LevelManager::set_current_level);
	ClassDB::bind_method(D_METHOD("get_current_level"), &LevelManager::get_current_level);


	// Register properties for editor
	//ADD_PROPERTY(PropertyInfo(Variant::OBJECT, "sprite", PROPERTY_HINT_RESOURCE_TYPE, "Texture2D"), "setSprite", "getSprite");
    ADD_PROPERTY(PropertyInfo(Variant::INT, "Current Score"),"set_score", "get_score");
	ADD_PROPERTY(PropertyInfo(Variant::INT, "Current Level"),"set_current_level", "get_current_level");

	ADD_SIGNAL(MethodInfo("score_updated"));
	ADD_SIGNAL(MethodInfo("level_updated"));
}

godot::LevelManager::LevelManager() {
	score = 0;
	currentLevel = 1;
}

godot::LevelManager::~LevelManager() {
}

void godot::LevelManager::_ready() {
}

int godot::LevelManager::get_score() {
	return score;
}

void godot::LevelManager::set_current_level(int level) {
	currentLevel = level;
}

int godot::LevelManager::get_current_level() {
	return currentLevel;
}

void godot::LevelManager::set_score(int balloonScore) {
    score = balloonScore;
}
