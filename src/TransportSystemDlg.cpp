//
// TransportSystemDlg.cpp
//
// Copyright (C) 2017
//
#include <iostream>

#include <QDir>
#include <QFileDialog>

#include "TransportSystemDlg.h"

#include "FileReader.h"
#include "FileWriter.h"

namespace TransportSystemDlg {

TransportSystemDlg::TransportSystemDlg(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);

    // Init object structure
    mVehicles.clear();
    mRoutes.clear();

    initVehicles();
    initRoutes();
//---------------------------------------
//---------------------------------------

    buildUI();

    connections();
}

TransportSystemDlg::~TransportSystemDlg()
{
}

void TransportSystemDlg::printDebugLog()
{
    mVehicles = mVehicleTab->vehicleData();
    qDebug("vehicle size = %d",mVehicles.size());

    mRoutes = mRouteTab->routeData();
    qDebug("route size = %d",mRoutes.size());
}

void TransportSystemDlg::saveFiles()
{
    saveFileVehicles();
    saveFileRoutes();
}

void TransportSystemDlg::buildUI()
{
    qDebug("mVehicles.size=%d",mVehicles.size());
    mVehicleTab = new VehicleTab();
    mVehicleTab->setVehicleData(mVehicles);
    mTabWidget->addTab(mVehicleTab, "Vehicles");

    qDebug("mRoutes.size=%d",mRoutes.size());
    mRouteTab = new RouteTab();
    mRouteTab->setRouteData(mRoutes);
    mTabWidget->addTab(mRouteTab, "Routes");
}

void TransportSystemDlg::connections()
{
    connect(mCloseBtn, SIGNAL(clicked()), this, SLOT(printDebugLog()));
    connect(mCloseBtn, SIGNAL(clicked()), this, SLOT(saveFiles()));
    connect(mCloseBtn, SIGNAL(clicked()), this, SLOT(close()));
}

void TransportSystemDlg::initVehicles()
{
    bool vehicleFileFails = false;

    QString filePath = QApplication::applicationDirPath() + "/../var/";
    qDebug("filePath=%s",qPrintable(filePath));

    QDir tmpDir(filePath);
    if (!tmpDir.exists()) {
        qDebug("filePath NOT exists");
        if (!tmpDir.mkpath(filePath)) {
            qDebug("filePath -> can't create dir '%s'\n", qPrintable(filePath));
            vehicleFileFails = true;
        }
    }

    QString fileName = "vehicles.csv";
    if (vehicleFileFails == false) {

        QStringList filters;
        filters << fileName;

        QStringList existingFile = tmpDir.entryList(filters, QDir::Files, QDir::Name);

        if (existingFile.empty()) {
            qDebug("existingFile empty");
            QFileDialog fileDialog;

            fileDialog.setNameFilter("(*.csv)");

            if (fileDialog.exec()) {
                qDebug("Selected file: %s",qPrintable(fileDialog.selectedFiles()[0]));
                fileName = fileDialog.selectedFiles()[0];
            } else
                vehicleFileFails = true;
        } else {
            qDebug("existingFile NOT empty");
            foreach (QString fileName, existingFile)
                qDebug("%s", qPrintable(fileName));
            fileName = filePath + fileName;
        }
    }

    if (vehicleFileFails == false) {
        qDebug("OPEN vehicles.csv");
        FileReader fileReader(fileName, ",", "\n", "|", false);
        fileReader.readFileData();

        qDebug("fileReader.rowCount()=%d",fileReader.rowCount());
        for (int row = 0; row < fileReader.rowCount(); row++) {
            QStringList rowData = fileReader.readRow(row);
            if (rowData.size() == 6) {
                mVehicles.append(Vehicle(rowData.at(0), rowData.at(1),
                                         rowData.at(2).toUInt(), rowData.at(3).toUInt(),
                                         rowData.at(4).toUInt(), rowData.at(5).toDouble()));
                qDebug()<<(mVehicles.last());
            } else
                qDebug("Error rowData.size() %d <> 6",rowData.size());
        }
    }
}

void TransportSystemDlg::initRoutes()
{
    bool routeFileFails = false;

    QString filePath = QApplication::applicationDirPath() + "/../var/";
    qDebug("filePath=%s",qPrintable(filePath));

    QDir tmpDir(filePath);
    if (!tmpDir.exists()) {
        qDebug("filePath NOT exists");
        if (!tmpDir.mkpath(filePath)) {
            qDebug("filePath -> can't create dir '%s'\n", qPrintable(filePath));
            routeFileFails = true;
        }
    }

    QString fileName = "routes.csv";
    if (routeFileFails == false) {

        QStringList filters;
        filters << fileName;

        QStringList existingFile = tmpDir.entryList(filters, QDir::Files, QDir::Name);

        if (existingFile.empty()) {
            qDebug("existingFile empty");
            QFileDialog fileDialog;

            fileDialog.setNameFilter("(*.csv)");

            if (fileDialog.exec()) {
                qDebug("Selected file: %s",qPrintable(fileDialog.selectedFiles()[0]));
                fileName = fileDialog.selectedFiles()[0];
            } else
                routeFileFails = true;
        } else {
            qDebug("existingFile NOT empty");
            foreach (QString fileName, existingFile)
                qDebug("%s", qPrintable(fileName));
            fileName = filePath + fileName;
        }
    }

    if (routeFileFails == false) {
        qDebug("OPEN routes.csv");
        FileReader fileReader(fileName, ",", "\n", "|", false);
        fileReader.readFileData();

        qDebug("fileReader.rowCount()=%d",fileReader.rowCount());
        for (int row = 0; row < fileReader.rowCount(); row++) {
            QStringList rowData = fileReader.readRow(row);
            if (rowData.size() == 3) {
                mRoutes.append(Route(rowData.at(0), rowData.at(1).toUInt(), rowData.at(2).toUInt()));
                qDebug()<<(mRoutes.last());
            } else
                qDebug("Error rowData.size() %d <> 3",rowData.size());
        }
    }
}

void TransportSystemDlg::saveFileVehicles()
{
    mVehicles = mVehicleTab->vehicleData();

    bool vehicleFileFails = false;

    QString filePath = QApplication::applicationDirPath() + "/../var/";
    QDir tmpDir(filePath);
    if (!tmpDir.exists()) {
        if (!tmpDir.mkpath(filePath)) {
            qDebug("filePath -> can't create dir '%s'\n", qPrintable(filePath));
            vehicleFileFails = true;
        }
    }

    QString fileName = filePath + "vehicles.csv";
    if (vehicleFileFails)
        QMessageBox::critical(this, "Vehicles", "Can't create directory %s!",qPrintable(filePath));
    else {
        FileWriter fileWriter(fileName);

        for (int row = 0; row < mVehicles.size(); row++) {
            QStringList rowData;
            rowData.append(mVehicles.at(row).brand());
            rowData.append(mVehicles.at(row).model());
            rowData.append(QString("%1").arg(mVehicles.at(row).year()));
            rowData.append(QString("%1").arg(mVehicles.at(row).passengers()));
            rowData.append(QString("%1").arg(mVehicles.at(row).loadCapacity()));
            rowData.append(QString("%1").arg(mVehicles.at(row).fuelConsumption()));

            fileWriter.addRow(rowData);
        }
    }
}

void TransportSystemDlg::saveFileRoutes()
{
    mRoutes = mRouteTab->routeData();

    bool routeFileFails = false;

    QString filePath = QApplication::applicationDirPath() + "/../var/";
    QDir tmpDir(filePath);
    if (!tmpDir.exists()) {
        if (!tmpDir.mkpath(filePath)) {
            qDebug("filePath -> can't create dir '%s'\n", qPrintable(filePath));
            routeFileFails = true;
        }
    }

    QString fileName = filePath + "routes.csv";
    if (routeFileFails)
        QMessageBox::critical(this, "Routes", "Can't create directory %s!",qPrintable(filePath));
    else {
        FileWriter fileWriter(fileName);

        for (int row = 0; row < mRoutes.size(); row++) {
            QStringList rowData;
            rowData.append(mRoutes.at(row).points());
            rowData.append(QString("%1").arg(mRoutes.at(row).distance()));
            rowData.append(QString("%1").arg(mRoutes.at(row).dailyRepeats()));

            fileWriter.addRow(rowData);
        }
    }
}


}   // namespace TransportSystemDlg

