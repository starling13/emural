extends StaticBody
class_name Ural53

enum Mode_t {OFF = 0, RADIO = 1, VINIL = 2}

signal remove_disk

var _disk_in_active_zone: VinilDiskScene = null

var _inserted_disk: VinilDiskScene = null
# Motor set speed: 33, 78
var motor_mode: int = 0
# Current motor rotation speed
var motor_speed: float = 0.0
# Sound volume level
var volume: float = 0.0
# Current mode
var mode: int = Mode_t.OFF

var disk_position: float = 0.0

var disk_start_probe_anle = 0.4

func _ready():
	pass

func _on_Button_pressed():
	if $AudioStreamPlayer3D.playing:
		$AudioStreamPlayer3D.stop()
		$NoiseSound.stop()
	else:
		$AudioStreamPlayer3D.play()
		$NoiseSound.play()


func _on_Area_body_entered(body):
	print_debug("Body entered ", body)
	if body is VinilDiskScene:
		var vd: VinilDiskScene = body as VinilDiskScene
		_disk_in_active_zone = vd
		print_debug("Set active disk ", vd)


func _on_Area_body_exited(body):
	if _disk_in_active_zone == body:
		_disk_in_active_zone = null
		print_debug("Unset active disk ", body)


func use_disk(disk, player):
	var side: int
	
	if not disk is VinilDiskScene:
		print_debug("Unknown type")
		return
	
	if not player is Player:
		print_debug("Unknown type")
		return
		
	var vdisk: VinilDiskScene = disk as VinilDiskScene
		
	if _disk_in_active_zone != vdisk:
		print_debug("Not an active disk")
		return
	
	side = 0 if vdisk.global_transform.basis.y.y>0 else 1

	player.drop_object(vdisk)
	vdisk.mode = RigidBody.MODE_STATIC
	
	$DiskPlacement.add_child(vdisk)
	vdisk.transform = Transform.IDENTITY
	if side == 1:
		vdisk.rotate(Vector3.RIGHT, deg2rad(180.0))
	_inserted_disk = vdisk
	
	$AudioStreamPlayer3D.stream = vdisk.disk_item.audio_streams[side]

func _on_Area_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.pressed and e.button_index == BUTTON_LEFT:
			if _inserted_disk != null:
				emit_signal("remove_disk", _inserted_disk)
				_inserted_disk = null


func _physics_process(delta):
	var _old_speed = motor_speed
	if motor_speed != float(motor_mode):
		motor_speed = clamp(
			motor_speed+sign(float(motor_mode)-motor_speed)*delta*30.0,
			0.0,
			78.0
		)
		if abs(motor_speed-motor_mode) < 1:
			motor_speed = float(motor_mode)
			
	if motor_speed == 0.0:
		$AudioStreamPlayer3D.stop()
	
	if motor_speed != _old_speed:
		$AudioStreamPlayer3D.pitch_scale = motor_speed / 78.0
	
	if $AudioStreamPlayer3D.playing:
		disk_position = $AudioStreamPlayer3D.get_playback_position() / $AudioStreamPlayer3D.stream.get_length()


func _process(delta):
	$DiskPlacement.rotate_y(-delta*motor_speed / 60.0 * 2*PI)
	if $AudioStreamPlayer3D.playing:
		$SoundProbe._open_state = range_lerp(disk_position, 0.0, 1.0, disk_start_probe_anle, 1.0)
		$SoundProbe.rotation_degrees.y = -$SoundProbe.rot_max_angle * $SoundProbe._open_state


func _on_SpeedLever_state_changed(state: int):
	if state == 0:
		motor_mode = 0
	elif state == 1:
		motor_mode = 33
	elif state == 2:
		motor_mode = 78


func _on_VolumeLever_open_state_changed(v: float):
	volume = v
	$AudioStreamPlayer3D.max_db = (volume - 0.75) * 24.0


func _on_ModeSwitch_state_changed(s: int):
	mode = s


func _on_soundProbe_open_state_changed(s: float):
	if s > disk_start_probe_anle:
		disk_position = range_lerp(s, disk_start_probe_anle, 1.0, 0.0, 1.0)
		if mode == Mode_t.VINIL:
			$AudioStreamPlayer3D.play(disk_position)
	else:
		disk_position = 0.0
		$AudioStreamPlayer3D.stop()
