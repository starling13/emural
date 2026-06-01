extends Node2D


func _ready():
	update_scale_and_position()
	# Listen to viewport size changes
	get_viewport().connect("size_changed", self, "update_scale_and_position")


func update_scale_and_position():
	var screen_size = get_viewport().get_visible_rect().size
	var tex_size = $panel/panel_background.texture.get_size()
	if tex_size.x == 0 or tex_size.y == 0:
		return
	# Fit: uniform scale so that both dimensions fit inside the screen
	var scale_factor = screen_size.x / tex_size.x
	#$panel/panel_background.scale = Vector2(scale_factor, scale_factor)
	#$panel/panel_background.position = screen_size * 0.5
