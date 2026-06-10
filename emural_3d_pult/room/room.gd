extends Spatial


# Called when the node enters the scene tree for the first time.
func _ready():
	pass


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass


func _on_light_switch_changed(v: bool):
	var le: float = 0.5 if v else 0.0
	$SpotLight.light_energy = le
	$SpotLight2.light_energy = le
	$SpotLight3.light_energy = le
	$SpotLight4.light_energy = le
	$SpotLight5.light_energy = le
	$SpotLight6.light_energy = le
