#include "spindelegate.h"
/*!
 * \brief SpinDelegate::SpinDelegate конструктор
 * \param parent родитель
 */
SpinDelegate::SpinDelegate(QObject *parent):
    QItemDelegate(parent){

}

/*!
 * \brief SpinDelegate::~SpinDelegate деструктор
 */
SpinDelegate::~SpinDelegate(){

}

/*!
 * \brief SpinDelegate::createEditor получение редактора, который будет использоваться для редактирования элемента данных с заданным индексом
 * \param parent виджета редактора
 * \param option неиспользуемый параметр
 * \param index неиспользуемый параметр
 * \return редактор, который будет использоваться для редактирования элемента данных с заданным индексом.
 */
QWidget *SpinDelegate::createEditor(QWidget *parent,const QStyleOptionViewItem& /*option*/, const QModelIndex& /*index*/) const{
    QSpinBox *editor = new QSpinBox(parent);

    editor->setRange(INT_MIN, INT_MAX);
    editor->installEventFilter(const_cast<SpinDelegate*>(this));
    return editor;
}

/*!
 * \brief SpinDelegate::setEditorData задает данные, которые будут отображаться и редактироваться редактором из элемента модели данных, указанного индексом модели
 * \param editor виджета редактора
 * \param index модельный индекс
 */
void SpinDelegate::setEditorData(QWidget* editor,const QModelIndex& index) const{
    int value =index.model()->data(index).toInt();
    QSpinBox *box = static_cast<QSpinBox*>(editor);
    if(box == nullptr){
        return;
    }
    box->setValue(value);
}

/*!
 * \brief SpinDelegate::setModelData получение данных из виджета редактора и сохраняет их в указанной модели в index
 * \param editor виджета редактора
 * \param model модель
 * \param index модельный индекс
 */
void SpinDelegate::setModelData(QWidget* editor, QAbstractItemModel* model, const QModelIndex& index) const{
    QSpinBox *box = static_cast<QSpinBox*>(editor);
    if(box == nullptr){
        return;
    }
    int value = box->value();
    model->setData(index, value);
}

/*!
 * \brief SpinDelegate::updateEditorGeometry обновление редактора для элемента, указанного индексом, в соответствии с заданным параметром стиля
 * \param editor виджета редактора
 * \param option параметр стиля
 * \param index неиспользуемый параметр
 */
void SpinDelegate::updateEditorGeometry(QWidget* editor, const QStyleOptionViewItem& option, const QModelIndex& index) const{
    editor->setGeometry(option.rect);
}
