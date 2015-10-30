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

#ifndef _CONTROLREGISTERPANEL_HPP
#define	_CONTROLREGISTERPANEL_HPP

#include "ui_ControlRegisterPanel.h"
#include "ui_AdderRegisterPanel.h"
#include "ui_PCWIdget.h"
#include "ui_ArithmUnitRegisterPanel.h"
#include "ui_CommandRegisterPanel.h"

#include "ural.hpp"

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

#endif	/* _CONTROLREGISTERPANEL_HPP */
