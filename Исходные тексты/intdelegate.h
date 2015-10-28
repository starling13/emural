/*
 * File:   IntDelegate.h
 * Author: starling13
 *
 * Created on 16 Август 2012 г., 16:03
 */

#ifndef INTDELEGATE_H
#define	INTDELEGATE_H

#include <QItemDelegate>
#include <QSpinBox>
#include <QStyleOptionViewItem>

class IntDelegate : public QItemDelegate
{
	Q_OBJECT

	int min;
	int max;
	int step;

public:
	/**
	* Инициализирующий конструктор
	* @param parent родительский объект
	* @param iMin минимальное значение поля
	* @param iMax максимальное значение
	* @param iStep шаг значения
	*/
	IntDelegate(QObject*, int, int, int);
	
	~IntDelegate();

	QWidget* createEditor(QWidget*, const QStyleOptionViewItem&,
	    const QModelIndex&) const;
	void setEditorData(QWidget*, const QModelIndex&) const;
	void setModelData(QWidget*, QAbstractItemModel*, const QModelIndex&) const;
public slots:
	void commitAndCloseEditor();
};

#endif	/* INTDELEGATE_H */

