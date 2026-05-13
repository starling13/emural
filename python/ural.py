import enum
import random

# Hexadecimal constants
HEX_MOST_18BIT = 0xFFFFC0000
HEX_5BIT = 0x1F
HEX_11BIT = 0x7FF
HEX_18BIT = 0x3FFFF
HEX_18TH_BIT = 0x20000
HEX_35BIT = 0x7FFFFFFFF
HEX_36BIT = 0xFFFFFFFFF
HEX_36TH_BIT = 0x800000000
HEX_37BIT = 0x1FFFFFFFFF
HEX_3637_BITS = 0x1800000000

# Octal constants
OCT_00 = 0x0
OCT_01 = 0x1
OCT_02 = 0x2
OCT_03 = 0x3
OCT_04 = 0x4
OCT_05 = 0x5
OCT_06 = 0x6
OCT_07 = 0x7
OCT_10 = 0x8
OCT_11 = 0x9
OCT_12 = 0xA
OCT_13 = 0xB
OCT_14 = 0xC
OCT_15 = 0xD
OCT_16 = 0xE
OCT_17 = 0xF
OCT_20 = 0x10
OCT_21 = 0x11
OCT_22 = 0x12
OCT_23 = 0x13
OCT_24 = 0x14
OCT_25 = 0x15
OCT_26 = 0x16
OCT_27 = 0x17
OCT_30 = 0x18
OCT_31 = 0x19
OCT_32 = 0x1A
OCT_33 = 0x1B
OCT_34 = 0x1C
OCT_35 = 0x1D
OCT_36 = 0x1E
OCT_37 = 0x1F

class opcode_t(enum.Enum):
    NOP_00 = OCT_00
    JMP_22 = OCT_22


class HalfWord:
    def __init__(self, v: int):
        self._value = v & HEX_18BIT

    def value(self) -> int:
        return self._value & HEX_18BIT

    def set_value(self, v: int):
        self._value = v & HEX_18BIT

    def get_sign(self) -> bool:
        return (self._value & HEX_18TH_BIT) == 0


class Command(HalfWord):
    def __init__(self, v: int):
        super().__init__(v)

    def opcode(self) -> int:
        return (self._value >> 12) & HEX_5BIT

    def address(self) -> int:
        return self._value & HEX_11BIT


class Word:
    def __init__(self, v: int = 0):
        self._value = v & HEX_36BIT

    def most_half(self, hw: HalfWord) -> None:
        hw.set_value((self._value >> 18) & HEX_18BIT)

    def set_most_half(self, hw: HalfWord):
        self._value &= HEX_18BIT
        self._value |= hw.value() << 18

    def least_half(self, hw: HalfWord) -> None:
        hw.set_value(self._value & HEX_18BIT)

    def set_least_half(self, hw: HalfWord):
        self._value &= HEX_MOST_18BIT
        self._value |= hw.value()

    def value(self) -> int:
        return self._value & HEX_36BIT

    def set_value(self, v: int):
        self._value = v & HEX_36BIT

    def get_sign(self) -> bool:
        return ((self._value >> 35) & 1) == 1


class Adder:
    def __init__(self, v: int = 0):
        self._value = v & HEX_37BIT

    def most_half(self, hw: HalfWord) -> None:
        hw.set_value((self._value >> 18) & HEX_18BIT)

    def set_most_half(self, hw: HalfWord):
        self._value &= HEX_18BIT
        self._value |= hw.value() << 18

    def least_half(self, hw: HalfWord) -> None:
        hw.set_value(self._value & HEX_18BIT)

    def set_least_half(self, hw: HalfWord):
        self._value &= HEX_MOST_18BIT
        self._value |= hw.value()

    def value(self) -> int:
        return self._value & HEX_37BIT

    def set_value(self, v: int):
        self._value = v & HEX_37BIT

    def get_sign(self) -> int:
        return (self._value >> 35) & 3

    def set_sign(self, v: int) -> None:
        self._value = (self._value & HEX_35BIT) + ((v & 3) << 35)

    def from_word(self, w: Word) -> None:
        if w.get_sign():
            v = HEX_35BIT
        else:
            v = 0
        self._value = (w.value() & HEX_35BIT) ^ v
        self.set_sign(int(w.get_sign()) * 3)


class MagneticDrum:
    def __init__(self):
        self._data = []
        self.write_block = False
        for _ in range(1024):
            self._data.append(Word(random.randint(0, HEX_36BIT)))

    def write_half(self, address: int, value: HalfWord):
        if self.write_block:
            return
        ea = address // 2
        mod = address % 2
        if mod == 0:
            self._data[ea].set_least_half(value)
        else:
            self._data[ea].set_most_half(value)

    def read_half(self, address: int, value: HalfWord):
        ea = address // 2
        mod = address % 2
        if mod == 0:
            self._data[ea].least_half(value)
        else:
            self._data[ea].most_half(value)

    def clear(self):
        for i in range(1024):
            self._data[i].set_value(0)

class state_t(enum.Enum):
    IDLE = 0
    RUN = 1

class ECVM:
    def __init__(self):
        self._state = state_t.IDLE
        self._schk = 0
        self._rgk = Command(0)
        self._dshk = 0
        self._given_Address = 0
        self._rg_au = Word(0)
        self._drum = MagneticDrum()
        self._adder = Adder(0)

    def get_drum(self) -> MagneticDrum:
        return self._drum

    def rgk(self) -> Command:
        return self._rgk

    def get_schk(self) -> int:
        return self._schk

    def get_dshk(self) -> int:
        return self._dshk

    def adder(self) -> Adder:
        return self._adder

    def rgau(self) -> Word:
        return self._rg_au

    def set_rgau_and_adder(self, w: Word):
        self._rg_au = w
        self._adder.from_word(w)

    def clock_step(self):
        if self._state == state_t.RUN:
            self.step()

    def start(self):
        self._state = state_t.RUN

    def stop(self):
        self._state = state_t.IDLE

    def step(self):
        # X.1 Increase program counter
        self._schk = self._schk + 1
        if self._schk == 0x800:
            self._schk = 0

        # 1.2 Decoding current command opcode
        self._dshk = self._rgk.opcode()
        self._given_Address = self._rgk.address()

        # 1.3 Executing current command
        match self._dshk:
            case opcode_t.NOP_00:
                self._op_nop_00()
            case opcode_t.JMP_22:
                self._op_jmp_22()
            case _:
                pass  # нереализованные команды игнорируются

        # 2.2 Fetch next command
        self._drum.read_half(self._schk, self._rgk)

    def _op_nop_00(self):
        pass

    def _op_jmp_22(self):
        self._schk = self._given_Address
