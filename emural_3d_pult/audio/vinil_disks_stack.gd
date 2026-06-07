class_name VinilDiskStack
extends Spatial

const disks_path = "user://vinil_disks"
var disks: Array = []

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
		print_debug(folder)
		
		disk = VinilDisk.new()
		disk.load_from_dir(disks_path+"/"+folder)
		disks.append(disk)
		
	dir.list_dir_end()
