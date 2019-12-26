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
    connect(workerDialog.get(), &choseWorker::okSklad, this, &MainWindow::showSkladChoseWaybillDialog);
    connect(workerDialog.get(), &choseWorker::okManufacture, this, &MainWindow::showManufactureChoseWaybillDialog);
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
void MainWindow::showSkladChoseWaybillDialog(){
    skladChoseWaybillDialog = std::make_unique<SkladChoseWaybill>(database);
    connect(skladChoseWaybillDialog.get(), &SkladChoseWaybill::showWaybillSklad, this, &MainWindow::showWaybillSkladDialog);
}
void MainWindow::showWaybillSkladDialog(QString id_waybill){
    waybillSkladDialog = std::make_unique<waybillSklad>(database, id_waybill);
}
void MainWindow::showManufactureChoseWaybillDialog(){
    manufactureChoseWaybillDialog = std::make_unique<manufactureChoseWaybill>(database);
    connect(manufactureChoseWaybillDialog.get(), &manufactureChoseWaybill::showWaybillManufacture, this, &MainWindow::showWaybillManufactureDialog);
    connect(manufactureChoseWaybillDialog.get(), &manufactureChoseWaybill::showControlManufacture, this, &MainWindow::showManufactureControlDialog);
}
void MainWindow::showWaybillManufactureDialog(QString id_waybill){
    waybillManufactureDialog = std::make_unique<waybillManufacture>(database, id_waybill);
}
void MainWindow::showManufactureControlDialog(QString id_waybill){
    manufactureControlDialog = std::make_unique<ManufactureControl>(database, id_waybill);
}
