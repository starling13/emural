extends Spatial

export var open_state: float = 0.0
signal open_state_changed

var _handle: StaticBody
var _state_grabbed: bool = false


func _ready():
	pass


func init_door():
	self._handle = self.get_node("StaticBody")
	self._handle.connect("mouse_entered", self, "_on_handle_mouse_entered")
	self._handle.connect("mouse_exited", self, "_on_handle_mouse_exited")
	self._handle.connect("input_event", self, "_on_input_event")
	
	
func _on_handle_mouse_entered():
	Input.set_default_cursor_shape(Input.CURSOR_CAN_DROP)
	

func _on_handle_mouse_exited():
	Input.set_default_cursor_shape(Input.CURSOR_ARROW)


func _input(event):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_LEFT:
			if not e.pressed and self._state_grabbed:
				self._state_grabbed = false
				print(self._state_grabbed)
	elif event is InputEventMouseMotion and self._state_grabbed:
		var e: InputEventMouseMotion = event as InputEventMouseMotion
		self.open_state -= e.relative.y / 300.0
		self.open_state = clamp(self.open_state, 0.0, 1.0)
		emit_signal("open_state_changed", self.open_state)


func _on_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_LEFT:
			self._state_grabbed = e.pressed
