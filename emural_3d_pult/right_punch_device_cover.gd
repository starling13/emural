extends Door


func _ready():
	self.connect("open_state_changed", self, "_on_open_state_changed")

func _on_open_state_changed(value):
	if value == 1.0:
		$OmniLight.light_energy = 0.75
		$HatchLamp.get_active_material(1).emission_enabled = true
		$HatchLamp.get_active_material(1).emission_energy = 1.0
	else:
		$OmniLight.light_energy = 0.0
		$HatchLamp.get_active_material(1).emission_enabled = false
		$HatchLamp.get_active_material(1).emission_energy = 0.0
