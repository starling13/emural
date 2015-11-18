/*
 *   emural - эмулятор ЭЦВМ семейства "Урал"
 *
 *   Copyright (C) 2015 А.В. Скворцов <starling13@gmail.com>
 *
 *   Данная программа является свободным программным обеспечением. Вы
 *   вправе распространять её и/или модифицировать в соответствии с
 *   условиями версии 2, либо по вашему выбору с условиями более поздней
 *   версии Стандартной Общественной Лицензии GNU, опубликованной Free
 *   Software Foundation.
 *
 *   Мы распространяем данную программу в надежде на то, что она будет
 *   вам полезной, однако НЕ ПРЕДОСТАВЛЯЕМ НА НЕЁ НИКАКИХ ГАРАНТИЙ, в том
 *   числе ГАРАНТИИ ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ПРИГОДНОСТИ ДЛЯ
 *   ИСПОЛЬЗОВАНИЯ В КОНКРЕТНЫХ ЦЕЛЯХ. Для получения более подробной
 *   информации ознакомьтесь со Стандартной Общественной Лицензией GNU.
 *
 *   Вместе с данной программой вы должны были получить экземпляр
 *   Стандартной Общественной Лицензии GNU. Если вы его не получили,
 *   сообщите об этом в Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
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
