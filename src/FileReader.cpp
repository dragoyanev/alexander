//
// FileReader.cpp
//
// Copyright (C) 2017
//

#include "FileReader.h"

namespace TransportSystemDlg { // start of TransportSystemDlg namespace

FileReader::FileReader(const QString &fileName, const QString &columnSeparator,
                       const QString &rowSeparator, const QString &elementSeparator,
                       bool skipEmptyParts) :
    mFileName(fileName),
    mColumnSeparator(columnSeparator),
    mRowSeparator(rowSeparator),
    mElementSeparator(elementSeparator),
    mFile(mFileName),
    mStream(&mFile),
    mSkipEmptyParts(skipEmptyParts)
{

}

int FileReader::elementCount(int columnNumber) const
{
    if (columnNumber >= mColumnCount || columnNumber < 0)
        return 0;

    QStringList column = readColumn(columnNumber);
    QRegExp exp("[" + elementSeparator() + "]*[" + elementSeparator() + "]");
    QStringList tmp = column.value(0).split(exp, mSkipEmptyParts ? QString::SkipEmptyParts : QString::KeepEmptyParts);

    return tmp.size();
}

QString FileReader::readWholeRow(int rowNumber) const
{
    if (rowNumber >= mRowCount || rowNumber < 0)
        return QString();
    return mFileContent.at(rowNumber);
}

QString FileReader::readCell(int rowNumber, int columnNumber) const
{
    if (rowNumber >= mRowCount || rowNumber < 0)
        return QString();
    if (columnNumber >= mColumnCount || columnNumber < 0)
        return QString();

    QStringList tmp = readRow(rowNumber);
    if(columnNumber >= tmp.size())
        return QString();
    return tmp[columnNumber];
}

QStringList FileReader::readColumn(int columnNumber) const
{
    if (columnNumber >= mColumnCount || columnNumber < 0)
        return QStringList();

    QStringList tmp;
    foreach (QString x, mFileContent)
        if (!x.isEmpty())
            tmp += x.split(mColumnSeparator, mSkipEmptyParts ? QString::SkipEmptyParts : QString::KeepEmptyParts);

    QStringList column;
    for (int x = columnNumber; x < tmp.size(); x += mColumnCount)
        column += tmp[x];

    return column;
}

QStringList FileReader::readRow(int rowNumber) const
{
    if (rowNumber >= mRowCount || rowNumber < 0)
        return QStringList();

    QStringList tmp = mFileContent.at(rowNumber).split(mColumnSeparator, mSkipEmptyParts ? QString::SkipEmptyParts : QString::KeepEmptyParts);
    return tmp;
}

QStringList FileReader::parseCell(int rowNumber, int columnNumber) const
{
    QString tmp = readCell(rowNumber, columnNumber);

    if (mElementSeparator.isEmpty())
        return QStringList(tmp);

    return tmp.split(mElementSeparator, mSkipEmptyParts ? QString::SkipEmptyParts : QString::KeepEmptyParts);
}

QStringList FileReader::parseColumn(int columnNumber) const
{
    QStringList tmp = readColumn(columnNumber);

    if (mElementSeparator.isEmpty())
        return tmp;

    QStringList str;
    foreach (QString x, tmp)
        str += x.split(mElementSeparator, mSkipEmptyParts ? QString::SkipEmptyParts : QString::KeepEmptyParts);

    return str;
}

QStringList FileReader::parseRow(int rowNumber) const
{
    QStringList tmp = readRow(rowNumber);

    if (mElementSeparator.isEmpty())
        return tmp;

    QStringList row;
    foreach(QString x, tmp)
        row += x.split(mElementSeparator, mSkipEmptyParts ? QString::SkipEmptyParts : QString::KeepEmptyParts);

    return row;
}

QStringList FileReader::elementFromColumn(QStringList column, int elementIndex, int elementCount) const
{
    if (elementIndex >= elementCount || elementIndex < 0)
        return QStringList();

    QStringList elements;
    for (int x = elementIndex; x < column.size(); x += elementCount)
        elements += column[x];
    return elements;
}

void FileReader::readFileData()
{
    if (mFile.open(QIODevice::ReadOnly | QIODevice::Text))
        mFileContent = mStream.readAll().split(mRowSeparator, mSkipEmptyParts ? QString::SkipEmptyParts : QString::KeepEmptyParts);
    mFile.close();

    if (!mFileContent.isEmpty()) {
        // Remove possible last empty line.
        if (mFileContent.last().isEmpty())
            mFileContent.removeLast();

        if (!mFileContent.isEmpty())
            mColumnCount = mFileContent.first().count(mElementSeparator + mColumnSeparator + mElementSeparator) + 1;
    } else {
        mColumnCount = 0;
    }

    mRowCount = mFileContent.size();
}

}
