class_name DiscreteLever
extends Lever

export var max_value: int = 2
var _state: int = 0

signal state_changed


func _input(event):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_LEFT:
			if not e.pressed and _state_grabbed:
				_state_grabbed = false
				print(_state_grabbed)
	elif event is InputEventMouseMotion and _state_grabbed:
		var e: InputEventMouseMotion = event as InputEventMouseMotion
		_open_state -= e.relative.y / rot_scale
		if _open_state < 0:
			_open_state = 0
		elif _open_state > max_value:
			_open_state = max_value
		var new_state: int = round(_open_state)
		if new_state != _state:
			_state = new_state
			if rot_max_angle != 0.0:
				var os: Vector3 = rot_axis * rot_max_angle * _state / max_value
				rotation_degrees = os
			emit_signal("state_changed", _state)
