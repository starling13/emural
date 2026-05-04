extends StaticBody

func _ready():
	$group8_00.set_color(Color.black)
	$group8_01.set_color(Color.black)
	$group8_02.set_color(Color.black)
	$group8_03.set_color(Color.black)
	$group8_04.set_color(Color.black)
	$group8_05.set_color(Color.black)
	
	$group8_06.set_color(Color.white)
	$group8_07.set_color(Color.white)
	$group8_08.set_color(Color.white)
	$group8_09.set_color(Color.white)
	$group8_10.set_color(Color.white)
	$group8_11.set_color(Color.white)
	
	$group8_1_00.set_color(Color.black)
	$group8_1_01.set_color(Color.black)
	$group8_1_02.set_color(Color.black)
	$group8_1_03.set_color(Color.black)
	
	$group8_1_04.set_color(Color.red)
	$group8_1_05.set_color(Color.red)


func _on_addr_vz_left_pressed():
	$addr_vz.set_state(true)
	$group8_00.set_value(-1)
	$group8_01.set_value(-1)
	$group8_02.set_value(-1)
	$group8_03.set_value(-1)
	$group8_04.set_value(-1)


func _on_addr_vz_left_released():
	$addr_vz.set_state(false)
