extends Spatial

var _value: int = 0

var _elements: Array = []

func _ready():
	pass

func set_value(v: int):
	_value = v
	
	var i: int = 0
	for e in _elements:
		e.set_state(((_value >> i) & 1) == 1)
		i += 1
