extends Sprite2D

@onready var my_sprite: Sprite2D = self

#func _ready() -> void:
	#Input.mouse_mode = Input.MOUSE_MODE_HIDDEN
	
func _physics_process(delta: float) -> void:
	global_position = lerp(global_position, get_global_mouse_position(), 16.5 * delta)



func _input(event: InputEvent) -> void:
	if event is InputEventMouseButton:
		if event.button_index == MOUSE_BUTTON_LEFT and event.is_pressed():
			print("left Mouse button pressed");
			my_sprite.rotate(90.0)
