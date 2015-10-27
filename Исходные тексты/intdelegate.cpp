#include "intdelegate.h"

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
 //  CGlobal *g = CGlobal::getInstance();
   int kk = index.model()->data(index, Qt::DisplayRole).toInt();
 //  QDate d = g->_DATA(kk);

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
