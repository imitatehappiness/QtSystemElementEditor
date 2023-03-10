#pragma once

#include <QItemDelegate>

/*!
 * \class ComboBoxDelegate
 * \brief делегат ComboBoxDelegate используется для выбора типа элемента в дереве
 */
class ComboBoxDelegate : public QItemDelegate{
    Q_OBJECT
public:
    explicit ComboBoxDelegate(QObject *parent = nullptr);
    ~ComboBoxDelegate();
    /// \group переопределенные методы
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void setItems(QStringList &texts);

signals:
    /// сигнал нажатия на элемент в списке combobox
    void activatedComboBox(int index);

private:
    /// список элементов combobox
    QStringList mTexts;
};

