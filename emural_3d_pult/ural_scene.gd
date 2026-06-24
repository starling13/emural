extends Spatial

var ecvm: Ural = null
var _heat_state: float = 0.0
var _fans: Array = []

const _heat_accel = 1.5

func _init():
	ecvm = Ural.new()

func _ready():
	$central_cabinet/panel.ecvm = ecvm
	$central_cabinet/pult_panel/pult.ecvm = ecvm
	
	_fans.append($central_cabinet/FanSound)
	_fans.append($left_cabinet/FanSound)
	_fans.append($right_cabinet/FanSound)
	_fans.append($leftmost_cabinet/FanSound)
	_fans.append($rightmost_cabinet/FanSound)


func _physics_process(delta):
	var fan: AudioStreamPlayer3D
	
	ecvm.clock_step()
	
	if ecvm.heat_voltage():
		if _heat_state < 1.0:
			_heat_state += delta / _heat_accel
		
			for i in range(_fans.size()):
				fan = _fans[i]
				fan.pitch_scale = _heat_state
				fan.max_db = -30.0 + 6.0 * _heat_state
		else:
			_heat_state = 1.0
		
		for i in range(_fans.size()):
			fan = _fans[i]
			if not fan.playing:
				fan.play()

	else:
		if _heat_state > 0.0:
			_heat_state -= delta / _heat_accel
		
			for i in range(_fans.size()):
				fan = _fans[i]
				fan.pitch_scale = _heat_state
				fan.max_db = -30.0 + 6.0 * _heat_state
		else:
			_heat_state = 0.0
			for i in range(_fans.size()):
				fan = _fans[i]
				if fan.playing:
					fan.stop()
