class_name VinilDisk
extends Object

var audio_streams: Array = [
	null, null
]

var images: Array = [
	null, null
]

func load_from_dir(path: String) -> void:
	var s: AudioStreamOGGVorbis
	var f: File
	var fpath: String
	
	s = _load_ogg(path + "/1.ogg")
	audio_streams[0] = s
	
	s = _load_ogg(path + "/2.ogg")
	audio_streams[1] = s
	
	var t: StreamTexture = null
	
	t = load(path + "/1.png")
	images[0] = t
	
	t = load(path + "/2.png")
	images[1] = t
	
func _load_ogg(fpath: String) -> AudioStreamOGGVorbis:
	var res: AudioStreamOGGVorbis = null
	var data: PoolByteArray
	var f: File
	
	f = File.new()
	if not f.file_exists(fpath):
		push_error("No such file: " + fpath)
		return null
	else:
		print_debug("Found file: " + fpath)
	
	f.open(fpath, File.READ)
	data = f.get_buffer(f.get_len())
	f.close()
	
	res = AudioStreamOGGVorbis.new()
	res.data = data
	
	return res
