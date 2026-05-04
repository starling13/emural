extends Spatial


# Declare member variables here. Examples:
# var a = 2
# var b = "text"


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.


func _input(event):
	if event is InputEventMouseMotion:
		var e: InputEventMouseMotion = event as InputEventMouseMotion
		if e.button_mask & BUTTON_RIGHT:
			$Camera.rotation.y += e.relative.x/250.0
			$Camera.rotation.x += e.relative.y/250.0
	elif event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_WHEEL_UP:
			$Camera.fov = max(20.0, $Camera.fov-1)
		elif e.button_index == BUTTON_WHEEL_DOWN:
			$Camera.fov = min(90.0, $Camera.fov+1)
