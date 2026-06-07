extends Lever
class_name Door

signal open_state_changed


func _input(event):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_LEFT:
			if not e.pressed and _state_grabbed:
				_state_grabbed = false
	elif event is InputEventMouseMotion and _state_grabbed:
		var e: InputEventMouseMotion = event as InputEventMouseMotion
		_open_state -= e.relative.y / rot_scale
		_open_state = clamp(_open_state, 0.0, 1.0)
		emit_signal("open_state_changed", _open_state)
		if rot_max_angle != 0.0:
			var os = rot_axis * rot_max_angle * _open_state
			rotation_degrees = os
