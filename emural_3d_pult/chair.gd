extends StaticBody
class_name Chair

signal selected

func _ready():
	pass


func _on_chair_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_LEFT:
			if e.pressed:
				emit_signal("selected", self)
