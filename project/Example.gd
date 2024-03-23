extends Example

func _ready():
	exposed_method()
	
	print(get_preload())
	$Sprite2D.texture = get_preload()
	get_node("2356362")
	var a = [1]
	get_ref(a)
	
	#get_tree().create_timer(5).timeout.connect(get_tree().quit)
