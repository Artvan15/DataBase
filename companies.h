#ifndef COMPANIES_H
#define COMPANIES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlTableModel>
#include <memory>

namespace Ui {
class companies;
}

class companies : public QDialog
{
    Q_OBJECT

public:
    explicit companies(std::shared_ptr<QSqlDatabase>, QWidget *parent = nullptr);
    ~companies();

private slots:


    void on_submmitButton_clicked();

    void on_revertButton_clicked();

    void on_selectButton_clicked();

    void on_addButton_clicked();

    void on_deleteButton_clicked();

private:
    Ui::companies *ui;
    QSqlTableModel *model;
    std::shared_ptr<QSqlDatabase> database;
};

#endif // COMPANIES_H

