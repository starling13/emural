extends StaticBody

class_name Button3D

signal left_pressed
signal left_released

export var press_state: bool = false
export var press_height: float = 0.005

func _ready():
	connect("mouse_entered", self, "_on_button_mouse_entered")
	connect("mouse_exited", self, "_on_button_mouse_exited")
	connect("input_event", self, "_on_button_input_event")


func set_state(new_val: bool):
	if new_val:
		$mesh.position.y = 0
	else:
		$mesh.position.y = press_height
	press_state = new_val


func _on_button_mouse_entered():
	Input.set_default_cursor_shape(Input.CURSOR_CAN_DROP)


func _on_button_mouse_exited():
	Input.set_default_cursor_shape(Input.CURSOR_ARROW)


func _on_button_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.pressed and e.button_index == BUTTON_LEFT:
			emit_signal("left_pressed")
		if not e.pressed and e.button_index == BUTTON_LEFT:
			emit_signal("left_released")
