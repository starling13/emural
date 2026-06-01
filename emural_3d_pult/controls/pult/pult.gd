extends Spatial

var _adder_keyboard: Array = []
var _command_reg_keyboard: Array = []

var ecvm: Ural = null

func _ready():
	$group8_00.set_colors(Color.black, Color.white)
	self._adder_keyboard.append($group8_00)
	$group8_01.set_colors(Color.black, Color.white)
	self._adder_keyboard.append($group8_01)
	$group8_02.set_colors(Color.black, Color.white)
	self._adder_keyboard.append($group8_02)
	$group8_03.set_colors(Color.black, Color.white)
	self._adder_keyboard.append($group8_03)
	$group8_04.set_colors(Color.black, Color.white)
	self._adder_keyboard.append($group8_04)
	$group8_05.set_colors(Color.black, Color.white)
	self._adder_keyboard.append($group8_05)
	
	$group8_06.set_colors(Color.white, Color.black)
	self._adder_keyboard.append($group8_06)
	$group8_07.set_colors(Color.white, Color.black)
	self._adder_keyboard.append($group8_07)
	$group8_08.set_colors(Color.white, Color.black)
	self._adder_keyboard.append($group8_08)
	$group8_09.set_colors(Color.white, Color.black)
	self._adder_keyboard.append($group8_09)
	$group8_10.set_colors(Color.white, Color.black)
	self._adder_keyboard.append($group8_10)
	$group8_11.set_colors(Color.white, Color.black)
	self._adder_keyboard.append($group8_11)
	
	$group8_1_00.set_colors(Color.black, Color.white)
	self._command_reg_keyboard.append($group8_1_00)
	$group8_1_01.set_colors(Color.black, Color.white)
	self._command_reg_keyboard.append($group8_1_01)
	$group8_1_02.set_colors(Color.black, Color.white)
	self._command_reg_keyboard.append($group8_1_02)
	$group8_1_03.set_colors(Color.black, Color.white)
	self._command_reg_keyboard.append($group8_1_03)
	
	$group8_1_04.set_colors(Color.red, Color.white)
	self._command_reg_keyboard.append($group8_1_04)
	$group8_1_05.set_colors(Color.red, Color.white)
	self._command_reg_keyboard.append($group8_1_05)

func _on_rgk_and_button_left_pressed():
	$rgk_and_button.set_state(true)

	var rgk_value: int = 0
	
	rgk_value |= $group8_1_00.value()
	rgk_value |= $group8_1_01.value() << 3
	rgk_value |= $group8_1_02.value() << 6
	rgk_value |= $group8_1_03.value() << 9
	rgk_value |= $group8_1_04.value() << 12
	rgk_value |= $group8_1_05.value() << 15
	
	ecvm.rgk().set_value(rgk_value)


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
	
	var w: Ural.Word = Ural.Word.new(rgau_value)
	ecvm.set_rgau_and_adder(w)


func _on_clear_button_pressed():
	ecvm._drum.clear()


func _on_addr_vz_button_pressed():
	for b in self._adder_keyboard:
		b.set_value(-1)


func _on_block_drum_write_switch_changed(new_val: bool):
	ecvm.set_drum_write_block(new_val)


func _on_block_magtape_write_switch_changed(new_val: bool):
	ecvm.set_magtape_write_block(new_val)


func _on_phi_blocking_switch_changed(new_val: bool):
	ecvm.set_phi_block(new_val)


func _on_block_commandreg_reset_switch_changed(new_val: bool):
	ecvm.set_command_reg_reset_block(new_val)


func _on_control_reg_addr_panel_changed(value: int):
	ecvm.set_control_reg_address(value)


func _on_start_button_pressed():
	ecvm.start()


func _on_single_step_button_pressed():
	ecvm.step()


func _on_stop_button_pressed():
	ecvm.stop()
