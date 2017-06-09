//
// VehicleTab.cpp
//
// Copyright (C) 2017
//

#include <QDataWidgetMapper>
#include <QDate>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QValidator>

#include "VehicleTab.h"

namespace TransportSystemDlg {

VehicleTab::VehicleTab(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    mIdSb->setReadOnly(true);
    mIdSb->setHidden(true);
    mIdLabel->setHidden(true);

    QRegularExpression rx(Vehicle::VEHICLE_REGULAR_EXPRESSION_VALID);
    QValidator *stringValidator = new QRegularExpressionValidator(rx);

    mBrandEdit->setMaxLength(20);
    mBrandEdit->setValidator(stringValidator);

    mModelEdit->setMaxLength(20);
    mModelEdit->setValidator(stringValidator);

    for (int i = QDate().currentDate().year(); i >= (int)Vehicle::MIN_VEHICLE_YEAR; i--)
        mYearCombo->addItem(QString("%1").arg(i), i);

    mPassengersSb->setMaximum(Vehicle::MAX_VEHICLE_PASSENGERS);
    mPassengersSb->setValue(1);
    mLoadCapacitySb->setMaximum(Vehicle::MAX_VEHICLE_LOAD_CAPACITY);
    mLoadCapacitySb->setValue(1);
    mFuelConsumptionSb->setMinimum(Vehicle::MIN_VEHICLE_FUEL_CONSUMPTION);
    mFuelConsumptionSb->setMaximum(Vehicle::MAX_VEHICLE_FUEL_CONSUMPTION);
    mFuelConsumptionSb->setValue(1.0);

    connect(mNewVehicleBtn, &QPushButton::clicked, this, &VehicleTab::onNewButtonClicked);
    connect(mDelVehicleBtn, &QPushButton::clicked, this, &VehicleTab::onDeleteButtonClicked);

    // Table widget
    mVehicleTableWidget->setColumnCount(6);
    mVehicleTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Brand")));
    mVehicleTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Model")));
    mVehicleTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Year")));
    mVehicleTableWidget->setHorizontalHeaderItem(3, new QTableWidgetItem(QString("Passengers")));
    mVehicleTableWidget->setHorizontalHeaderItem(4, new QTableWidgetItem(QString("Load")));
    mVehicleTableWidget->setHorizontalHeaderItem(5, new QTableWidgetItem(QString("Consumption")));

    mVehicleTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mVehicleTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    updateTable();
}

const QList<Vehicle> &VehicleTab::vehicleData() const
{
    return mVehicleData;
}

void VehicleTab::setVehicleData(const QList<Vehicle> &vehicleData)
{
    mVehicleData = vehicleData;

    updateTable();
}

void VehicleTab::onNewButtonClicked()
{
    mVehicleTableWidget->insertRow(mVehicleTableWidget->rowCount());


    mVehicleData.append(Vehicle(mBrandEdit->text(), mModelEdit->text(),
                                mYearCombo->itemData(mYearCombo->currentIndex()).toUInt(),
                                mPassengersSb->value(),mLoadCapacitySb->value(), mFuelConsumptionSb->value()));

    int row = mVehicleTableWidget->rowCount() - 1;

    QTableWidgetItem *col0 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).brand()));
    mVehicleTableWidget->setItem(row, 0, col0);
    QTableWidgetItem *col1 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).model()));
    mVehicleTableWidget->setItem(row, 1, col1);
    QTableWidgetItem *col2 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).year()));
    mVehicleTableWidget->setItem(row, 2, col2);
    QTableWidgetItem *col3 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).passengers()));
    mVehicleTableWidget->setItem(row, 3, col3);
    QTableWidgetItem *col4 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).loadCapacity()));
    mVehicleTableWidget->setItem(row, 4, col4);
    QTableWidgetItem *col5 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).fuelConsumption()));
    mVehicleTableWidget->setItem(row, 5, col5);

    emit vehicleRowAdded(mVehicleData);
}

void VehicleTab::onDeleteButtonClicked()
{
    int currRow = mVehicleTableWidget->currentRow();

    if (currRow < 0 or currRow >= mVehicleData.size()) {
        QMessageBox::information(this, "Vehicles", "No selected row to delete!");
        return;
    }

    emit vehicleRowDeleted(currRow);

    mVehicleTableWidget->removeRow(currRow);
    mVehicleTableWidget->selectRow(mVehicleTableWidget->currentRow());
    mVehicleData.removeAt(currRow);
}

void VehicleTab::updateTable()
{
    mVehicleTableWidget->setRowCount(mVehicleData.size());
    for (int row = 0; row < mVehicleData.size(); row++) {
        QTableWidgetItem *col0 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).brand()));
        mVehicleTableWidget->setItem(row, 0, col0);
        QTableWidgetItem *col1 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).model()));
        mVehicleTableWidget->setItem(row, 1, col1);
        QTableWidgetItem *col2 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).year()));
        mVehicleTableWidget->setItem(row, 2, col2);
        QTableWidgetItem *col3 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).passengers()));
        mVehicleTableWidget->setItem(row, 3, col3);
        QTableWidgetItem *col4 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).loadCapacity()));
        mVehicleTableWidget->setItem(row, 4, col4);
        QTableWidgetItem *col5 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(row).fuelConsumption()));
        mVehicleTableWidget->setItem(row, 5, col5);
    }
}

}   // namespace TransportSystemDlg
