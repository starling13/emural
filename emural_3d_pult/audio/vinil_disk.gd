class_name VinilDisk
extends Object

var audio_streams: Array = [
	null, null
]

var images: Array = [
	null, null
]

func init_from_dir(path: String) -> void:
	var s: AudioStreamOGGVorbis = null
	
	s = load(path + "1.ogg")
	audio_streams[0] = s
	
	s = load(path + "2.ogg")
	audio_streams[1] = s
	
	
