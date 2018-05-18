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

#include "intdelegate.hpp"

IntDelegate::IntDelegate(QObject *parent,
        int iMin, int iMax, int iStep) : QItemDelegate(parent),
        min(iMin),
        max(iMax),
        step(iStep)
{

}

IntDelegate::~IntDelegate()
{
}

QWidget *IntDelegate::createEditor(QWidget *parent, const
QStyleOptionViewItem&, const QModelIndex&) const
{
   QSpinBox *edit = new QSpinBox(parent);
   edit->setValue(0);
   edit->setMinimum(min);
   edit->setMaximum(max);
   edit->setSingleStep(step);

   connect(edit, SIGNAL(editingFinished()),
           this, SLOT(commitAndCloseEditor()));

   return edit;
}


void IntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
	int kk = index.model()->data(index, Qt::DisplayRole).toInt();

	QSpinBox *edit = qobject_cast<QSpinBox*>(editor);
	edit->setValue(kk);
}


void IntDelegate::setModelData(QWidget *editor, QAbstractItemModel *model,
const QModelIndex &index) const
{
	QSpinBox *edit = qobject_cast<QSpinBox*>(editor);
	model->setData(index, QString::number(edit->value()) );
}

void IntDelegate::commitAndCloseEditor()
{
	QSpinBox *editor = qobject_cast<QSpinBox*>(sender());
	emit commitData(editor);
	emit closeEditor(editor);
}
