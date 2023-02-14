#include "treeitem.h"

/*!
 * \brief TreeItem::TreeItem конструктор
 * \param data данные элемента
 * \param parent родитель
 */
TreeItem::TreeItem(const QVector<QVariant> &data, TreeItem *parent)
    : mData(data), mParent(parent){
}

/*!
 * \brief TreeItem::~TreeItem деструктор
 */
TreeItem::~TreeItem(){
    qDeleteAll(mChildren);
}

/*!
 * \brief TreeItem::child получение потомка с индексом row в списке потомков
 * \param row номер потомка
 * \return потомок
 */
TreeItem *TreeItem::child(int row){
    if (row < 0 || row >= mChildren.size()){
        return nullptr;
    }
    return mChildren[row];
}

/*!
 * \brief TreeItem::row получение индекса элемента в списке потомков родителя
 * \return индекс элемента в списке потомков родителя
 */
int TreeItem::row() const{
    return mParent != nullptr ? mParent->mChildren.indexOf(const_cast<TreeItem*>(this)) : 0;
}

/*!
 * \brief TreeItem::childCount получение количества потомков
 * \return количество потомков
 */
int TreeItem::childCount() const{
    return mChildren.size();
}

/*!
 * \brief TreeItem::columnCount получение количество столбцов элемента
 * \return количество столбцов элемента
 */
int TreeItem::columnCount() const{
    return mData.size();
}

/*!
 * \brief TreeItem::getParent получение родителя элемента
 * \return родитель элемента
 */
TreeItem* TreeItem::getParent() const{
    return mParent;
}

/*!
 * \brief TreeItem::getChildren получение списка потомков элемента
 * \return список потомков
 */
QVector<TreeItem*> TreeItem::getChildren() const{
    return mChildren;
}

/*!
 * \brief TreeItem::addChild добавление нового элемента в список потомков
 * \param item элемент, который необходимо добавить
 */
void TreeItem::addChild(TreeItem* item){
    mChildren.append(item);
}

/*!
 * \brief TreeItem::getFont получение жирного шрифта для имен контейнеров
 * \param column номер столбца
 * \return жирный шрифт, если элемент является контейнером иначе QVariant()
 */
QVariant TreeItem::getFont(int column){
    if (column == TREE_ITEM_NAME && mData[TREE_ITEM_TYPE].toInt() == 1){
        QFont font;
        font.setBold(true);
        return font;
    }
    return QVariant();
}

/*!
 * \brief TreeItem::data получение данных указанного столбца
 * \param column номер столбца
 * \return данные указанного столбца
 */
QVariant TreeItem::data(int column) const{
    if (column < 0 || column >= mData.size()){
        return QVariant();
    }
    return mData[column];
}

/*!
 * \brief TreeItem::setData установка значения value в стобец с индексом value
 * \param column номер столбца
 * \param value значение
 * \return результат вставки
 *
 * \details Возвращает булево значение: true при успешной вставке иначе false
 */
bool TreeItem::setData(int column, const QVariant &value){
    if (column < 1 || column >= mData.size()){
        return false;
    }
    mData[column] = value;
    return true;
}

/*!
 * \brief TreeItem::getDataByIndex получение значения, хранящееся в столбце с индексом index
 * \param index индекс столбца
 * \return значение, хранящееся в столбце с индексом index
 */
QVariant TreeItem::getDataByIndex(int index){
    if(index < 0 ||  index > mData.size()){
        return QVariant();
    }
    return mData[index];
}

/*!
 * \brief TreeItem::setParent установка родителя элемента
 * \param parent родитель
 */
void TreeItem::setParent(TreeItem *parent){
    mParent = parent;
}

/*!
 * \brief TreeItem::getData получение данных всех столбцов элемента
 * \return данные всех столбцов элемента
 */
QVector<QVariant> TreeItem::getData() const{
    return mData;
}

