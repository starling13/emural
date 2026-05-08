extends Button3D

func _ready():
	pass


func get_state() -> bool:
	return press_state
	

func set_color(c: Color):
	var m: Material = $mesh.get_active_material(0)
	m.albedo_color = c
