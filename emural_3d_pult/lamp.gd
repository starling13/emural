extends Spatial


export var _state: bool = false


# Called when the node enters the scene tree for the first time.
func _ready():
	pass


func set_state(v: bool):
	_state = v
	if _state:
		$glass.get_surface_material(0).emission_energy = 1.0
		$OmniLight.light_energy = 0.25
	else:
		$glass.get_surface_material(0).emission_energy = 0.0
		$OmniLight.light_energy = 0.0
