extends HandItem
class_name VinilDisk

var track_id: int = -1
var stream: AudioStreamOGGVorbis = null

func _ready():
	pass
	
func set_track_id(tid: int) -> void:
	stream=load("res://audio/"+str(tid)+".ogg")
	$MeshInstance2.get_active_material(0).albedo_texture = load("res://audio/"+str(tid)+".png")
