extends Switch3D
class_name LeverSwitch

signal changed

func _ready():
	pass

func _on_LeverSwitch_left_pressed():
	$AudioStreamPlayer3D.play()
	press_state = !press_state
	emit_signal("changed", press_state)
	if press_state:
		$lever.rotation_degrees.x = -20.0
	else:
		$lever.rotation_degrees.x  = 20.0
