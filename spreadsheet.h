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

private:

};

#endif // SPREADSHEET_H
