extends Button3D

func _ready():
	pass


func set_base_color(c: Color):
	var m: ShaderMaterial = $mesh.get_active_material(0)
	m.set_shader_param("base_color", c)
	var m2: Material = $mesh.get_active_material(1)
	m2.albedo_color = c
	
func set_decal_color(c: Color):
	var m: ShaderMaterial = $mesh.get_active_material(0)
	m.set_shader_param("decal_color", c)
	
func set_digit(d: int):
	var decal = null
	if d == 0:
		decal = load("res://ural_model/digit0.png")
	elif d == 1:
		decal = load("res://ural_model/digit1.png")
	elif d == 2:
		decal = load("res://ural_model/digit2.png")
	elif d == 3:
		decal = load("res://ural_model/digit3.png")
	elif d == 4:
		decal = load("res://ural_model/digit4.png")
	elif d == 5:
		decal = load("res://ural_model/digit5.png")
	elif d == 6:
		decal = load("res://ural_model/digit6.png")
	elif d == 7:
		decal = load("res://ural_model/digit7.png")
	elif d == 8:
		decal = load("res://ural_model/digit8.png")
	elif d == 9:
		decal = load("res://ural_model/digit9.png")
	else:
		print_debug("Bad digit", d)
	var m: ShaderMaterial = $mesh.get_active_material(0)
	m.set_shader_param("decal", decal)

func _on_button_left_pressed():
	$AudioStreamPlayer3D.play()
