extends Spatial

var _buttons: Array = []
var _value: int = -1

# Called when the node enters the scene tree for the first time.
func _ready():
	$button_00.set_digit(0)
	_buttons.append($button_00)
	$button_01.set_digit(1)
	_buttons.append($button_01)
	$button_02.set_digit(2)
	_buttons.append($button_02)
	$button_03.set_digit(3)
	_buttons.append($button_03)
	$button_04.set_digit(4)
	_buttons.append($button_04)
	$button_05.set_digit(5)
	_buttons.append($button_05)
	$button_06.set_digit(6)
	_buttons.append($button_06)
	$button_07.set_digit(7)
	_buttons.append($button_07)


func set_value(v: int):
	if v > 7:
		return
	_value = v
	for b in _buttons:
		b.set_state(false)
	if v >= 0:
		_buttons[v].set_state(true)


func value() -> int:
	return _value

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
