extends Node2D


# Called when the node enters the scene tree for the first time.
func _ready():
	$panel/panel_background.scale = \
		
		$panel/panel_background.texture.get_size().x


# Called every frame. 'delta' is the elapsed time since the previous frame.
#func _process(delta):
#	pass
