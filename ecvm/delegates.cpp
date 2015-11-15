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

QWidget *NumberDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &, const QModelIndex &) const
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
