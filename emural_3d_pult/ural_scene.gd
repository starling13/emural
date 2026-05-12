extends Spatial

var ecvm: Ural = null

func _init():
	ecvm = Ural.new()

func _ready():
	$central_cabinet/panel.ecvm = ecvm
	$central_cabinet/pult_panel/pult.ecvm = ecvm


func _physics_process(delta):
	ecvm.clock_step()
