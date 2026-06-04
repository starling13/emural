extends StaticBody
class_name Ural53

signal remove_disk

var _disk_in_active_zone: VinilDisk = null
var _inserted_disk: VinilDisk = null


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
	if body is VinilDisk:
		var vd: VinilDisk = body as VinilDisk
		_disk_in_active_zone = vd
		print_debug("Set active disk ", vd)


func _on_Area_body_exited(body):
	if _disk_in_active_zone == body:
		_disk_in_active_zone = null
		print_debug("Unset active disk ", body)


func use_disk(disk, player):
	if not disk is VinilDisk:
		print_debug("Unknown type")
		return
	
	if not player is Player:
		print_debug("Unknown type")
		return
		
	var vdisk: VinilDisk = disk as VinilDisk
		
	if _disk_in_active_zone != vdisk:
		print_debug("Not an active disk")
		return

	player.drop_object(vdisk)
	vdisk.mode = RigidBody.MODE_STATIC
	$DiskPlacement.add_child(vdisk)
	vdisk.transform = Transform.IDENTITY
	_inserted_disk = vdisk
	$AudioStreamPlayer3D.stream = vdisk.stream

func _on_Area_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var e: InputEventMouseButton = event as InputEventMouseButton
		if e.pressed and e.button_index == BUTTON_LEFT:
			if _inserted_disk != null:
				emit_signal("remove_disk", _inserted_disk)
				_inserted_disk = null

func _physics_process(delta):
	if $AudioStreamPlayer3D.playing:
		$DiskPlacement.rotate_y(-delta*78 / 60.0 * 2*PI)
