extends Door

var ecvm: Ural = null

# Called when the node enters the scene tree for the first time.
func _ready():
	self.connect("open_state_changed", self, "_on_open_state_changed")


func _on_open_state_changed(value):
	self.rotation_degrees.x = 80.0 * value


func _process(delta):
	$schk_panel.set_value(ecvm.schk())
	$rgk_panel.set_value(ecvm.rgk().value())
	$dshk_panel.set_value(ecvm.dshk())
	$rgau_panel.set_value(ecvm.rgau().value())
	$adder_panel.set_value(ecvm.adder().value())
	$control_reg_panel.set_value(ecvm.control_reg().value())

	var warning_value: int = 0
	if ecvm.phi_block():
		warning_value |= 1
	if ecvm.magtape_write_block():
		warning_value |= (1<<1)
	if ecvm.drum_write_block():
		warning_value |= (1<<2)
	if ecvm.command_reg_reset_block():
		warning_value |= (1<<3)
	$warning_panel.set_value(warning_value)
