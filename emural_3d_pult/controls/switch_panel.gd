extends Spatial
class_name SwitchPanel

signal changed

var _elements: Array = []

func _ready():
	pass
	
func _on_switch_changed(v: bool):
	emit_signal("changed", get_value())
	
func add_element(e: LeverSwitch):
	_elements.append(e)
	e.connect("changed", self, "_on_switch_changed")

func get_value() -> int:
	var res: int = 0
	var i: int = 0
	
	for e in _elements:
		if e.press_state:
			res |= (1 << i)
		i += 1
	
	return res
