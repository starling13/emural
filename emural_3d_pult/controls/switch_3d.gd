extends CollisionObject

class_name Switch3D

signal left_pressed
signal left_released

export var press_state: bool = false

func _ready():
	connect("mouse_entered", self, "_on_button_mouse_entered")
	connect("mouse_exited", self, "_on_button_mouse_exited")
	connect("input_event", self, "_on_button_input_event")


func set_state(new_val: bool):
	press_state = new_val
	self._update_geometry()


func _update_geometry() -> void:
	pass


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
