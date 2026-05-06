extends KinematicBody


var _mov_spd: Vector3 = Vector3.ZERO


# Called when the node enters the scene tree for the first time.
func _ready():
	pass # Replace with function body.

func _physics_process(delta):
	if _mov_spd != Vector3.ZERO:
		var mv = self.transform.basis.xform(_mov_spd)
		self.move_and_slide(mv, Vector3.UP, true, 4, 0.1, false)	
	

func _input(event):
	if event is InputEventMouseMotion:
		var e: InputEventMouseMotion = event as InputEventMouseMotion
		if e.button_mask & BUTTON_RIGHT:
			self.rotation.y += e.relative.x/250.0
			$Camera.rotation.x += e.relative.y/250.0
	elif event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_WHEEL_UP:
			$Camera.fov = max(20.0, $Camera.fov-1)
		elif e.button_index == BUTTON_WHEEL_DOWN:
			$Camera.fov = min(90.0, $Camera.fov+1)

	if event.is_action_pressed("act_move_left"):
		_mov_spd.x = -0.5
	elif event.is_action_released("act_move_left"):
		_mov_spd.x = 0.0
		
	if event.is_action_pressed("act_move_right"):
		_mov_spd.x = 0.5
	elif event.is_action_released("act_move_right"):
		_mov_spd.x = 0.0

	if event.is_action_pressed("act_move_forward"):
		_mov_spd.z = -0.5
	elif event.is_action_released("act_move_forward"):
		_mov_spd.z = 0.0
		
	if event.is_action_pressed("act_move_backward"):
		_mov_spd.z = 0.5
	elif event.is_action_released("act_move_backward"):
		_mov_spd.z = 0.0
