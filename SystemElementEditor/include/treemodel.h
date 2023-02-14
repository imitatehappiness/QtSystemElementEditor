#pragma once

#include <QAbstractItemModel>
#include <QModelIndex>

#include "treeitem.h"
#include "comboboxdelegate.h"
#include "databaseaccessor.h"

/*!
 * \class TreeModel
 * \brief модель дерева
 */
class TreeModel : public QAbstractItemModel{
    Q_OBJECT
public:
    explicit TreeModel(QObject *parent = nullptr);
    ~TreeModel();
    /// \group переопределенные методы
    QModelIndex index(int row, int column, const QModelIndex &parentIndex = QModelIndex()) const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    QModelIndex parent(const QModelIndex &childIndex) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role) const override;

    TreeItem* getRoot() const;
    TreeItem* itemByIndex(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void setupModelData(QVector <TreeItem*>& elements);
    QVector<TreeItem*> getRoots(QVector<TreeItem *>& elements);
    void findChildren(QVector<TreeItem*>& parents, TreeItem* item);
    void sorting(QVector<TreeItem *> &roots);
    QVariant getIdItemByIndex(const QModelIndex &index) const;
    void changeSize(TreeItem *root, const QString& id, int size);
signals:
    /// сигнал изменения типа элемента
    void typeChanged(const QModelIndex &index);
private:
    /// корень дерева
    TreeItem* mRoot;
};
