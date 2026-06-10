class_name VinilDiskStack
extends Spatial


signal disk_selected

const disks_path = "user://vinil_disks"

var _disks: Array = []

var selected_disk: int = -1

var side: int = 0


func _ready():
	var dir: Directory
	var folder: String
	var disk: VinilDisk
	
	dir = Directory.new()

	if dir.open(disks_path) != OK:
		push_error("Directory \"vinil_disks\" is not available")
	
	dir.list_dir_begin(true, true)
	while true:
		folder=dir.get_next()
		if folder == "":
			break
		_disks.append(disks_path+"/"+folder)
		selected_disk = 0
	dir.list_dir_end()
	
	_update_disk_sprite()


func take_disk(index: int) -> VinilDiskScene:
	var vdisk: VinilDisk
	var sc: PackedScene
	var res: VinilDiskScene
	var vdisk_path: String
	
	vdisk = VinilDisk.new()
	vdisk_path = _disks.pop_at(index)
	vdisk.load_from_dir(vdisk_path)
	
	sc = load("res://audio/vinil_disk_scene.tscn")
	res = sc.instance()
	res.set_disk(vdisk)
	
	while _disks.size()-1 < selected_disk:
		selected_disk -= 1
	
	return res


func _on_StaticBody_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var mb_event: InputEventMouseButton = event as InputEventMouseButton
		if mb_event.button_index == BUTTON_LEFT:
			$Sprite3D.visible = true


func _update_disk_sprite():
	if selected_disk >= 0:
		var disk = VinilDisk.new()
		disk.load_from_dir(_disks[selected_disk])
		$Sprite3D.texture = disk.images[side]
	else:
		$Sprite3D.texture = null


func _on_Area_input_event(camera, event, position, normal, shape_idx):
	if event is InputEventMouseButton:
		var mb_event: InputEventMouseButton = event as InputEventMouseButton
		if mb_event.button_index == BUTTON_MASK_RIGHT:
			$Sprite3D.visible = false
		
		if $Sprite3D.visible:
			if mb_event.button_index == BUTTON_MIDDLE:
				side = 1 - side
			if mb_event.button_index == BUTTON_WHEEL_UP:
				selected_disk += 1
			elif mb_event.button_index == BUTTON_WHEEL_DOWN:
				selected_disk -= 1
			if selected_disk >= _disks.size():
				selected_disk = 0
			if selected_disk < 0:
				selected_disk = _disks.size()-1
			_update_disk_sprite()
			if selected_disk < 0:
				return
			
			if mb_event.button_index == BUTTON_LEFT and mb_event.pressed:
				var disk: VinilDiskScene = take_disk(selected_disk)
				_update_disk_sprite()
				if disk != null:
					emit_signal("disk_selected", disk)
