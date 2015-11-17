#ifndef CONTROLREADDEVICE_HPP
#define CONTROLREADDEVICE_HPP

#include <QWidget>
#include <QMenu>
#include <QPainter>
#include "ural.hpp"

namespace Ui {
class ControlReadDevice;
}

/**
 * @brief Перфолента
 */
class PunchTape
{
public:

	PunchTape();

	~PunchTape();

	void loadData(const QByteArray&);

	void saveData(QByteArray&);

	URAL::Numbers &tapeData()
	{
		return (_data);
	}

private:

	URAL::Numbers _data;
};

/**
 * @brief Виджет просмотра перфоленты
 */
class PunchTapeViewWidget : public QWidget
{
	Q_OBJECT

public:

	PunchTapeViewWidget(QWidget *parent = NULL);
	~PunchTapeViewWidget();

	void setTape(PunchTape*);

public slots:

	void setPosition(int newVal)
	{
		_position = newVal;
		this->update();
	}

protected:

	void paintEvent(QPaintEvent*) override;

private:

	void drawFrame(int);
	PunchTape  *_tape;
	QPainter    _painter;
	int         _position;
};

/**
 * @brief Виджет контрольно-считывающего устройства
 */
class ControlReadDevice : public QWidget
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

	Ui::ControlReadDevice &ui;

	PunchTape   _tape;

	QMenu   _contextMenu;
};

#endif // CONTROLREADDEVICE_HPP
