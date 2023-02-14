#pragma once

#include <QVector>
#include <QVariant>

/*!
 * \enum TableData
 * \brief индексы, соответсвующие списку данных элемента TableItem
 * TableColumn::TABLE_ITEM_NAME имя элемента
 * TableColumn::TABLE_ITEM_SIZE размер элемента
 * TableColumn::TABLE_ITEM_ID идентификатор элемента
 */
enum TableData{
    TABLE_ITEM_NAME = 0,
    TABLE_ITEM_SIZE,
    TABLE_ITEM_ID
};

/*!
 * \class TableItem
 * \brief элемент таблицы
 */
class TableItem{
public:
     TableItem(const QVector<QVariant> &data);
    ~TableItem();
    QVector<QVariant> getData() const;
    void setDataByIndex(int index, QVariant value);
    QVariant getDataByIndex(int index);

private:
    /// список данных
    QVector<QVariant> mData;
};

