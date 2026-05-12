# URAL electronic digital computing machine module

extends Object
class_name Ural


# Hexadecimal constants
const HEX_MOST_18BIT = 0xFFFFC0000
const HEX_5BIT = 0x1F
const HEX_11BIT = 0x7FF
const HEX_18BIT = 0x3FFFF
const HEX_36BIT = 0xFFFFFFFFF

# Octal constants
const OCT_00 = 0x0
const OCT_01 = 0x1
const OCT_02 = 0x2
const OCT_03 = 0x3
const OCT_04 = 0x4
const OCT_05 = 0x5
const OCT_06 = 0x6
const OCT_07 = 0x7
const OCT_10 = 0x8
const OCT_11 = 0x9
const OCT_12 = 0xA
const OCT_13 = 0xB
const OCT_14 = 0xC
const OCT_15 = 0xD
const OCT_16 = 0xE
const OCT_17 = 0xF
const OCT_20 = 0x10
const OCT_21 = 0x11
const OCT_22 = 0x12
const OCT_23 = 0x13
const OCT_24 = 0x14
const OCT_25 = 0x15
const OCT_26 = 0x16
const OCT_27 = 0x17
const OCT_30 = 0x18
const OCT_31 = 0x19
const OCT_32 = 0x1A
const OCT_33 = 0x1B
const OCT_34 = 0x1C
const OCT_35 = 0x1D
const OCT_36 = 0x1E
const OCT_37 = 0x1F

# Half-word (Short 18-bit machine word. Command or 18-bit fixed point fraction)
class HalfWord:
	var _value: int
	
	func _init(v: int):
		_value = v & HEX_18BIT
	
	func value() -> int:
		return _value & HEX_18BIT
		
	func set_value(v: int):
		_value = v & HEX_18BIT


class Command:
	extends HalfWord
	
	func _init(v: int).(v):
		pass
		
	func opcode() -> int:
		return (self._value >> 12) & HEX_5BIT
		
	func address() -> int:
		return self._value & HEX_11BIT


# Machine word (Full 36-bit fixed point fraction in direct code)
class Word:
	var _value: int
	
	func _init(v: int):
		_value = v & 0xFFFFFFFFF
	
	func most_half(hw: HalfWord) -> int:
		return hw.set_value((_value >> 18) & HEX_18BIT)
		
	func set_most_half(hw: HalfWord):
		self._value &= HEX_18BIT
		self._value |= hw.value() << 18
		
	func least_half(hw: HalfWord) -> int:
		return hw.set_value(_value & HEX_18BIT)
		
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
var _rgk: Command = Command.new(0)

# Command decoder register (ДШК - DSHK)
var _dshk: int = 0

# Command address part register
var _given_Address: int = 0

# Arithmetic unit register (РГАУ - RGAU)
var _rg_au: Word = Word.new(0)

# RAM magnetic drum
var _drum: MagneticDrum = MagneticDrum.new()


func get_drum() -> MagneticDrum:
	return _drum


func _init():
	pass


func rgk() -> Command:
	return _rgk


func get_schk() -> int:
	return _schk
	
	
func get_dshk() -> int:
	return _dshk
	

func rgau() -> Word:
	return _rg_au

	
func clock_step():
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
	# One working tact. Executed by control unit 100 times per second
	# or from control panel with the Single step ("Однотактный режим") button
	
	# 2-stage pipeline:
	#  1. Command fetching 
	#  2. Data fetching, command decoding and execution
	# 2 commands is being processed: current command 2-nd stage,
	#   and next command first stage
	# Command counter (SCHK - СЧК) pointing to the next command address
	# Command register (RGK - РГК) contains current command
	
	# 1.1 Decoding current command opcode
	_dshk = _rgk.opcode()
	_given_Address = _rgk.address()

	# 2.1 Fetch next command
	_drum.read_half(_schk, _rgk)
	
	# X.2 Increase program counter
	_schk = _schk + 1
	print_debug(_schk)
	if _schk == 0x800:
		_schk = 0
	
	# 1.2 Executing current command
	match _dshk:
		OCT_00:
			_op_nop_00()
		OCT_22:
			_op_jmp_22()
		_:
			print_debug("FIXME: not implemented opcode: ", _dshk)
	
		
func _op_nop_00():
	pass

func _op_jmp_22():
	_schk = _given_Address
