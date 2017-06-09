//
// FileWriter.h
//
// Copyright (C) 2017
//

#ifndef TRANSPORTSYSTEMGUI_FILEWRITER_H
#define TRANSPORTSYSTEMGUI_FILEWRITER_H

#include <QFile>
#include <QTextStream>
#include <QStringList>

namespace TransportSystemDlg {

class FileWriter
{
public:
    FileWriter(const QString &fileName) :
            mFileName(fileName),
            mColumnSeparator(","),
            mRowSeparator("\n"),
            mFile(fileName),
            mStream(&mFile)
    {
        mFile.open(QIODevice::WriteOnly);
    }

    QString fileName() const { return mFileName; }

    QString rowSeparator() const { return mRowSeparator; }
    QString columnSeparator() const { return mColumnSeparator; }

    void setRowSeparator(const QString &sep) { mRowSeparator = sep; }
    void setColumnSeparator(const QString &sep) { mColumnSeparator = sep; }

    void addRow(const QStringList &row) { mStream << row.join(mColumnSeparator) + mRowSeparator; }
    FileWriter& operator<<(const QStringList &row) { addRow(row); return *this; }

private:
    QString mFileName;
    QString mColumnSeparator;
    QString mRowSeparator;
    QFile mFile;
    QTextStream mStream;
};

class CSVColumn
{
public:
     CSVColumn () : mElemSeparator("|") { }

     QString column() const { return mColumn; }
     QString elemSeparator() const { return mElemSeparator; }

     void setColumn(const QString &col) { mColumn = col; }
     void setElemSeparator(const QString &sep) { mElemSeparator = sep; }

     QString addElement(const QString &elem);
     CSVColumn& operator<<(const QString &elem);
     CSVColumn& operator<<(int elem);

     operator QString() { return mColumn; }

 private:
     QString mColumn;
     QString mElemSeparator;
};

} // end of TransportSystemDlg namespace

#endif // TRANSPORTSYSTEMGUI_FILEWRITER_H
