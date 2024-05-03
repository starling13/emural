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

#ifndef _CONTROLREGISTERPANEL_HPP
#define	_CONTROLREGISTERPANEL_HPP

#include "ui_ControlRegisterPanel.h"
#include "ui_AdderRegisterPanel.h"
#include "ui_PCWIdget.h"
#include "ui_ArithmUnitRegisterPanel.h"
#include "ui_CommandRegisterPanel.h"
#include "ui_CommandDecoderWidget.h"
#include "ui_StatusRegisterPanel.h"
#include "ui_ModesPanel.h"

#include "ural.hpp"

namespace Ui
{
    class StopReasonsPanel;
    class DebugPanel;
}

/**
 * Панель индикаторных тиратронов одного регистра
 */
class LampPanel : public QWidget
{
	Q_OBJECT
	    
public:
	
	LampPanel(QWidget *parent = 0);
	
	virtual ~LampPanel() = default;
	
	void setValue(uint64_t);
	
protected:

	/**
	 * Масив изображений отключенного и включенного тиратрона
	 */
	static const QPixmap	*_lampPixmaps[2];
	/**
	 * Массив индикаторных тиратронов одного регистра
	 */
	QVector<QLabel*>	 _lamps;
};

/**
 * Панель тиратронов контрольного регистра
 */
class ControlRegisterPanel : public LampPanel
{
	Q_OBJECT
	
public:
	
	ControlRegisterPanel(QWidget *parent = 0);
	
	~ControlRegisterPanel();
	
private:
	
	Ui::ControlRegisterPanel widget;
};

/**
 * Панель тиратронов контрольного регистра
 */
class AdderRegisterPanel : public LampPanel
{
	Q_OBJECT
	
public:
	
	AdderRegisterPanel(QWidget *parent = 0);
	
	~AdderRegisterPanel();
	
private:
	
	Ui::AdderRegisterPanel widget;
};

/**
 * Панель тиратронов счётчика команд
 */
class PCWidget : public LampPanel
{
	Q_OBJECT
	
public:
	
	PCWidget(QWidget *parent = 0);
	
	~PCWidget();
	
private:
	
	Ui::PCWIdget widget;
};

/**
 * Панель тиратронов регистра арифметического устройства
 */
class ArithmUnitRegisterPanel : public LampPanel
{
	Q_OBJECT
	
public:
	
	ArithmUnitRegisterPanel(QWidget *parent = 0);
	
	~ArithmUnitRegisterPanel();
	
private:
	
	Ui::ArithmUnitRegisterPanel widget;
};

/**
 * Панель тиратронов регистра команд
 */
class CommandRegisterPanel : public LampPanel
{
	Q_OBJECT
	
public:
	
	CommandRegisterPanel(QWidget *parent = 0);
	
	~CommandRegisterPanel();
	
private:
	
	Ui::CommandRegisterPanel widget;
};

class CommandDecoderWidget : public LampPanel
{
	Q_OBJECT
	
public:
	
	CommandDecoderWidget(QWidget *parent = 0);
	
	~CommandDecoderWidget();
	
private:
	
	Ui::CommandDecoderWidget widget;
};

class StatusRegisterPanel : public LampPanel
{
	Q_OBJECT
	
public:
	
	StatusRegisterPanel(QWidget *parent = 0);
	
	~StatusRegisterPanel();
	
private:
	
	Ui::StatusRegisterPanel widget;
};

/**
 * @brief Панель режимов работы
 */
class ModesPanel : public LampPanel
{
    Q_OBJECT

public:

    ModesPanel(QWidget *parent = 0);

    ~ModesPanel();

private:

    Ui::ModesPanel widget;
};

class StopReasonsPanel : public LampPanel
{
    Q_OBJECT

public:

    StopReasonsPanel(QWidget *parent = 0);

    ~StopReasonsPanel();

private:

    Ui::StopReasonsPanel &widget;
};

class DebugPanel : public LampPanel
{
    Q_OBJECT

public:

    DebugPanel(QWidget *parent = 0);

    ~DebugPanel();

private:

    Ui::DebugPanel &widget;
};

#endif	/* _CONTROLREGISTERPANEL_HPP */
