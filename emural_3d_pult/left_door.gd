extends Door

func _ready():
	self.connect("open_state_changed", self, "_on_open_state_changed")

func _on_open_state_changed(value):
	self.rotation_degrees.y = 100.0 * value
