/*
 *   Данная программа является свободным программным обеспечением. Вы
 *   вправе распространять её и/или модифицировать в соответствии с
 *   условиями версии 2, либо по вашему выбору с условиями более поздней
 *   версии Стандартной Общественной Лицензии GNU, опубликованной Free
 *   Software Foundation.

 *   Мы распространяем данную программу в надежде на то, что она будет
 *   вам полезной, однако НЕ ПРЕДОСТАВЛЯЕМ НА НЕЁ НИКАКИХ ГАРАНТИЙ, в том
 *   числе ГАРАНТИИ ТОВАРНОГО СОСТОЯНИЯ ПРИ ПРОДАЖЕ и ПРИГОДНОСТИ ДЛЯ
 *   ИСПОЛЬЗОВАНИЯ В КОНКРЕТНЫХ ЦЕЛЯХ. Для получения более подробной
 *   информации ознакомьтесь со Стандартной Общественной Лицензией GNU.

 *   Вместе с данной программой вы должны были получить экземпляр
 *   Стандартной Общественной Лицензии GNU. Если вы его не получили,
 *   сообщите об этом в Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <cstdlib>
#include <iostream>

#include <QTimer>
#include <QApplication>

#include "DrumWidget.hpp"
#include "PultWIdget.hpp"
#include "PanelWidget.hpp"
#include "AuxControlsWidget.hpp"
#include "printdevice.hpp"
#include "ural_cpu.hpp"

using namespace std;

int main(int argc, char** argv)
{
	int		res;
	QApplication	app(argc, argv);
	
	FixedPointFraction<uint64_t, 36>::SignedMagnitude	a;
	
	{
        Q_DECLARE_METATYPE(URAL::HalfWord_t);

		URAL::CPU	ural;
		DrumWidget	drumWidget(ural.drum);
		PultWIdget	pultWidget(ural);
		PanelWidget	panelWidget(ural);
		AuxControlsWidget auxControlWidget(ural);
        PrintDevice pDevice;
		
		QObject::connect(&auxControlWidget, SIGNAL(controlRegisterAddressChanged(size_t)),
		    &panelWidget, SLOT(controlRegisterUpdated()));
		QObject::connect(&pultWidget, SIGNAL(tactFinished()),
		    &panelWidget, SLOT(updateRegisters()));
        QObject::connect(&pultWidget, SIGNAL(stopped()),
            &drumWidget, SLOT(updateView()));
        QObject::connect(&auxControlWidget, SIGNAL(printMode(bool)),
            &pDevice, SLOT(setMode(bool)));
        QObject::connect(&auxControlWidget, SIGNAL(printAdder(quint64)),
            &pDevice, SLOT(printWord(quint64)));
	
		drumWidget.show();
		pultWidget.show();
		panelWidget.show();
		auxControlWidget.show();
        pDevice.show();
	
		res = app.exec();
	}
	
	return (res);
}
