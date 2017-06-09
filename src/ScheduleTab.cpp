//
// ScheduleTab.cpp
//
// Copyright (C) 2017
//

#include <QDataWidgetMapper>
#include <QDate>
#include <QMessageBox>

#include "ScheduleTab.h"

namespace TransportSystemDlg {

ScheduleTab::ScheduleTab(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    mIdSb->setReadOnly(true);
    mIdSb->setHidden(true);
    mIdLabel->setHidden(true);

//    mVehicleIdCombo->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);
//    mRouteIdCombo->setSizeAdjustPolicy(QComboBox::SizeAdjustPolicy::AdjustToContents);

    mDailyFuelLabel->setHidden(true);
    mDailyFuelSb->setHidden(true);

    connect(mNewScheduleBtn, &QPushButton::clicked, this, &ScheduleTab::onNewButtonClicked);
    connect(mDelScheduleBtn, &QPushButton::clicked, this, &ScheduleTab::onDeleteButtonClicked);

    // Table widget
    mScheduleTableWidget->setColumnCount(3);
    mScheduleTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Vehicle")));
    mScheduleTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Route")));
    mScheduleTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Daily Fuel")));

    mScheduleTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mScheduleTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    updateTable();
}

const QList<Schedule> &ScheduleTab::scheduleData() const
{
    return mScheduleData;
}

void ScheduleTab::setScheduleData(const QList<Schedule> &scheduleData)
{
    mScheduleData = scheduleData;

    updateTable();
}

const QList<Vehicle> &ScheduleTab::vehicleData() const
{
    return mVehicleData;
}

void ScheduleTab::setVehicleData(const QList<Vehicle> &vehicleData)
{
    mVehicleData = vehicleData;

    refreshVehicleCombo();
}

const QList<Route> &ScheduleTab::routeData() const
{
    return mRouteData;
}

void ScheduleTab::setRouteData(const QList<Route> &routeData)
{
    mRouteData = routeData;

    refreshRouteCombo();
}

void ScheduleTab::onVehicleRowDeleted(unsigned currRow)
{
    qDebug("11 onVehicleRowDeleted mScheduleData.size()=%d", mScheduleData.size());

    for (int i = 0; i < mScheduleData.size(); i++) {
        if (mScheduleData.at(i).vehicleId() == currRow) {
            mScheduleData.removeAt(i);
            i--;
        }
    }

    qDebug("22 onVehicleRowDeleted mScheduleData.size()=%d", mScheduleData.size());
    for (int i = 0; i < mScheduleData.size(); i++) {
        if (mScheduleData.at(i).vehicleId() > currRow) {
            Schedule tmpSchedule;
            tmpSchedule.setVehicleId(mScheduleData.at(i).vehicleId() - 1);
            tmpSchedule.setRouteId(mScheduleData.at(i).routeId());
            mScheduleData.replace(i, tmpSchedule);
        }
    }

    mVehicleData.removeAt(currRow);
    refreshVehicleCombo();

    updateTable();
}

void ScheduleTab::onVehicleRowAdded(const QList<Vehicle> &vehicleData)
{
    setVehicleData(vehicleData);
}

void ScheduleTab::onRouteRowDeleted(unsigned currRow)
{
    for (int i = 0; i < mScheduleData.size(); i++) {
        if (mScheduleData.at(i).routeId() == currRow) {
            mScheduleData.removeAt(i);
            i--;
        }
    }
    for (int i = 0; i < mScheduleData.size(); i++) {
        if (mScheduleData.at(i).routeId() > currRow) {
            Schedule tmpSchedule;
            tmpSchedule.setVehicleId(mScheduleData.at(i).vehicleId());
            tmpSchedule.setRouteId(mScheduleData.at(i).routeId() - 1);
            mScheduleData.replace(i, tmpSchedule);
        }
    }

    mRouteData.removeAt(currRow);
    refreshRouteCombo();

    updateTable();
}

void ScheduleTab::onRouteRowAdded(const QList<Route> &routeData)
{
    setRouteData(routeData);
}

void ScheduleTab::onNewButtonClicked()
{
    qDebug("77 mScheduleTableWidget rows=%d", mScheduleTableWidget->rowCount());
    mScheduleTableWidget->insertRow(mScheduleTableWidget->rowCount());
    qDebug("88 mScheduleTableWidget rows=%d", mScheduleTableWidget->rowCount());

    mScheduleData.append(Schedule(mVehicleIdCombo->itemData(mVehicleIdCombo->currentIndex()).toUInt(),
                                  mRouteIdCombo->itemData(mRouteIdCombo->currentIndex()).toUInt()));

    int row = mScheduleTableWidget->rowCount() - 1;
    qDebug("mScheduleTableWidget rows=%d dataSize=%d", mScheduleTableWidget->rowCount(), mScheduleData.size());

    QTableWidgetItem *col0 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(mScheduleData.at(row).vehicleId()).brand() +
                                                                    " " +
                                                                    mVehicleData.at(mScheduleData.at(row).vehicleId()).model()));
    mScheduleTableWidget->setItem(row, 0, col0);
    QTableWidgetItem *col1 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(mScheduleData.at(row).routeId()).points()));
    mScheduleTableWidget->setItem(row, 1, col1);
    double fuel = mVehicleData.at(mScheduleData.at(row).vehicleId()).fuelConsumption() *
                  (mRouteData.at(mScheduleData.at(row).routeId()).distance() *
                   mRouteData.at(mScheduleData.at(row).routeId()).dailyRepeats()) / 100.0;
    QTableWidgetItem *col2 = new QTableWidgetItem(QString("%1").arg(fuel));
    mScheduleTableWidget->setItem(row, 2, col2);

    qDebug("mScheduleTableWidget rows=%d", mScheduleTableWidget->rowCount());

    updateTable();
}

void ScheduleTab::onDeleteButtonClicked()
{
    int currRow = mScheduleTableWidget->currentRow();

    if (currRow < 0 or currRow >= mScheduleData.size()) {
        QMessageBox::information(this, "Schedules", "No selected row to delete!");
        return;
    }

    mScheduleTableWidget->removeRow(currRow);
    mScheduleTableWidget->selectRow(mScheduleTableWidget->currentRow());
    mScheduleData.removeAt(currRow);

    updateTable();
}

void ScheduleTab::updateTable()
{
    for (int row = 0; row < mScheduleData.size(); row++) {
        bool error = false;

        if (mVehicleData.size() <= mScheduleData.at(row).vehicleId())
            error = true;
        if (mRouteData.size() <= mScheduleData.at(row).routeId())
            error = true;

        if (error) {
            mScheduleData.removeAt(row);
            row--;
            continue;
        }
    }

    mScheduleTableWidget->setRowCount(mScheduleData.size());
    for (int row = 0; row < mScheduleData.size(); row++) {
        QTableWidgetItem *col0 = new QTableWidgetItem(QString("%1").arg(mVehicleData.at(mScheduleData.at(row).vehicleId()).brand() +
                                                                        " " +
                                                                        mVehicleData.at(mScheduleData.at(row).vehicleId()).model()));
        mScheduleTableWidget->setItem(row, 0, col0);
        QTableWidgetItem *col1 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(mScheduleData.at(row).routeId()).points()));
        mScheduleTableWidget->setItem(row, 1, col1);
        double fuel = mVehicleData.at(mScheduleData.at(row).vehicleId()).fuelConsumption() *
                      (mRouteData.at(mScheduleData.at(row).routeId()).distance() *
                       mRouteData.at(mScheduleData.at(row).routeId()).dailyRepeats()) / 100.0;
        QTableWidgetItem *col2 = new QTableWidgetItem(QString("%1").arg(fuel));
        mScheduleTableWidget->setItem(row, 2, col2);
    }
}

void ScheduleTab::refreshVehicleCombo()
{
    mVehicleIdCombo->clear();

    for (int i = 0; i < mVehicleData.size(); i++) {
        mVehicleIdCombo->addItem(QString("%1").arg(mVehicleData.at(i).brand() + mVehicleData.at(i).model()), i);
    }
}

void ScheduleTab::refreshRouteCombo()
{
    mRouteIdCombo->clear();

    for (int i = 0; i < mRouteData.size(); i++) {
        mRouteIdCombo->addItem(QString("%1").arg(mRouteData.at(i).points()), i);
    }
}

}   // namespace TransportSystemDlg
