extends RigidBody
class_name HandItem


signal left_pressed
signal left_released
signal right_pressed
signal right_released

#var player = null


func _ready():
	connect("input_event", self, "_on_button_input_event")


func _on_button_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.pressed and e.button_index == BUTTON_LEFT:
			emit_signal("left_pressed", self)
		if not e.pressed and e.button_index == BUTTON_LEFT:
			emit_signal("left_released", self)
		if e.pressed and e.button_index == BUTTON_RIGHT:
			emit_signal("right_pressed", self)
		if not e.pressed and e.button_index == BUTTON_RIGHT:
			emit_signal("right_released", self)
