#pragma once

#include <QAbstractTableModel>

QT_BEGIN_NAMESPACE
class TableItem;
class TreeItem;
class DatabaseAccessor;
QT_END_NAMESPACE

/*!
 * \class TableModel
 * \brief модель таблица
 */
class TableModel : public QAbstractTableModel {
    Q_OBJECT
public:
    explicit TableModel(QObject* parent = 0);
    ~TableModel();
    /// \group переопределенные методы
    int rowCount(const QModelIndex& parent ) const override;
    int columnCount( const QModelIndex& parent ) const override;
    QVariant data( const QModelIndex& index, int role ) const override;
    bool setData( const QModelIndex& index, const QVariant& value, int role ) override;
    QVariant headerData( int section, Qt::Orientation orientation, int role ) const override;
    Qt::ItemFlags flags( const QModelIndex& index ) const override;

    void addItem(TableItem* item);
    void setupModelData(TreeItem * root, int type);
    void clearModel();
    QString getParentId() const;
signals:
    /// сигнал изменения размера элемента
    void sizeChanged(const QString& id, int size);
private:
    /// идентификатор родителя
    QString parentId;
    /// список элементов
    QVector<TableItem*> mItems;
};

