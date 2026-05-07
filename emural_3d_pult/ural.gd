# URAL electronic digital computing machine module
extends Node
class_name Ural

const HEX_LEAST_18BIT = 0x3FFFF
const HEX_MOST_18BIT = 0xFFFFC0000
const HEX_36BIT = 0xFFFFFFFFF
const HEX_5BIT = 0x1F

# Half-word (Short 18-bit machine word. Command or 18-bit fixed point fraction)
class HalfWord:
	var _value: int
	
	func _init(v: int):
		_value = v & HEX_LEAST_18BIT
	
	func value() -> int:
		return _value & HEX_LEAST_18BIT
		
	func set_value(v: int):
		_value = v & HEX_LEAST_18BIT


class Command:
	extends HalfWord
	
	func _init(v: int).(v):
		pass
		
	func opcode() -> int:
		return (self._value >> 12) & HEX_5BIT


# Machine word (Full 36-bit fixed point fraction in direct code)
class Word:
	var _value: int
	
	func _init(v: int):
		_value = v & 0xFFFFFFFFF
	
	func most_half(hw: HalfWord) -> int:
		return hw.set_value((_value >> 18) & HEX_LEAST_18BIT)
		
	func set_most_half(hw: HalfWord):
		self._value &= HEX_LEAST_18BIT
		self._value |= hw.value() << 18
		
	func least_half(hw: HalfWord) -> int:
		return hw.set_value(_value & HEX_LEAST_18BIT)
		
	func set_leasr_half(hw: HalfWord):
		self._value &= HEX_MOST_18BIT
		self._value |= hw.value()
		
	func value() -> int:
		return _value & 0xFFFFFFFFF
	
	func set_value(v: int):
		_value = v & 0xFFFFFFFFF

# Magnetic drum (RAM)
class MagneticDrum:
	# RAM cells
	var _data: Array = []
	# Write block
	var write_block: bool = false
	
	func _init():
		for i in range(1024):
			_data.append(Word.new(randi()))
	
	func write_half(address: int, value: HalfWord):
		if write_block:
			return
		
		var ea: int = address / 2
		var mod: int = address % 2
		
		if mod == 0:
			_data[ea].set_leasr_half(value)
		else:
			_data[ea].set_most_half(value)
			
	func read_half(address: int, value: HalfWord):
		var ea: int = address / 2
		var mod: int = address % 2
		
		if mod == 0:
			_data[ea].least_half(value)
		else:
			_data[ea].most_half(value)
			
	func clear():
		for i in range(1024):
			_data[i].set_value(0)


# CPU state enum
enum state_t {IDLE=0, RUN=1}

# Current state
var _state: int = state_t.IDLE

# Command counter (СЧК - SCHK)
var _schk: int = 0

# Command register (РГК - RGK)
var _rgk: HalfWord = HalfWord.new(0)

# RAM
var _drum: MagneticDrum = MagneticDrum.new()


func _init():
	print("URAL CPU init")
	

func _ready():
	print("URAL CPU ready")
	
	_drum.clear()
	
func get_rgk() -> HalfWord:
	return _rgk


func get_schk() -> int:
	return _schk

	
func _physics_process(delta):
	match _state:
		state_t.IDLE:
			pass
		state_t.RUN:
			step()


func start():
	_state = state_t.RUN


func stop():
	_state = state_t.IDLE


func step():
	if _schk == 0x800:
		_schk = 0
	
	var command: Command = Command.new(0)
	_rgk = _drum.read_half(_schk, command)
	
	match command.opcode():
		0:
			self._op_nop_00()
		
func _op_nop_00():
	_schk  = _schk + 1
