#ifndef WAYBILLMANUFACTURE_H
#define WAYBILLMANUFACTURE_H

#include <QDialog>
#include <memory>
#include <QSqlDatabase>
#include <QSqlRelationalTableModel>
#include <QItemDelegate>

namespace Ui {
class waybillManufacture;
}

class waybillManufacture : public QDialog
{
    Q_OBJECT

public:
    explicit waybillManufacture(std::shared_ptr<QSqlDatabase>, QString, QWidget *parent = nullptr);
    ~waybillManufacture();

private slots:
    void on_submmitButton_clicked();

    void on_revertButton_clicked();

private:
    Ui::waybillManufacture *ui;
    std::shared_ptr<QSqlDatabase> database;
    QSqlRelationalTableModel *model;
    QString id_waybill;
};

class NotEditableDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit NotEditableDelegate(QObject *parent = 0)
        : QItemDelegate(parent)
    {}

protected:
    bool editorEvent(QEvent *event, QAbstractItemModel *model, const QStyleOptionViewItem &option, const QModelIndex &index)
    { return false; }
    QWidget* createEditor(QWidget *, const QStyleOptionViewItem &, const QModelIndex &) const
    { return Q_NULLPTR; }

};

#endif // WAYBILLMANUFACTURE_H
