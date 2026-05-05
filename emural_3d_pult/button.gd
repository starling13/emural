extends StaticBody

signal left_pressed
signal left_released

var _state: bool = false

func _ready():
	pass

func set_state(new_val: bool):
	if new_val:
		$MeshInstance.position.y = -0.01
	else:
		$MeshInstance.position.y = 0.01
	_state = new_val
	

func get_state() -> bool:
	return _state
	

func set_color(c: Color):
	var m: Material = $MeshInstance.get_active_material(0)
	m.albedo_color = c


func _on_button_mouse_entered():
	Input.set_default_cursor_shape(Input.CURSOR_DRAG)


func _on_button_mouse_exited():
	Input.set_default_cursor_shape(Input.CURSOR_ARROW)


func _on_button_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.pressed and e.button_index == BUTTON_LEFT:
			emit_signal("left_pressed")
		if not e.pressed and e.button_index == BUTTON_LEFT:
			emit_signal("left_released")
