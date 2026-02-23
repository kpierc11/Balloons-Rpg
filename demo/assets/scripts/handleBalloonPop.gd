extends Button

@onready var balloonNode = get_node("/root/Main/CanvasLayer/BalloonManager")

func _on_pressed() -> void:
	balloonNode.popAllBalloons();
