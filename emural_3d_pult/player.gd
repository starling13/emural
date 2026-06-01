extends KinematicBody

var _mov_spd: Vector3 = Vector3.ZERO
var _chair: Chair = null

func _ready():
	pass

func _physics_process(delta):
	if _mov_spd != Vector3.ZERO:
		var mv = self.transform.basis.xform(_mov_spd)
		self.move_and_slide(mv, Vector3.UP, true, 4, 0.1, false)
	if not is_on_floor():
		_mov_spd.y -= 9.81 * delta

func _input(event):
	if event.is_action_pressed("act_cancel") and _chair != null:
		_stand_up()
	
	if event is InputEventMouseMotion:
		var e: InputEventMouseMotion = event as InputEventMouseMotion
		if e.button_mask & BUTTON_RIGHT:
			$Camera.rotation.x += e.relative.y/250.0
			if _chair != null:
				$Camera.rotation.y += e.relative.x/250.0
	elif event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.button_index == BUTTON_WHEEL_UP:
			$Camera.fov = max(10.0, $Camera.fov-1)
		elif e.button_index == BUTTON_WHEEL_DOWN:
			$Camera.fov = min(100.0, $Camera.fov+1)
			
	if _chair != null:
		return
	
	if event is InputEventMouseMotion:
		var e: InputEventMouseMotion = event as InputEventMouseMotion
		if e.button_mask & BUTTON_RIGHT:
			self.rotation.y += e.relative.x/250.0

	if event.is_action_pressed("act_move_left"):
		_mov_spd.x = -0.75
	elif event.is_action_released("act_move_left"):
		_mov_spd.x = 0.0
		
	if event.is_action_pressed("act_move_right"):
		_mov_spd.x = 0.75
	elif event.is_action_released("act_move_right"):
		_mov_spd.x = 0.0

	if event.is_action_pressed("act_move_forward"):
		_mov_spd.z = -1.0
	elif event.is_action_released("act_move_forward"):
		_mov_spd.z = 0.0
		
	if event.is_action_pressed("act_move_backward"):
		_mov_spd.z = 1.0
	elif event.is_action_released("act_move_backward"):
		_mov_spd.z = 0.0
		
	if event.is_action_pressed("act_jump"):
		_mov_spd.y = 3.0
		
func _on_chair_selected(chair):
	if _chair == null:
		_sit_down(chair)
	else:
		print("Already siiting on a chair", _chair)

func _sit_down(chair):
	_mov_spd = Vector3.ZERO
	var sit_point = chair.get_node_or_null("EyePoint")
	$Camera.global_transform.origin = sit_point.global_transform.origin - Vector3(0, 0, 0)
	_chair = chair
	print("Sit on a chair", _chair)
	
func _stand_up():
	$Camera.position = Vector3(0, 0.7, 0)
	$Camera.rotation = Vector3(0, 0, 0)
	print("Standing up from chair", _chair)
	_chair = null
