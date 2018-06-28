#ifndef SPREADSHEET_H
#define SPREADSHEET_H

#include <QTableWidget>

class SpreadSheet :public QTableWidget
{
    Q_OBJECT

public:
    explicit SpreadSheet(QWidget *parent = 0);

    bool readFile(QString fileName);
    bool writeFile(QString fileName);

protected:

signals:

private slots:
    void findPrevious(const QString&str, Qt::CaseSensitivity cs);
    void findNext(const QString&str, Qt::CaseSensitivity cs);

private:

};

#endif // SPREADSHEET_H
