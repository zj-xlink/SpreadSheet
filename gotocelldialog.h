#ifndef GOTOCELLDIALOG_H
#define GOTOCELLDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QPushButton;

class GotoCellDialog : public QDialog
{
    Q_OBJECT

public:
    GotoCellDialog(QWidget *parent = 0);
    QString GetString();

private slots:
    void enableOK(const QString &str);

private:
    QLabel *label;
    QLineEdit *lineEdit;
    QPushButton *okButton;
    QPushButton *cancelButton;
};

#endif // GOTOCELLDIALOG_H
