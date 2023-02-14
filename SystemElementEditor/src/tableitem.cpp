#include "tableitem.h"

/*!
 * \brief TableItem::TableItem конструктор
 * \param data список данных элемента
 *
 * \details инициализирует элемент, присваивая список данных
 */
TableItem::TableItem(const QVector<QVariant> &data)
    : mData(data){

}

TableItem::~TableItem(){
}

/*!
 * \brief TableItem::getData получение данных всех столбцов элемента
 * \return данные всех столбцов элемента
 */
QVector<QVariant> TableItem::getData() const{
    return mData;
}

/*!
 * \brief TableItem::setData установка значения value в стобец с индексом value
 * \param index номер столбца
 * \param value значение
 */
void TableItem::setDataByIndex(int index, QVariant value){
    mData[index] = value;
}

/*!
 * \brief TableItem::getDataByIndex получение значения, хранящееся в столбце с индексом index
 * \param index индекс столбца
 * \return значение, хранящееся в столбце с индексом index
 */
QVariant TableItem::getDataByIndex(int index){
    return mData[index];
}

