#include <tablemodel.h>

/*!
 * \brief TableModel::TableModel конструктор
 * \param parent родитель
 */
TableModel::TableModel(QObject* parent) :
    QAbstractTableModel(parent) {
}

/*!
 * \brief TableModel::~TableModel деструктор
 */
TableModel::~TableModel(){
    qDeleteAll(mItems);
}

/*!
 * \brief TableModel::rowCount получение количества строк для элемента с заданным индексом
 * \param parentIndex модельный индекс элемента
 * \return количество строк
 */
int TableModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return mItems.size();
}

/*!
 * \brief TableModel::columnCount получение количества столбцов для элемента с заданным индексом
 * \param parentIndex модельный индекс элемента
 * \return количество столбцов
 *
 * \details количество столбцов всегда равняется 2
 */
int TableModel::columnCount( const QModelIndex& parent) const {
    Q_UNUSED(parent)
    return 2;
}

/*!
 * \brief TableModel::data получение данных из модельного индекса index с ролью role
 * \param index модельный индекс элемента
 * \param role роль
 * \return данные из модельного индекса index с ролью role
 */
QVariant TableModel::data(const QModelIndex &index, int role) const{
    if(!index.isValid() || mItems.size() <= index.row()) {
        return QVariant();
    }

    if(role == Qt::DisplayRole){
        return mItems[index.row()]->getDataByIndex(index.column());
    }

    if(role == Qt::FontRole){
        if(index.column() == TABLE_ITEM_SIZE && mItems[index.row()]->getDataByIndex(TABLE_ITEM_SIZE) < 0){
            QFont boldFont;
            boldFont.setBold(true);
            return boldFont;
        }
    }

    if(role == Qt::TextColorRole && mItems[index.row()]->getDataByIndex(TABLE_ITEM_SIZE) < 0){
        if(index.column() == TABLE_ITEM_SIZE){
            QBrush color(Qt::red);
            return color;
        }
    }

    return QVariant();
}

/*!
 * \brief TableModel::setData установка данных в узел с модельным индексом index со значением value
 * \param index модельный индекс элемента
 * \param value значение
 * \param role роль
 * \return результат вставки
 *
 * \details Возвращает булево значение: true при успешной вставке иначе false
 */
bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role){
    if(!index.isValid() || role != Qt::EditRole || mItems.size() <= index.row()){
        return false;
    }
    mItems[index.row()]->setDataByIndex(index.column(), value);
    emit dataChanged(index, index);

    QString size = mItems[index.row()]->getDataByIndex(TABLE_ITEM_SIZE).toString();
    QString id = mItems[index.row()]->getDataByIndex(TABLE_ITEM_ID).toString();
    emit sizeChanged(id, size.toInt());

    QString query = "UPDATE schema SET size=" + size + " WHERE id='" +id + "'";
    QVector<QVector<QVariant>> resultSqlQuery;
    DatabaseAccessor::getInstance()->setQuery(query);
    resultSqlQuery = DatabaseAccessor::getInstance()->executeSqlQuery();
    return true;
}

/*!
 * \brief TableModel::headerData установка данных заголовка столбца
 * \param section секция
 * \param orientation ориентация
 * \param role роль
 * \return данные заголовка столбца
 */
QVariant TableModel::headerData( int section, Qt::Orientation orientation, int role) const{
    if( role != Qt::DisplayRole ){
        return QVariant();
    }
    if( orientation == Qt::Vertical){
        return section;
    }
    if(section == TABLE_ITEM_NAME){
        return QVariant("Наименование");
    }
    if(section == TABLE_ITEM_SIZE){
        return QVariant("Размер");
    }

    return QVariant();
}

/*!
 * \brief TreeModel::flags получение флага выбора
 * \param index модельный индекс элемента
 * \return флаг выбора
 */
Qt::ItemFlags TableModel::flags(const QModelIndex &index) const{
    if(index.isValid()) {
        if(index.column() == TABLE_ITEM_SIZE) {
            return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
        }
    }
    return QAbstractTableModel::flags(index);
}

/*!
 * \brief TableModel::addItem добавление нового элемента в модель
 * \param item элемент, который необходимо вставить
 */
void TableModel::addItem(TableItem* item) {
    int row = mItems.count();

    beginInsertRows(QModelIndex(), row, row);
    mItems.append(item);
    endInsertRows();
}

/*!
 * \brief TableModel::setupModelData заполнение модели
 * \param root родитель элементов модели
 * \param type тип элементов модели
 */
void TableModel::setupModelData(TreeItem *root, int type){
    parentId = root->getDataByIndex(TREE_ITEM_ID).toString();
    for (auto &item : root->getChildrens()){

        if(item->childCount() != 0){
            continue;
        }
        int currentType = item->getDataByIndex(TREE_ITEM_TYPE).toString().section(' ', 1).toInt();
        if(type == currentType){

            QVector<QVariant> data;
            data << item->getDataByIndex(TREE_ITEM_NAME) << item->getDataByIndex(TREE_ITEM_SIZE) << item->getDataByIndex(TREE_ITEM_ID);
            addItem(new TableItem(data));
        }
    }
}

/*!
 * \brief TableModel::clearModel очистка модели от элементов
 */
void TableModel::clearModel(){
    beginResetModel();
    mItems.clear();
    mItems.squeeze();
    endResetModel();
}

/*!
 * \brief TableModel::getParentId получение родителя элементов модели
 * \return идентификатор родителя
 */
QString TableModel::getParentId() const{
    return parentId;
}


