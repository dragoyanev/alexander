//
// FileWriter.cpp
//
// Copyright (C) 2017
//


#include "FileWriter.h"

namespace TransportSystemDlg {

QString CSVColumn::addElement(const QString &elem)
{
    return elemSeparator() + elem + elemSeparator();
}

CSVColumn& CSVColumn::operator <<(const QString &elem)
{
    mColumn.append(addElement(elem));
    return *this;
}

CSVColumn& CSVColumn::operator <<(int elem)
{
    mColumn.append(addElement(QString::number(elem)));
    return *this;
}

} // end of TransportSystemDlg namespace
