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
