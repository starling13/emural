###############################################################################
# Radiola Ural-53 (USSR, 1953 year)
#
###############################################################################

class_name Ural53
extends StaticBody

# Main modes lever: Device OFF, Radio mode, vinil disks player mode
enum Mode_t {OFF = 0, RADIO = 1, VINIL = 2}
# Mode of the disks player motor: 33 1/3 rpm, Off, 78 rpm
enum MotorMode_t {OFF = 0, SPEED33 = 1, SPEED78 = 2}

signal remove_disk

# Current mode
var mode: int = Mode_t.OFF

var _disk_in_active_zone: VinilDiskScene = null

var _inserted_disk: VinilDiskScene = null
# Motor set speed: 33, 78
var motor_mode: int = 0
# Current motor rotation speed
var motor_speed: float = 0.0
# Sound volume level
var volume: float = 0.0

# Position in current disk
var disk_position: float = 0.0

var disk_start_probe_anle = 0.4

var _bus_idx: int = -1

var _eq: AudioEffectEQ6

var _tembr: float = 0.0
# AC power master switch
var _power: bool = false


func _ready():
	var bus_name: String = "Ural53_"+str(get_instance_id())
	# Create local audio bus
	_bus_idx = AudioServer.get_bus_index(bus_name)
	if _bus_idx == -1:
		AudioServer.add_bus()
		_bus_idx = AudioServer.get_bus_count() - 1
		AudioServer.set_bus_name(_bus_idx, bus_name)
		AudioServer.set_bus_send(_bus_idx, "Master")
	
	# Create equalizer
	_eq = AudioEffectEQ6.new()
	AudioServer.add_bus_effect(_bus_idx, _eq, 0)
	
	# Set bus to main sound source
	$AudioStreamPlayer3D.bus = bus_name
	$NoiseSound.bus = bus_name
	
	# Default init tembr
	_update_eq()


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
	AudioServer.set_bus_volume_db(_bus_idx, (volume - 0.75) * 24.0)


func _on_ModeSwitch_state_changed(s: int) -> void:
	$ModeSwitch/ClickSound.play()
	mode = s
	_update_mode()
	

func _update_mode() -> void:
	if mode == Mode_t.OFF:
		_power = false
	else:
		_power = true

	if mode == Mode_t.RADIO:
		$ScaleLight01.visible = true
		$ScaleLight02.visible = true
		$ScaleLight03.visible = true
	else:
		$ScaleLight01.visible = false
		$ScaleLight02.visible = false
		$ScaleLight03.visible = false
		

func _on_soundProbe_open_state_changed(s: float):
	if s > disk_start_probe_anle:
		disk_position = range_lerp(s, disk_start_probe_anle, 1.0, 0.0, 1.0)
		if mode == Mode_t.VINIL:
			$AudioStreamPlayer3D.play(disk_position)
	else:
		disk_position = 0.0
		$AudioStreamPlayer3D.stop()


func _on_TembLever_open_state_changed(v: float):
	_tembr = v - 0.5
	_update_eq()


func _update_eq():
	# Move tone balance
	var treble_db: float = _tembr * 24.0
	var bass_db: float = -treble_db
	
	_eq.set_band_gain_db(0, bass_db)
	_eq.set_band_gain_db(1, bass_db / 2.0)
	
	_eq.set_band_gain_db(2, bass_db / 4.0)
	_eq.set_band_gain_db(3, treble_db / 4.0)
	
	_eq.set_band_gain_db(4, treble_db / 2.0)
	_eq.set_band_gain_db(5, treble_db)
