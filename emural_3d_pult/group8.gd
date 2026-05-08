extends Spatial

var _buttons: Array = []
var _value: int = -1

# Called when the node enters the scene tree for the first time.
func _ready():
	_buttons.append($button_00)
	_buttons.append($button_01)
	_buttons.append($button_02)
	_buttons.append($button_03)
	_buttons.append($button_04)
	_buttons.append($button_05)
	_buttons.append($button_06)
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


func set_color(c: Color):
	for b in _buttons:
		b.set_color(c)

func _on_button_input_event(camera, event, position, normal, shape_idx, button_index):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.pressed and e.button_index == BUTTON_LEFT:
			if _buttons[button_index].press_state:
				return
			self.set_value(button_index)
