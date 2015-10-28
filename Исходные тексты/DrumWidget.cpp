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

#include "DrumWidget.hpp"

#include <cstring>

#include <QResizeEvent>
#include <QDebug>
#include <qt4/QtGui/qmessagebox.h>

DrumWidget::DrumWidget(URAL::Word_t (&drum)[URAL::drumWordsNumber]) :
_format(OCT),
_drum(drum),
_position(0ul)
{
	widget.setupUi(this);
	
	widget.formatGroup->setId(widget.octSwitch, OCT);
	widget.formatGroup->setId(widget.binSwitch, BIN);
}

DrumWidget::~DrumWidget()
{
}

void DrumWidget::resizeEvent(QResizeEvent *event)
{
	QWidget::resizeEvent(event);
	updateView();
}

void DrumWidget::setPosition(int newVal)
{
	qDebug() << __PRETTY_FUNCTION__ << newVal;
	this->_position = newVal;
	this->updateView();
}

void DrumWidget::on_drumScroll_valueChanged(int value)
{
	qDebug() << __PRETTY_FUNCTION__ << value;
	this->setPosition(value);
}

void DrumWidget::on_formatGroup_buttonClicked(int newVal)
{
	Q_ASSERT((newVal == OCT) || (newVal == BIN));
	
	this->_format = Format(newVal);
	this->updateView();
}

void DrumWidget::on_drumView_cellChanged(int row, int col)
{
	bool	ok;
	uint	data;
	size_t	wordNumber;
	
	data = this->widget.drumView->item(row, col)->text().toUInt(&ok,
	    int(this->_format));
	wordNumber = this->_position / 2 + row;
	
	if (col == 0)
		this->_drum[wordNumber].halfWords.most = data;
	else if (col == 1)
		this->_drum[wordNumber].halfWords.least = data;
	else
		qWarning() << u8"Недопустимый номер столбца" << col;
}

void DrumWidget::on_clearButton_clicked()
{
	if (QMessageBox::question(this, QString::fromUtf8(u8"Очистка ОЗУ"),
	    QString::fromUtf8(u8"Очистить все ячейки магнитного барабана?"),
	    QString::fromUtf8(u8"Да"), QString::fromUtf8(u8"Нет")) == 0) {
		std::memset(&this->_drum, 0, sizeof (this->_drum));
		this->updateView();
	}
}

void DrumWidget::updateView()
{
	size_t			 rowCount;
	QTableWidgetItem	*item;
	
	this->widget.drumView->blockSignals(true);
	
	this->widget.drumView->setRowCount(1);	
	rowCount = this->widget.drumView->height() /
	    this->widget.drumView->rowHeight(0) - 1;

	if (this->_position + rowCount > 2046)
		rowCount = (2048-this->_position) / 2;
	
	this->widget.drumView->setRowCount(rowCount);
	for (size_t i=0; i<rowCount; ++i) {
		size_t wordIndex = _position / 2 + i;
		
		item = new QTableWidgetItem(QString("0").append(
		    QString::number(this->_position + 2*i, 8)));
		this->widget.drumView->setVerticalHeaderItem(i, item);

		item = new QTableWidgetItem(QString::number(
		    _drum[wordIndex][2].data, int(this->_format)));
		this->widget.drumView->setItem(i, 0, item);
		
		item = new QTableWidgetItem(QString::number(
		    _drum[wordIndex][1].data, int(this->_format)));
		this->widget.drumView->setItem(i, 1, item);
	}
	
	this->widget.drumView->blockSignals(false);
}
