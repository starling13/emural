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
