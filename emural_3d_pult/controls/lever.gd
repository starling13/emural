###############################################################################
# Lever, rotating around axis on the angle by mouse grabbing
#
# Provide public properties:
#   rot_axis: Vector3D
#   rot_max_angle: float
#   rot_scale: float
###############################################################################

class_name Lever
extends Spatial

# Axis of the rotation
export var rot_axis: Vector3 = Vector3.UP
# Maximu angle (deg). Lever will turn from 0 to this value around the axis
export var rot_max_angle: float = 90.0
# Proportional coefficient between mouse movement and rotational angle
export var rot_scale: float = 300.0

var _open_state: float = 0.0

var _state_grabbed: bool = false


func _ready():
	var handle = self.get_node("StaticBody")
	handle.connect("mouse_entered", self, "_on_handle_mouse_entered")
	handle.connect("mouse_exited", self, "_on_handle_mouse_exited")
	handle.connect("input_event", self, "_on_input_event")


func _on_handle_mouse_entered():
	Input.set_default_cursor_shape(Input.CURSOR_CAN_DROP)


func _on_handle_mouse_exited():
	Input.set_default_cursor_shape(Input.CURSOR_ARROW)


func _on_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_LEFT:
			_state_grabbed = e.pressed
