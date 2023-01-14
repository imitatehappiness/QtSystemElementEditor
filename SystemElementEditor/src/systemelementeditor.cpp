#include "systemelementeditor.h"
#include "./ui_systemelementeditor.h"

#include <QKeyEvent>

/*!
 * \brief SystemElementEditor::SystemElementEditor констуктор
 * \param parent родитель
 *
 * \details инициализация главного окна
 */
SystemElementEditor::SystemElementEditor(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::SystemElementEditor)
{
    ui->setupUi(this);

    ui->l_systemComposition->setText("<strong>Состав системы:</strong>");
    ui->l_type2->setText("<strong>Элементы \"Тип 2\":</strong>");
    ui->l_type3->setText("<strong>Элементы \"Тип 3\":</strong>");

    QThread *thread = new QThread();
    DatabaseAccessor::getInstance()->moveToThread(thread);

    //connect(thread,&QThread::started,this,&DatabaseAccessor::slotStartArticlesList);
   // connect(thread,&QThread::started,lsArticles,&ListArticles::createListGoods);

    connect(thread,&QThread::finished,thread,&QThread::deleteLater);
    thread->start();

    parseTableShema();

    /// tree
    mTreeModel = new TreeModel();
    mTreeModel->setupModelData(mTreeItems);
    ui->treeView_systemComposition->setModel(mTreeModel);

    ui->treeView_systemComposition->hideColumn(TREE_ITEM_ID);
    ui->treeView_systemComposition->hideColumn(TREE_ITEM_ID_UP);
    ui->treeView_systemComposition->hideColumn(TREE_ITEM_SIZE);
    ui->treeView_systemComposition->setEditTriggers(QAbstractItemView::AllEditTriggers);
    ui->treeView_systemComposition->header()->setSectionResizeMode(QHeaderView::ResizeToContents);

    mComboBoxDelegate = new ComboBoxDelegate();
    ui->treeView_systemComposition->setItemDelegate(mComboBoxDelegate);

    /// tables
    mSpinDelegate = new SpinDelegate();

    mTableType2 = new TableModel();
    ui->tableView_type2->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_type2->setItemDelegateForColumn(TABLE_ITEM_SIZE, mSpinDelegate);
    ui->tableView_type2->setModel(mTableType2);

    mTableType3 = new TableModel();
    ui->tableView_type3->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    ui->tableView_type3->setItemDelegateForColumn(TABLE_ITEM_SIZE, mSpinDelegate);
    ui->tableView_type3->setModel(mTableType3);

    connect(ui->treeView_systemComposition->selectionModel(),SIGNAL(selectionChanged(const QItemSelection &, const QItemSelection &)),
            this, SLOT(treeSelectionChanged(const QItemSelection &, const QItemSelection &)));

    connect(mTreeModel,SIGNAL(typeChanged(const QModelIndex &)), this, SLOT(typeChanged(const QModelIndex &)));
    connect(mTableType2,SIGNAL(sizeChanged(const QString&, int)), this, SLOT(sizeChanged(const QString&, int)));
    connect(mTableType3,SIGNAL(sizeChanged(const QString&, int)), this, SLOT(sizeChanged(const QString&, int)));
    connect(mComboBoxDelegate, SIGNAL(activatedComboBox(int)), this, SLOT(pressEnter(int)));
}

/*!
 * \brief SystemElementEditor::~SystemElementEditor деструктор
 */
SystemElementEditor::~SystemElementEditor(){
    qDeleteAll(mTreeItems);
    delete mTreeModel;
    delete mComboBoxDelegate;
    delete mTableType2;
    delete mTableType3;
    delete mSpinDelegate;
    delete ui;
}

/*!
 * \brief SystemElementEditor::typeChanged вызов обновления таблиц после изменения типа объекта
 * \param index модельный индекс элемента
 */
void SystemElementEditor::typeChanged(const QModelIndex &index){
    TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
    if(item->getParent()->getDataByIndex(TREE_ITEM_ID) == mTableType2->getParentId()){
        updateTables(item->getParent());
    }
}

/*!
 * \brief SystemElementEditor::sizeChanged обновление размера элемента
 * \param id идентификатор элемента
 * \param size новые размер элемента
 */
void SystemElementEditor::sizeChanged(const QString &id, int size){
    for(auto &item : mTreeItems){
        if(id == item->getDataByIndex(TREE_ITEM_ID).toString()){
            item->setData(TREE_ITEM_SIZE, size);
            mTreeModel->changeSize(mTreeModel->getRoot(), id, size);
        }
    }
}

/*!
 * \brief SystemElementEditor::parseTableShema формирование списка элементов из таблицы schema
 */
void SystemElementEditor::parseTableShema(){
    DatabaseAccessor::getInstance()->setQuery("SELECT * FROM schema");
    QVector<QVector<QVariant>> result = DatabaseAccessor::getInstance()->executeSqlQuery();

    for(int i = 0; i < result.size(); i++){
        QVector<QVariant> itemData{result[i][3].toString(), result[i][2].toInt(), result[i][0].toString(), result[i][1].toString(), result[i][4].toInt()};
        TreeItem* item = new TreeItem(itemData);
        mTreeItems.append(item);
    }
}

/*!
 * \brief SystemElementEditor::treeSelectionChanged обновленик таблиц после изменения типа объекта
 * \param selected неиспользуемый параметр
 * \param deselected неиспользуемый параметр
 */
void SystemElementEditor::treeSelectionChanged(const QItemSelection &selected, const QItemSelection &deselected){
    Q_UNUSED(selected)
    Q_UNUSED(deselected)

    QItemSelectionModel *selections = ui->treeView_systemComposition->selectionModel();
    QModelIndexList indexes = selections->selectedIndexes();
    for(QModelIndex index : indexes){
        TreeItem* item = static_cast<TreeItem*>(index.internalPointer());
        if (item){
            updateTables(item);
        }
    }
}

/*!
 * \brief SystemElementEditor::pressEnter имитация нажатия Enter, для корректного обновления таблиц
 * \param index неиспользуемый параметр
 *
 * \details без SystemElementEditor::pressEnter после изменения типа необходимо было нажимать мышью в любой участок формы или нажимать Enter самостоятельно
 */
void SystemElementEditor::pressEnter(int index){
    Q_UNUSED(index);
    ui->treeView_systemComposition->setFocus();
    QApplication::sendEvent(ui->treeView_systemComposition, new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier));
}

/*!
 * \brief SystemElementEditor::updateTables обновление таблиц
 * \param item родитель элементов таблиц
 */
void SystemElementEditor::updateTables(TreeItem *item){
    if (item && item->childCount() != 0){
        mTableType2->clearModel();
        mTableType3->clearModel();
        mTableType2->setupModelData(item, 2);
        mTableType3->setupModelData(item, 3);
    }
}
