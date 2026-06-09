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
	
	var t: ImageTexture = null
	
	t = _load_png(path + "/1.png")
	images[0] = t
	
	t = _load_png(path + "/2.png")
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

func _load_png(path: String) -> ImageTexture:
	# 1. Load the raw image data
	var image: Image
	
	var texture: ImageTexture
	
	var res: ImageTexture
	
	image = Image.new()
	if image.load(path) != OK:
		printerr("Failed to load image from path: ", path)
		return res

	# 2. Create a texture from the loaded image data
	texture = ImageTexture.new()
	texture.create_from_image(image)

	return texture
