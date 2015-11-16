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

#include "delegates.hpp"

#include <QDebug>

NumberDelegate::NumberDelegate(int bitCount, URAL::Format format, QObject *parent) :
	QItemDelegate(parent),
	_bitCount(bitCount),
	_format(format)
{
	switch (_format) {
	case URAL::BIN :
		_mask.fill('B', _bitCount);
		_validator = new QRegExpValidator(QRegExp(QString("[01]{%1}").arg(
								  _bitCount)), this);
		break;
	case URAL::OCT :
		_mask.fill('9', _bitCount / 3);
		_validator = new QRegExpValidator(QRegExp(QString("[0-7]{%1}").arg(
								  _bitCount / 3)), this);
		break;
	case URAL::DEC :
		_mask.fill('9', _bitCount / 4);
		_validator = new QRegExpValidator(QRegExp(QString("[0-9]{%1}").arg(
								  _bitCount / 4)), this);
		break;
	}
}

NumberDelegate::~NumberDelegate()
{

}

QWidget *NumberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &,
	const QModelIndex &) const
{
	ReplaceLineEdit *edit = new ReplaceLineEdit(parent);
	edit->setInputMask(_mask);
	QObject::connect(edit, SIGNAL(editingFinished()), this, SLOT(commitAndCloseEditor()));
	edit->setValidator(_validator);
	return (edit);
}

void NumberDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	QString str = index.model()->data(index, Qt::DisplayRole).toString();
	ReplaceLineEdit *edit = qobject_cast<ReplaceLineEdit*>(editor);
	edit->setText(str);
}

void NumberDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
	const QModelIndex &index) const
{
	ReplaceLineEdit *edit = qobject_cast<ReplaceLineEdit*>(editor);
	model->setData(index, edit->text());
	qDebug() << edit->text();
}

void NumberDelegate::commitAndCloseEditor()
{
	ReplaceLineEdit *editor = qobject_cast<ReplaceLineEdit*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
