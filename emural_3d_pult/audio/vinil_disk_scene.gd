extends HandItem
class_name VinilDiskScene


var _disk_item: VinilDisk


func _ready():
	pass


func set_disk(d: VinilDisk) -> void:
	_disk_item = d
	print_debug($side_1_label)
	print_debug($side_2_label)
	$side_1_label.texture = d.images[0]
	$side_2_label.texture = d.images[1]


func disk_item() -> VinilDisk:
	return _disk_item
