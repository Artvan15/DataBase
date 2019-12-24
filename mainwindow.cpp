#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    bd = std::make_unique<connectToBD>();

    connect(bd.get(), &connectToBD::openWorkerDialog, this, &MainWindow::showWorkerDialog);
}

void MainWindow::showWorkerDialog(std::shared_ptr<QSqlDatabase> db){
    database = db;
    workerDialog = std::make_unique<choseWorker>();
    connect(workerDialog.get(), &choseWorker::okOffice, this, &MainWindow::showOfficeDialog);
}
void MainWindow::showOfficeDialog(){
    officeDialog = std::make_unique<office>(database);
    connect(officeDialog.get(), &office::showCompanies, this, &MainWindow::showCompaniesDialog);
    connect(officeDialog.get(), &office::showWaybills, this, &MainWindow::showAllWaybillsDialog);
    connect(officeDialog.get(), &office::showChoseCompany, this, &MainWindow::showChoseCompanyDialog);
    connect(officeDialog.get(), &office::showDeleteWaybill, this, &MainWindow::showDeleteWaybillDialog);
    connect(officeDialog.get(), &office::showEditWaybill, this, &MainWindow::showEditWaybillDialog);
}

void MainWindow::showCompaniesDialog(){
    companiesDialog = std::make_unique<companies>(database);
}
void MainWindow::showAllWaybillsDialog(){
    waybillsDialog = std::make_unique<AllWayBills>(database);
    connect(waybillsDialog.get(), &AllWayBills::showEditWaybill, this, &MainWindow::showEditWaybillDialog);
}
void MainWindow::showChoseCompanyDialog(QString id_waybill){
    choseCompanyDialog = std::make_unique<choseCompany>(database, id_waybill);
    connect(choseCompanyDialog.get(), &choseCompany::showCompanies, this, &MainWindow::showCompaniesDialog);
    connect(choseCompanyDialog.get(), &choseCompany::showEditWaybill, this, &MainWindow::showEditWaybillDialog);
}
void MainWindow::showDeleteWaybillDialog(QString str){
    deleteWaybillDialog = std::make_unique<DeleteWaybill>(database, str);
}
void MainWindow::showEditWaybillDialog(QString id_waybill){
    editWaybillDialog = std::make_unique<waybill>(database, id_waybill);
}
