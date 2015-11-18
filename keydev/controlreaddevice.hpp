#ifndef CONTROLREADDEVICE_HPP
#define CONTROLREADDEVICE_HPP

#include <QWidget>
#include <QMenu>
#include <QPainter>

#include "ural.hpp"
#include "qcommon.hpp"

namespace Ui {
class ControlReadDevice;
}

/**
 * @brief Виджет просмотра перфоленты
 */
class PunchTapeViewWidget : public QWidget
{
	Q_OBJECT

public:

	PunchTapeViewWidget(QWidget *parent = NULL);
	~PunchTapeViewWidget();

	void setTape(URAL::PunchTape*);

public slots:

	void setPosition(int newVal)
	{
		_position = newVal;
		this->update();
	}

protected:

	void paintEvent(QPaintEvent*) override;

private:

	void	drawFrame(size_t);

	URAL::PunchTape	*_tape;
	QPainter	 _painter;
	size_t		 _position;
};

/**
 * @brief Виджет контрольно-считывающего устройства
 */
class ControlReadDevice : public QWidget, public TapeLoader
{
	Q_OBJECT

public:

	ControlReadDevice(QWidget *parent = NULL);

	~ControlReadDevice();

	void punchNumber(URAL::Number);

protected:

	void contextMenuEvent(QContextMenuEvent*) override;

private slots:

	void newTape();
	void loadTape();
	void saveTape();

private:

	Ui::ControlReadDevice	&ui;

	QMenu			 _contextMenu;
};

#endif // CONTROLREADDEVICE_HPP
