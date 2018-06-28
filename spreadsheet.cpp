#include "spreadsheet.h"

SpreadSheet::SpreadSheet(QWidget *parent) :QTableWidget(parent)
{

}

bool SpreadSheet::readFile(QString fileName)
{
    return true;
}

bool SpreadSheet::writeFile(QString fileName)
{
    return true;
}

void SpreadSheet::findPrevious(const QString &str, Qt::CaseSensitivity cs)
{

}

void SpreadSheet::findNext(const QString &str, Qt::CaseSensitivity cs)
{

}
