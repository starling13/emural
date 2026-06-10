class_name Player
extends KinematicBody

signal use_item

var _mov_spd: Vector3 = Vector3.ZERO
var _chair: Chair = null
var _holding: HandItem = null

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
		if e.control:
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
		
	if event.is_action_pressed("act_use"):
		if _holding != null:
			emit_signal("use_item", _holding, self)
	
	if event.is_action_pressed("act_drop"):
		if _holding != null:
			var item = _holding
			var gt = _holding.global_transform
			drop_object(item)
			get_parent().add_child(item)
			item.global_transform = gt
			item.collision_layer = 1
			item.collision_mask = 1
	
	if event.is_action_pressed("act_rotate"):
		if not event.control:
			$Camera/HoldPosition.rotate_x(0.1)


func _on_chair_selected(chair):
	if _chair == null:
		_sit_down(chair)
	else:
		print_debug("Already siiting on a chair", _chair)


func _sit_down(chair):
	_mov_spd = Vector3.ZERO
	var sit_point = chair.get_node_or_null("EyePoint")
	$Camera.global_transform.origin = sit_point.global_transform.origin - Vector3(0, 0, 0)
	_chair = chair
	print_debug("Sit on a chair", _chair)


func _stand_up():
	$Camera.position = Vector3(0, 0.7, 0)
	$Camera.rotation = Vector3(0, 0, 0)
	print_debug("Standing up from chair", _chair)
	_chair = null


func hold_object(item: HandItem):
	if _holding == null:
		item.connect("left_pressed", self, "hold_object")
		item.collision_layer = 2
		item.collision_mask = 2
		_holding = item
		_holding.mode = RigidBody.MODE_STATIC
		_holding.transform = Transform.IDENTITY
		var p = _holding.get_parent()
		if p != null:
			p.remove_child(_holding)
		$Camera/HoldPosition.add_child(_holding)
		#_holding.player = self
		print_debug("Holding a new object")
	else:
		print_debug("Already holding an object")


func drop_object(item: HandItem):
	if _holding != item:
		print_debug("Wrong object ", item)
		return
	#_holding.player = null
	_holding = null
	$Camera/HoldPosition.remove_child(item)
	item.mode = RigidBody.MODE_RIGID
