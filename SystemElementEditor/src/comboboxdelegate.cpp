#include "comboboxdelegate.h"
/*!
 * \brief ComboBoxDelegate::ComboBoxDelegate конструктор
 * \param parent родитель
 */
ComboBoxDelegate::ComboBoxDelegate (QObject *parent)
    : QItemDelegate(parent){
    texts << "Тип 2" << "Тип 3";
}

/*!
 * \brief ComboBoxDelegate::~ComboBoxDelegate
 */
ComboBoxDelegate::~ComboBoxDelegate(){
}

/*!
 * \brief ComboBoxDelegate::setItems установка элементов выбора combobox
 * \param item список элементов combobox
 */
void ComboBoxDelegate::setItems(QStringList &item) {
    texts = item;
}

/*!
 * \brief ComboBoxDelegate::createEditor получение редактора, который будет использоваться для редактирования элемента данных с заданным индексом
 * \param parent виджета редактора
 * \param parent виджета редактора
 * \param option неиспользуемый параметр
 * \param index неиспользуемый параметр
 * \return редактор, который будет использоваться для редактирования элемента данных с заданным индексом
 */
QWidget* ComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QComboBox *editor = new QComboBox(parent);
    editor->addItems(texts);
    return editor;
}

/*!
 * \brief ComboBoxDelegate::setEditorData задает данные, которые будут отображаться и редактироваться редактором из элемента модели данных, указанного индексом модели
 * \param editor виджета редактора
 * \param index модельный индекс
 */
void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const{
    QString text = index.model()->data(index, Qt::EditRole).toString();
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    connect(comboBox,SIGNAL(activated(int)), SIGNAL(activatedComboBox(int)));

    int tindex = comboBox->findText(text);
    comboBox->setProperty("type", tindex + 2);
    comboBox->setCurrentIndex(tindex);
}

/*!
 * \brief ComboBoxDelegate::setModelData получение данных из виджета редактора и сохраняет их в указанной модели в index
 * \param editor виджета редактора
 * \param model модель
 * \param index модельный индекс
 */
void ComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const{
    QComboBox *comboBox = static_cast<QComboBox*>(editor);
    QString text = comboBox->currentText();
    model->setData(index, text, Qt::EditRole);
}

/*!
 * \brief ComboBoxDelegate::updateEditorGeometry обновление редактора для элемента, указанного индексом, в соответствии с заданным параметром стиля
 * \param editor виджета редактора
 * \param option параметр стиля
 * \param index неиспользуемый параметр
 */
void ComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    editor->setGeometry(option.rect);
}
