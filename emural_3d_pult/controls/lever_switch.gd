extends Switch3D
class_name LeverSwitch

signal changed

func _ready():
	pass

func _on_LeverSwitch_left_pressed():
	press_state = !press_state
	emit_signal("changed", press_state)
	if press_state:
		$lever.rotation_degrees.x = -10.0
	else:
		$lever.rotation_degrees.x  = 10.0
