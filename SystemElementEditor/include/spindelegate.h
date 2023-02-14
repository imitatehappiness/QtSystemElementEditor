#pragma once

#include <QItemDelegate>
#include <QSpinBox>

#include "tableitem.h"

/*!
 * \class SpinDelegate
 * \brief делегат SpinDelegate используется для изменения размера элемента в таблицах
 */
class SpinDelegate : public QItemDelegate{
    Q_OBJECT
public:
    explicit SpinDelegate(QObject *parent = nullptr);
    ~SpinDelegate();
    /// \group переопределенные методы
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex  &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};

