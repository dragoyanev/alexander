//
// RouteTab.cpp
//
// Copyright (C) 2017
//

#include <QDataWidgetMapper>
#include <QDate>
#include <QMessageBox>
#include <QRegularExpressionValidator>
#include <QValidator>

#include "RouteTab.h"

namespace TransportSystemDlg {

RouteTab::RouteTab(QWidget *parent) :
    QWidget(parent)
{
    setupUi(this);

    mIdSb->setReadOnly(true);
    mIdSb->setHidden(true);
    mIdLabel->setHidden(true);

    QRegularExpression rx(Route::ROUTE_REGULAR_EXPRESSION_VALID);
    QValidator *stringValidator = new QRegularExpressionValidator(rx);

    mPointsEdit->setMaxLength(100);
    mPointsEdit->setValidator(stringValidator);

    mDistanceSb->setMaximum(Route::MAX_ROUTE_DISTANCE);
    mDistanceSb->setValue(1);
    mDailyRepeatsSb->setMaximum(Route::MAX_ROUTE_DAILY_REPEATS);
    mDailyRepeatsSb->setValue(1);

    connect(mNewRouteBtn, &QPushButton::clicked, this, &RouteTab::onNewButtonClicked);
    connect(mDelRouteBtn, &QPushButton::clicked, this, &RouteTab::onDeleteButtonClicked);

    // Table widget
    mRouteTableWidget->setColumnCount(3);
    mRouteTableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(QString("Route")));
    mRouteTableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(QString("Distance")));
    mRouteTableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(QString("Daily Repeats")));

    mRouteTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    mRouteTableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);

    updateTable();
}

const QList<Route> &RouteTab::routeData() const
{
    return mRouteData;
}

void RouteTab::setRouteData(const QList<Route> &routeData)
{
    mRouteData = routeData;

    updateTable();
}

void RouteTab::onNewButtonClicked()
{
    mRouteTableWidget->insertRow(mRouteTableWidget->rowCount());

    mRouteData.append(Route(mPointsEdit->text(), mDistanceSb->value(), mDailyRepeatsSb->value()));

    int row = mRouteTableWidget->rowCount() - 1;

    QTableWidgetItem *col0 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(row).points()));
    mRouteTableWidget->setItem(row, 0, col0);
    QTableWidgetItem *col1 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(row).distance()));
    mRouteTableWidget->setItem(row, 1, col1);
    QTableWidgetItem *col2 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(row).dailyRepeats()));
    mRouteTableWidget->setItem(row, 2, col2);

    emit routeRowAdded(mRouteData);
}

void RouteTab::onDeleteButtonClicked()
{
    int currRow = mRouteTableWidget->currentRow();

    if (currRow < 0 or currRow >= mRouteData.size()) {
        QMessageBox::information(this, "Routes", "No selected row to delete!");
        return;
    }

    emit routeRowDeleted(currRow);

    mRouteTableWidget->removeRow(currRow);
    mRouteTableWidget->selectRow(mRouteTableWidget->currentRow());
    mRouteData.removeAt(currRow);
}

void RouteTab::updateTable()
{
    mRouteTableWidget->setRowCount(mRouteData.size());
    for (int row = 0; row < mRouteData.size(); row++) {
        QTableWidgetItem *col0 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(row).points()));
        mRouteTableWidget->setItem(row, 0, col0);
        QTableWidgetItem *col1 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(row).distance()));
        mRouteTableWidget->setItem(row, 1, col1);
        QTableWidgetItem *col2 = new QTableWidgetItem(QString("%1").arg(mRouteData.at(row).dailyRepeats()));
        mRouteTableWidget->setItem(row, 2, col2);
    }
}

}   // namespace TransportSystemDlg
