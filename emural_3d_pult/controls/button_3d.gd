extends Switch3D
class_name Button3D


export var press_height: float = 0.005


func _ready():
	pass


func _update_geometry() -> void:
	if self.press_state:
		$model.position.y = 0
	else:
		$model.position.y = press_height
