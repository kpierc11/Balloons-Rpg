extends Node

@export var levelManager: LevelManager
@export var balloonManager: BalloonManager
@onready var score_label: Label = $Control/MarginContainer3/HBoxContainer/score
@onready var level_label: Label = $Control/MarginContainer2/HBoxContainer/Level
func _ready():
	print("on ready called")
	score_label.text ="Score: %d" % levelManager.get_score()




func _on_balloon_manager_balloon_popped(points: int) -> void:
	var score = levelManager.get_score();
	score += points
	levelManager.set_score(score);
	score_label.text ="Score: %d" % levelManager.get_score()


func _on_level_manager_level_updated() -> void:
	level_label.text ="Level: %d" % levelManager.get_current_level()
