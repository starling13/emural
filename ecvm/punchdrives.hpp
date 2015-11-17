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

#ifndef PUNCHDRIVES_HPP
#define PUNCHDRIVES_HPP

#include "ural.hpp"

#include <QWidget>
#include <QMutex>
#include <QWaitCondition>

class QtPunchDrive : public QWidget, public URAL::IExtMemoryDevice
{
	Q_OBJECT

public:

	QtPunchDrive();
	~QtPunchDrive();

//	URAL::Word_t	readWord() override;

//	URAL::HalfWord_t readHalfWord() override;
private:

	QMutex	_lock;
	QWaitCondition	_uralCond, tapeCond;
	URAL::Numbers	_tape;
};

#endif // PUNCHDRIVES_HPP
