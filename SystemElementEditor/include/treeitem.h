#pragma once

#include <QVector>
#include <QVariant>

QT_BEGIN_NAMESPACE
class ComboBoxDelegate;
QT_END_NAMESPACE

/*!
 * \enum TreeData
 * \brief индексы, соответсвующие списку данных элемента TreeItem
 * TreeData::TREE_ITEM_NAME имя элемента
 * TreeData::TREE_ITEM_TYPE тип элемента
 * TreeData::TREE_ITEM_ID идентификатор элемента
 * TreeData::TREE_ITEM_ID_UP идентификатор родительского элемента
 * TreeData::TREE_ITEM_SIZE размер элемента
 */
enum TreeData{
    TREE_ITEM_NAME,
    TREE_ITEM_TYPE,
    TREE_ITEM_ID,
    TREE_ITEM_ID_UP,
    TREE_ITEM_SIZE,
};

/*!
 * \class TreeItem
 * \brief элемент дерева
 */
class TreeItem{
public:
    explicit TreeItem(const QVector<QVariant> &data, TreeItem *parent = nullptr);
    ~TreeItem();
    TreeItem *child(int row);
    int row() const;
    int childCount() const;
    int columnCount() const;
    TreeItem *getParent() const;
    QVector<TreeItem*> getChildren() const;
    void addChild(TreeItem* item);
    QVariant getFont(int column);
    TreeItem* getItem(int row) const;
    QVariant data(int column) const;
    bool setData(int column, const QVariant &value);
    QVariant getDataByIndex(int index);
    QVector<QVariant> getData() const;
    void setParent(TreeItem *parent);
private:
    /// родитель
    TreeItem* mParent = nullptr;
    /// список потомков
    QVector<TreeItem*> mChildren;
    /// список данных элементов
    QVector<QVariant> mData;   
};
