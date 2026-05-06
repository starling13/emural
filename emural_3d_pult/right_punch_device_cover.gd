extends Door


func _ready():
	.init_door()
	self.connect("open_state_changed", self, "_on_open_state_changed")

func _on_open_state_changed(value):
	self.rotation_degrees.x = -80.0 * value
	if value == 1.0:
		$OmniLight.light_energy = 0.75
	else:
		$OmniLight.light_energy = 0.0
