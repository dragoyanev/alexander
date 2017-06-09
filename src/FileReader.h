//
// FileReader.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_FILEREADER_H
#define TRANSPORTSYSTEMGUI_FILEREADER_H

#include <QFile>
#include <QTextStream>
#include <QStringList>

namespace TransportSystemDlg {

class FileReader
{
public:
    FileReader(const QString &fileName, const QString &columnSeparator = ",",
              const QString &rowSeparator = "\n", const QString &elementSeparator = "|",
              bool skipEmptyParts = true);


    QString fileName() const { return mFileName; }
    QString columnSeparator() const { return mColumnSeparator; }
    QString rowSeparator() const { return mRowSeparator; }
    QString elementSeparator() const { return mElementSeparator; }
    int columnCount() const { return mColumnCount; }
    int rowCount() const { return mRowCount; }
    bool skipEmptyParts() const { return mSkipEmptyParts; }

    void setFileName(const QString &fileName) { mFileName = fileName; }
    void setColumnSeparator(const QString &colSeparator) { mColumnSeparator = colSeparator; }
    void setRowSeparator(const QString &rowSeparator) { mRowSeparator = rowSeparator; }
    void setElementSeparator(const QString &elementSeparator) { mElementSeparator = elementSeparator; }
    void setSkipEmptyParts(bool skipEmptyParts) { mSkipEmptyParts = skipEmptyParts; }

    int elementCount(int columnNumber) const;

    void readFileData();
    QString readWholeRow(int rowNumber) const;
    QString readCell(int rowNumber, int columnNumber) const;
    QStringList readColumn(int columnNumber) const;
    QStringList readRow(int rowNumber) const;
    QStringList parseCell(int rowNumber, int columnNumber) const;
    QStringList parseColumn(int columnNumber) const;
    QStringList parseRow(int rowNumber) const;
    QStringList elementFromColumn(QStringList column, int elementIndex, int elementCount) const;

private:
    QString mFileName;
    QString mColumnSeparator;
    QString mRowSeparator;
    QString mElementSeparator;
    QFile mFile;
    QTextStream mStream;
    QStringList mFileContent;
    int mColumnCount;
    int mRowCount;
    bool mSkipEmptyParts;
};

} // end of TransportSystemDlg namespace

#endif // TRANSPORTSYSTEMGUI_FILEREADER_H
