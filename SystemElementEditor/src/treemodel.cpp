#include "treemodel.h"
#include "treeitem.h"

/*!
 * \brief TreeModel::TreeModel констуктор
 * \param parent родитель
 */
TreeModel::TreeModel(QObject *parent)
    : QAbstractItemModel(parent)
{
    mRoot = new TreeItem({tr("Наименование"), tr("Тип"), tr("Идентификатор элемента"), tr("Идентификатор родительского элемента"), tr("Размер")});
}

/*!
 * \brief TreeModel::~TreeModel деструктор
 */
TreeModel::~TreeModel(){
    delete mRoot;
}

/*!
 * \brief TreeModel::index получение модельного индекса по строке и столбцу
 * \param row строка
 * \param column столбец
 * \param parentIndex модельный индекс родителя
 * \return модельный индекс элемента
 */
QModelIndex TreeModel::index(int row, int column, const QModelIndex& parentIndex) const{
    if (!hasIndex(row, column, parentIndex)){
        return QModelIndex();
    }

    TreeItem *parentItem;
    parentItem = !parentIndex.isValid() ? mRoot : static_cast<TreeItem*>(parentIndex.internalPointer());
    if(parentItem != nullptr){
        TreeItem *childItem = parentItem->child(row);
        if (childItem != nullptr){
            return createIndex(row, column, childItem);
        }
    }

    return QModelIndex();
}

/*!
 * \brief TreeModel::flags получение флага выбора
 * \param index модельный индекс элемента
 * \return флаг выбора
 */
Qt::ItemFlags TreeModel::flags(const QModelIndex& index) const{
    if (!index.isValid()){
        return Qt::NoItemFlags;
    }

    if(index.column() == 1){
        TreeItem* item = itemByIndex(index);
        if(item->childCount() == 0){
            return QAbstractItemModel::flags(index) | Qt::ItemIsSelectable | Qt::ItemIsEditable;
        }
    }

    return  QAbstractItemModel::flags(index) | Qt::ItemIsSelectable;
}

/*!
 * \brief TreeModel::parent получение модельного индекса родителя
 * \param childIndex модельный индекс элемента
 * \return модельный индекс родителя
 */
QModelIndex TreeModel::parent(const QModelIndex& childIndex) const{
    if (!childIndex.isValid()){
        return QModelIndex();
    }

    TreeItem *childItem = static_cast<TreeItem*>(childIndex.internalPointer());
    if(childItem == nullptr){
        return QModelIndex();;
    }

    TreeItem *parentItem = childItem->getParent();
    if (parentItem == mRoot){
        return QModelIndex();
    }

    return createIndex(parentItem->row(), 0, parentItem);
}

/*!
 * \brief TreeModel::rowCount получение количества строк для элемента с заданным индексом
 * \param parentIndex модельный индекс элемента
 * \return количество строк
 */
int TreeModel::rowCount(const QModelIndex& parentIndex) const {
    TreeItem* parentItem;
    if (parentIndex.column() > 0){
        return 0;
    }

    parentItem = !parentIndex.isValid() ? mRoot : static_cast<TreeItem*>(parentIndex.internalPointer());
    return parentItem == nullptr ? 0 :parentItem->childCount();
}

/*!
 * \brief TreeModel::columnCount получение количества столбцов для элемента с заданным индексом
 * \param parentIndex модельный индекс элемента
 * \return количество столбцов
 */
int TreeModel::columnCount(const QModelIndex& parent) const{
    if (parent.isValid()){
        TreeItem* item = static_cast<TreeItem*>(parent.internalPointer());
        if(item!= nullptr){
            return item->columnCount();
        }
    }
    return mRoot->columnCount();
}

/*!
 * \brief TreeModel::data получение данных из модельного индекса index с ролью role
 * \param index модельный индекс элемента
 * \param role роль
 * \return данные из модельного индекса index с ролью role
 */
QVariant TreeModel::data(const QModelIndex& index, int role) const{
    if (!index.isValid()){
        return QVariant();
    }
    TreeItem *item = itemByIndex(index);

    if (role == Qt::FontRole){
        return item->getFont(index.column());
    }else if (role != Qt::DisplayRole  && role != Qt::EditRole){
        return QVariant();
    }

    if(index.column() == TREE_ITEM_TYPE){
        if(item->getDataByIndex(TREE_ITEM_TYPE) == 1){
            return "";
        }else{
            return "Тип " + item->getDataByIndex(TREE_ITEM_TYPE).toString();
        }
    }

    return item->data(index.column());
}

/*!
 * \brief TreeModel::getRoot получение корня дерева
 * \return корень дерева
 */
TreeItem* TreeModel::getRoot() const{
    return mRoot;
}

/*!
 * \brief TreeModel::itemByIndex получение элемента модели по модельному индексу
 * \param index модельный индекс элемента
 * \return элемент модели
 */
TreeItem* TreeModel::itemByIndex(const QModelIndex &index) const{
    if (!index.isValid()){
        return mRoot;
    }
    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    return item == nullptr ? mRoot : item;
}

/*!
 * \brief TreeModel::headerData установка данных заголовка столбца
 * \param section секция
 * \param orientation ориентация
 * \param role роль
 * \return данные заголовка столбца
 */
QVariant TreeModel::headerData(int section, Qt::Orientation orientation, int role) const{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole){
        return mRoot->data(section);
    }
    return QVariant();
}

/*!
 * \brief TreeModel::setData установка данных в узел с модельным индексом index со значением value
 * \param index модельный индекс элемента
 * \param value значение
 * \param role роль
 * \return результат вставки
 *
 * \details Возвращает булево значение: true при успешной вставке иначе false
 */
bool TreeModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if (role != Qt::EditRole){
        return false;
    }

    TreeItem *item = itemByIndex(index);
    bool result = item->setData(index.column(), value);
    if (result) {
        emit dataChanged(index, index);
    }

    emit typeChanged(index);
    int type = item->getDataByIndex(TREE_ITEM_TYPE).toInt();
    auto query = QString( "UPDATE scheme SET type=%1 WHERE id='%2';" )
         .arg(type)
         .arg(getIdItemByIndex(index).toString());

    DatabaseAccessor::getInstance()->setQuery(query);
    result = DatabaseAccessor::getInstance()->executeUpdateQuery();
    return result;
}

/*!
 * \brief TreeModel::getIdItemByIndex возвращает идентификатор элемента с индексом index
 * \param index модельный индекс элемента
 * \return идентификатор элемента
 */
QVariant TreeModel::getIdItemByIndex(const QModelIndex &index) const{
    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    return item == nullptr ? QVariant(0) : item->getDataByIndex(TREE_ITEM_ID);
}

/*!
 * \brief TreeModel::changeSize установка нового значения size для элемента с идентификатором id
 * \param root родительский корень
 * \param id идентификатор элемента
 * \param size новый размер элемента
 */
void TreeModel::changeSize(TreeItem* root, const QString &id, int size){
    for (auto &item : root->getChildren()){
        if(item->getDataByIndex(TREE_ITEM_ID) == id){
            item->setData(TREE_ITEM_SIZE, size);
            return;
        }
        changeSize(item, id, size);
    }
}

/*!
 * \brief TreeModel::setupModelData заполнение модели
 * \param elements список элементов дерева
 */
void TreeModel::setupModelData(QVector<TreeItem *> &elements){
    sorting(elements);
    QVector<TreeItem*> roots = getRoots(elements);
    QVector<TreeItem*> parents;
    parents << getRoot();

    for (auto &item : roots){
        parents.last()->addChild(new TreeItem(item->getData(), parents.last()));
        parents << parents.last()->child(parents.last()->childCount()-1);
        findChildren(parents, item);
    }
}

/*!
 * \brief TreeModel::findChildren поиск потомков элемента
 * \param parents список родителей
 * \param item элемент, для которого проводится поиск потомков
 */
void TreeModel::findChildren(QVector<TreeItem*>& parents, TreeItem* item){
    for(auto &child : item->getChildren()){
        child->setParent(parents.last());
        parents.last()->addChild(new TreeItem(child->getData(), parents.last()));
        if(child->childCount() != 0){
            parents << parents.last()->child(parents.last()->childCount()-1);
            findChildren(parents, child);
        }
    }
    parents.pop_back();
}

/*!
 * \brief TreeModel::getRoots поиск потомков корня
 * \param elements список элементов дерева
 * \return возвращает список внешних контейнеров (потомков корня)
 */
QVector<TreeItem*> TreeModel::getRoots(QVector <TreeItem*>& elements){
    for(auto &child : elements){
        for(auto &father : elements){
            if(child->getDataByIndex(TREE_ITEM_ID_UP) == father->getDataByIndex(TREE_ITEM_ID)){
                child->setParent(father);
                father->addChild(child);
            }
        }
    }

    QVector<TreeItem*> roots;
    for(auto &item : elements){
        if(item->getParent() == nullptr){
            roots.append(item);
        }
    }
    return roots;
}

/*!
 * \brief TreeModel::sorting сортирует дерево по полю name
 * \param roots список корней
 */
void TreeModel::sorting(QVector<TreeItem*>& roots){
    qSort(roots.begin(), roots.end(), [](TreeItem* item1, TreeItem* item2) -> bool {
        return item1->getDataByIndex(TREE_ITEM_NAME).toString() < item2->getDataByIndex(TREE_ITEM_NAME).toString();
    });

    for(auto &child : roots){
        if(child->childCount() != 0){
            QVector<TreeItem*> childrens = child->getChildren();
            sorting(childrens);
        }
    }
}
