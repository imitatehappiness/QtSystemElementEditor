/*!
 * \file
 * \brief Заголовочный файл SystemElementEditor
 */
#ifndef SYSTEMELEMENTEDITOR_H
#define SYSTEMELEMENTEDITOR_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include <QMap>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QDir>
#include <QSettings>
#include <QVariant>
#include <QStandardItemModel>
#include <QHeaderView>
#include <treeitem.h>
#include <treemodel.h>
#include <comboboxdelegate.h>
#include <spindelegate.h>
#include <databaseaccessor.h>
#include <tablemodel.h>
#include <tableitem.h>

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
private:
    void parseTableShema();
    void updateTables(TreeItem* item);
    Ui::SystemElementEditor *ui;
    /// список элементов таблицы schema
    QVector<TreeItem*> mTreeItems;
    /// модель дерева
    TreeModel* mTreeModel;
    /// делегат combobox
    ComboBoxDelegate* mComboBoxDelegate;
    /// делегат spinbox
    SpinDelegate* mSpinDelegate;
    /// модель таблицы типа 2
    TableModel* mTableType2;
    /// модель таблицы типа 3
    TableModel* mTableType3;
private slots:
    void typeChanged(const QModelIndex &);
    void sizeChanged(const QString& id, int size);
    void treeSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected);
    void pressEnter(int index);
};

#endif // SYSTEMELEMENTEDITOR_H
