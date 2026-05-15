class_name PushButton3D

extends Button3D

signal pressed

func _ready():
	connect("left_pressed", self, "_on_left_pressed")
	connect("left_released", self, "_on_left_released")
	

func _on_left_pressed():
	if self.press_state:
		return
	
	self.set_state(true)
	emit_signal("pressed")

func _on_left_released():
	self.set_state(false)
