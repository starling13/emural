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

#include <cstdlib>
#include <iostream>

#include <QTimer>
#include <QApplication>
#include <QThread>

#include "DrumWidget.hpp"
#include "PultWIdget.hpp"
#include "PanelWidget.hpp"
#include "AuxControlsWidget.hpp"
#include "printdevice.hpp"
#include "ural_cpu.hpp"
#include "qural.hpp"
#include "punchdrives.hpp"

using namespace std;

int main(int argc, char** argv)
{
	int		res;
	QApplication	app(argc, argv);
	
	{
		QtPrintDevice		pDevice;
		QtPunchDrive		punchDrive;
		URAL::CPU		ural(pDevice, punchDrive);
		DrumWidget		drumWidget(ural.drum);
		PultWIdget		pultWidget(ural);
		PanelWidget		panelWidget(ural);
		AuxControlsWidget	auxControlWidget(ural);
		URALWrapper		wrapper(ural);
		QThread			uralThread;

		wrapper.moveToThread(&uralThread);

		QObject::connect(&auxControlWidget, SIGNAL(controlRegisterAddressChanged(size_t)),
				 &panelWidget, SLOT(controlRegisterUpdated()));
		QObject::connect(&pultWidget, SIGNAL(regsUpdated()),
				 &panelWidget, SLOT(updateRegisters()));
		QObject::connect(&wrapper, SIGNAL(stopped()),
				 &drumWidget, SLOT(updateView()));
		QObject::connect(&pultWidget, SIGNAL(singleStep()),
				 &wrapper, SLOT(singleStep()), Qt::QueuedConnection);
		QObject::connect(&pultWidget, SIGNAL(start()),
				 &wrapper, SLOT(start()));
		QObject::connect(&pultWidget, SIGNAL(stop()),
				 &wrapper, SLOT(stop()));
		QObject::connect(&wrapper, SIGNAL(tactFinished()),
				 &panelWidget, SLOT(updateRegisters()), Qt::QueuedConnection);
		QObject::connect(&wrapper, SIGNAL(stopped()),
				 &panelWidget, SLOT(updateRegisters()), Qt::QueuedConnection);
		QObject::connect(&auxControlWidget, SIGNAL(printMode(bool)),
				 &pDevice, SLOT(setMode(bool)));

		pDevice.start();
		uralThread.start();

		drumWidget.show();
		pultWidget.show();
		panelWidget.show();
		auxControlWidget.show();
		pDevice.show();
		punchDrive.show();

		res = app.exec();
	}
	
	return (res);
}
