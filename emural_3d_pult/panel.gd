extends Door

var ecvm: Ural = null

# Called when the node enters the scene tree for the first time.
func _ready():
	.init_door()
	self.connect("open_state_changed", self, "_on_open_state_changed")


func _on_open_state_changed(value):
	self.rotation_degrees.x = 80.0 * value


func _process(delta):
	$schk_panel.set_value(ecvm.get_schk())
