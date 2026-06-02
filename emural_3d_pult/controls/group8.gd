extends DigitButtonGroup

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
