#!/usr/bin/env python3

import curses
import time
import random
import enum

import ural

# ============================================================
# ncurses интерфейс
# ============================================================

def format_bits(value: int, bits: int, on_char: str = '█', off_char: str = '░') -> str:
    """
    Возвращает строку из `bits` символов, отображающих двоичное представление
    числа `value` (старший бит слева).
    """
    result = []
    for i in range(bits - 1, -1, -1):
        if (value >> i) & 1:
            result.append(on_char)
        else:
            result.append(off_char)
        result.append(' ')
        result.append(' ')
    result=''.join(result)

    return result


def draw_registers(stdscr, ecvm: ural.ECVM) -> None:
    """Отрисовывает все панели с лампами и текущее состояние."""
    # Получаем значения регистров
    adder_val = ecvm.adder().value()
    rgau_val = ecvm.rgau().value()
    rgk_val = ecvm.rgk().value()
    dshk_val = ecvm.get_dshk()
    schk_val = ecvm.get_schk()
    state_str = "RUN" if ecvm._state == ural.state_t.RUN else "IDLE"

    # Формируем строки для вывода
    lines = [
        "═" * 79,
        "          УРАЛ-1  ЭМУЛЯТОР          ",
        "═" * 79,
        f"Состояние: {state_str}",
        "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗",
        "║                             С      У      М      М      А      Т      О      Р                                  ║",
        "║ "+format_bits(adder_val, 37, on_char='●', off_char='○')+" ║",
        "║ "+"".join([f"{x:2d} " for x in range(37, 0, -1)])+" ║",
        "║       Р  Е  Г  И  С  Т  Р    А  Р  И  Ф  М  Е  Т  И  Ч  Е  С  К  О  Г  О    У  С  Т  Р  О  Й  С  Т  В  А        ║",
        "║  "+format_bits(rgau_val, 36, on_char='●', off_char='○')+"   ║",
        "║  "+"".join([f"{x:2d} " for x in range(36, 0, -1)])+"   ║",
        "║ НОМЕР ОПЕРАЦИИ     С Ч Ё Т Ч И К  К О М А Н Д                     Р  Е  Г  И  С  Т  Р    К  О  М  А  Н  Д       ║",
        "║ "+format_bits(dshk_val, 5, on_char='●', off_char='○') + "  " +
        format_bits(schk_val, 11, on_char='●', off_char='○') + "        "+
        format_bits(rgk_val, 18, on_char='●', off_char='○') + "║",
        "║"+"".join([f"{x:2d} " for x in range(5, 0, -1)]) + "  " +
        "".join([f"{x:2d} " for x in range(11, 0, -1)]) + "         "+
        "  "+"".join([f"{x:2d} " for x in range(5, 0, -1)]) +
        "".join([f"{x:2d} " for x in range(12, 0, -1)]) + " ║",
        "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝",
    ]

    h, w = stdscr.getmaxyx()
    for i, line in enumerate(lines):
        if i < h:
            # Обрезаем строку, если она шире окна
            stdscr.addstr(i, 0, line[:w - 1])
    stdscr.refresh()


def init_colors() -> None:
    if curses.has_colors():
        curses.start_color()
        # Попробуем использовать 208 цвет (оранжевый), если терминал поддерживает 256 цветов
        if curses.COLORS >= 256:
            # 208 — оранжевый в палитре xterm-256color
            curses.init_pair(1, 208, curses.COLOR_BLACK)
        else:
            # Если 256 нет, используем жёлтый (ближайший к оранжевому)
            curses.init_pair(1, curses.COLOR_YELLOW, curses.COLOR_BLACK)

def draw_panel(stdscr) -> None:
    h, w = stdscr.getmaxyx()

    lines = [
        "╔═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╗",
        "║ Магнитный барабан  Остановка Пуск Однотактный                                [Q] Выход                          ║",
        "║           СТИРАНИЕ                   режим                                                                      ║",
        "║             [E]       [T]     [R]     [S]                                                                       ║",
        "╚═════════════════════════════════════════════════════════════════════════════════════════════════════════════════╝",
    ]

    for i, line in enumerate(lines):
        if i < h:
            # Обрезаем строку, если она шире окна
            stdscr.addstr(i+16, 0, line[:w - 1])
    stdscr.refresh()

def main(stdscr) -> None:
    """Главный цикл интерфейса curses."""
    # Инициализация curses
    curses.curs_set(0)          # убираем курсор
    stdscr.nodelay(1)           # неблокирующий ввод
    stdscr.clear()

    init_colors()

    # Создаём экземпляр эмулятора
    ecvm = ural.ECVM()

    # Переменная для ограничения частоты шагов в автоматическом режиме (~100 Гц)
    last_step_time = time.time()

    # Начальная отрисовка
    draw_registers(stdscr, ecvm)
    draw_panel(stdscr)

    while True:
        # Обработка ввода с клавиатуры
        key = stdscr.getch()
        if key != -1:
            if key in (ord('q'), ord('Q')):
                break
            elif key in (ord('s'), ord('S')):
                ecvm.step()
                draw_registers(stdscr, ecvm)
            elif key in (ord('r'), ord('R')):
                ecvm.start()
            elif key in (ord('t'), ord('T')):
                ecvm.stop()
            elif key in (ord('e'), ord('E')):
                ecvm.get_drum().clear()

        # Автоматический режим (если состояние RUN)
        if ecvm._state == ural.state_t.RUN:
            now = time.time()
            if now - last_step_time >= 0.01:   # 10 мс -> 100 тактов/сек
                ecvm.clock_step()
                last_step_time = now
                draw_registers(stdscr, ecvm)
        else:
            # В режиме IDLE просто даём процессору отдохнуть
            time.sleep(0.01)
            # Обновляем экран на случай, если состояние изменилось извне
            draw_registers(stdscr, ecvm)

        # Небольшая пауза для снижения нагрузки на процессор
        time.sleep(0.001)


if __name__ == "__main__":
    curses.wrapper(main)
