extends Spatial

var ecvm: Ural = null

func _init():
	ecvm = Ural.new()
	self.add_child(ecvm)

func _ready():
	$central_cabinet/panel.ecvm = ecvm
	$central_cabinet/pult_panel/pult.ecvm = ecvm
