extends Spatial

var _adder_keyboard: Array = []
var _command_reg_keyboard: Array = []

var ecvm: Ural = null

func _ready():
	$group8_00.set_color(Color.black)
	self._adder_keyboard.append($group8_00)
	$group8_01.set_color(Color.black)
	self._adder_keyboard.append($group8_01)
	$group8_02.set_color(Color.black)
	self._adder_keyboard.append($group8_02)
	$group8_03.set_color(Color.black)
	self._adder_keyboard.append($group8_03)
	$group8_04.set_color(Color.black)
	self._adder_keyboard.append($group8_04)
	$group8_05.set_color(Color.black)
	self._adder_keyboard.append($group8_05)
	
	$group8_06.set_color(Color.white)
	self._adder_keyboard.append($group8_06)
	$group8_07.set_color(Color.white)
	self._adder_keyboard.append($group8_07)
	$group8_08.set_color(Color.white)
	self._adder_keyboard.append($group8_08)
	$group8_09.set_color(Color.white)
	self._adder_keyboard.append($group8_09)
	$group8_10.set_color(Color.white)
	self._adder_keyboard.append($group8_10)
	$group8_11.set_color(Color.white)
	self._adder_keyboard.append($group8_11)
	
	$group8_1_00.set_color(Color.black)
	self._command_reg_keyboard.append($group8_1_00)
	$group8_1_01.set_color(Color.black)
	self._command_reg_keyboard.append($group8_1_01)
	$group8_1_02.set_color(Color.black)
	self._command_reg_keyboard.append($group8_1_02)
	$group8_1_03.set_color(Color.black)
	self._command_reg_keyboard.append($group8_1_03)
	
	$group8_1_04.set_color(Color.red)
	self._command_reg_keyboard.append($group8_1_04)
	$group8_1_05.set_color(Color.red)
	self._command_reg_keyboard.append($group8_1_05)

func _on_addr_vz_left_pressed():
	$addr_vz.set_state(true)
	for b in self._adder_keyboard:
		b.set_value(-1)


func _on_addr_vz_left_released():
	$addr_vz.set_state(false)


func _on_start_button_left_pressed():
	$start_button.set_state(true)
	ecvm.start()

func _on_start_button_left_released():
	$start_button.set_state(false)

func _on_stop_button_left_pressed():
	$stop_button.set_state(true)
	ecvm.stop()

func _on_stop_button_left_released():
	$stop_button.set_state(false)


func _on_single_step_button_left_pressed():
	$single_step_button.set_state(true)
	ecvm.step()


func _on_single_step_button_left_released():
	$single_step_button.set_state(false)


func _on_rgk_and_button_left_pressed():
	$rgk_and_button.set_state(true)

	var rgk_value: int = 0
	
	rgk_value |= $group8_1_00.value()
	rgk_value |= $group8_1_01.value() << 3
	rgk_value |= $group8_1_02.value() << 6
	rgk_value |= $group8_1_03.value() << 9
	rgk_value |= $group8_1_04.value() << 12
	rgk_value |= $group8_1_05.value() << 15
	
	ecvm.set_rgk(rgk_value)


func _on_rgk_and_button_left_released():
	$rgk_and_button.set_state(false)


func _on_com_reg_vz_button_pressed():
	for b in self._command_reg_keyboard:
		b.set_value(-1)


func _on_reg_add_button_pressed():
	var rgau_value: int = 0
	
	rgau_value |= $group8_00.value()
	rgau_value |= $group8_01.value() << 3
	rgau_value |= $group8_02.value() << 6
	rgau_value |= $group8_03.value() << 9
	rgau_value |= $group8_04.value() << 12
	rgau_value |= $group8_05.value() << 15
	rgau_value |= $group8_06.value() << 18
	rgau_value |= $group8_07.value() << 21
	rgau_value |= $group8_08.value() << 24
	rgau_value |= $group8_09.value() << 27
	rgau_value |= $group8_10.value() << 30
	rgau_value |= $group8_11.value() << 33
	
	ecvm.set_rgau(rgau_value)
