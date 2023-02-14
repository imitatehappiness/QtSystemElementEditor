#pragma once

#include <QMainWindow>
#include <QtSql>
#include <QStandardItemModel>
#include <QHeaderView>
#include <QKeyEvent>

#include "databaseaccessor.h"

class TreeModel;
class TreeItem;
class ComboBoxDelegate;
class TableModel;
class TableItem;
class SpinDelegate;


QT_BEGIN_NAMESPACE
namespace Ui { class SystemElementEditor; }
QT_END_NAMESPACE

/*!
 * \class SystemElementEditor
 * \brief обеспечивает связь всех компонентов программы
 */
class SystemElementEditor : public QMainWindow{
    Q_OBJECT
public:
    explicit SystemElementEditor(QWidget *parent = nullptr);
    ~SystemElementEditor();

private slots:
    void typeChanged(const QModelIndex &);
    void sizeChanged(const QString& id, int size);
    void treeSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void pressEnter(int index);
    void errorOpenDatabase();

private:
    void parseTableScheme();
    void updateTables(TreeItem* item);
    Ui::SystemElementEditor *ui;
    /// список элементов таблицы schema
    QVector<TreeItem*> mTreeItems;
    /// модель дерева
    TreeModel* mTreeModel = nullptr;
    /// делегат combobox
    ComboBoxDelegate* mComboBoxDelegate = nullptr;
    /// делегат spinbox
    SpinDelegate* mSpinDelegate = nullptr;
    /// модель таблицы типа 2
    TableModel* mTableType2 = nullptr;
    /// модель таблицы типа 3
    TableModel* mTableType3 = nullptr;
};

