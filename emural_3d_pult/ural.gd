extends Node

class HalfWord:
	var _value: int
	
	func _init(v: int):
		_value = v
	
	func value() -> int:
		return _value & 0x3FFFF
		
	func set_value(v: int):
		_value = v & 0x3FFFF


class Word:
	var _value: int
	
	func _init(v: int):
		_value = v
	
	func most_half(hw: HalfWord) -> int:
		return hw.set_value((_value >> 18) & 0x3FFFF)
		
	func least_half(hw: HalfWord) -> int:
		return hw.set_value(_value & 0x3FFFF)
		
	func value() -> int:
		return _value & 0xFFFFFFFFF


# CPU state enum
enum state_t {IDLE=0, RUN=1}

# Current state
var _state: int = state_t.RUN

# Command counter (СЧК - SCHK)
var _schk: int = 0

# Command register (РГК - RGK)
var _rgk: HalfWord = HalfWord.new(0)

# Magnetic drum (RAM)
var _drum: Array = []

func _init():
	print("URAL CPU init")
	
	for i in range(1024):
		_drum.append(Word.new(0))
	
func _ready():
	print("URAL CPU ready")
	
	
func get_rgk() -> HalfWord:
	return _rgk

	
func _physics_process(delta):
	match _state:
		state_t.IDLE:
			pass
		state_t.RUN:
			step()
	
func step():
	var ea = _schk / 2
	var mod = _schk % 2
	
	var command: HalfWord = HalfWord.new(0)
	if mod == 1:
		_rgk = _drum[ea].most_half(command)
	else:
		_rgk = _drum[ea].least_half(command)

	_schk  = _schk + 1
	if _schk == 0x800:
		_schk = 0
