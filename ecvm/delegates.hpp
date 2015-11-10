#ifndef DELEGATES_HPP
#define DELEGATES_HPP

#include <QItemDelegate>
#include <QStyleOptionViewItem>
#include <QValidator>
#include <QLineEdit>
#include <QKeyEvent>

#include "ural.hpp"

/**
 * Объект LineEdit с нестираемыми символами
 */
class ReplaceLineEdit : public QLineEdit
{
    Q_OBJECT

public:
    ReplaceLineEdit(QWidget *parent=0) : QLineEdit(parent) {}
protected:
    void keyPressEvent(QKeyEvent *event)
    {
        if ((event->key() != Qt::Key_Backspace)
            &&	(event->key() != Qt::Key_Delete))
        QLineEdit::keyPressEvent(event);
    }
};

/**
 * Объект делегат для редактирования bitset<64>
 * @return
 */
class NumberDelegate : public QItemDelegate
{
    Q_OBJECT

public:

   /**
    * Инициализирующий конструктор
    * @param parent родительский объект
    */
    NumberDelegate(int, URAL::Format, QObject*);
    ~NumberDelegate();

    QWidget* createEditor(QWidget*, const QStyleOptionViewItem&, const QModelIndex&) const;
    void setEditorData(QWidget*, const QModelIndex&) const;
    void setModelData(QWidget*, QAbstractItemModel*, const QModelIndex&) const;

public slots:

    void commitAndCloseEditor();

private:

    int _bitCount;

    URAL::Format    _format;

    QString         _mask;

    QValidator      *_validator;
};
#endif // DELEGATES_HPP
