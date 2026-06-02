extends Spatial
class_name DigitButtonGroup

var _buttons: Array = []
var _value: int = -1

func _ready():
	pass

func value() -> int:
	return _value

func set_value(v: int):
	if v > (_buttons.size()-1):
		return
	_value = v
	for b in _buttons:
		b.set_state(false)
	if v >= 0:
		_buttons[v].set_state(true)

func set_colors(c1: Color, c2: Color):
	for b in _buttons:
		b.set_base_color(c1)
		b.set_decal_color(c2)

func _on_button_input_event(camera, event, position, normal, shape_idx, button_index):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.pressed and e.button_index == BUTTON_LEFT:
			if _buttons[button_index].press_state:
				return
			self.set_value(button_index)
