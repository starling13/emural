/*
 * This file is part of EMURAL - emulator for Ural computer from 1950s
 * Copyright (C) 2015-2024 Andrey V. Skvortsov <starling13@gmail.com>
 *
 * EMURAL is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "qcommon.hpp"

#include <QFileDialog>
#include <QDebug>

void TapeLoader::loadTapeFromFile()
{
	QString fileName;

	fileName = QFileDialog::getOpenFileName(0, QString::fromUtf8(
	    u8"ыбор файла перфоленты для загрузки"), QDir::homePath(), "*.upt");
	if (!fileName.isEmpty()) {
		QFile file(fileName);
		if (file.open(QFile::ReadOnly)) {
			QByteArray ba, line, bytes(11, Qt::Uninitialized);
			while (true) {
				line = file.readLine(file.size());
				bytes.clear();
				if (line.isEmpty())
					break;
				if (line[0] == '#')
					continue;
				if (line.size() < 11) {
					qWarning() << QString::fromUtf8(u8"Слишком короткая строка");
					continue;
				}
				for (int i=0; i<11; ++i) {
					char c = line[i];
					if (isdigit(c))
						bytes[i] = std::atoi(std::string("").append(1, c).c_str());
					else
						qWarning() << QString::fromUtf8(u8"Не цифра") << int (c);
				}
				ba.append(bytes);
			};
			_tape.loadData((const uint8_t*)(ba.data()), ba.size());
		} else
			qWarning() << QString::fromUtf8(u8"евозможно открыть файл") << fileName;
	}
}
