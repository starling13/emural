extends Spatial

var ecvm: Ural = null

func _init():
	ecvm = Ural.new()
	self.add_child(ecvm)

func _ready():
	$central_module/panel.ecvm = ecvm
	$central_module/pult_panel/pult.ecvm = ecvm
