#ifndef FINDDIALOG_H
#define FINDDIALOG_H

#include <QDialog>

class QLabel;
class QLineEdit;
class QCheckBox;
class QPushButton;

class FindDialog : public QDialog
{
    Q_OBJECT

public:
    FindDialog(QWidget *parent = 0);

signals:
    void findPrevious(const QString& str,Qt::CaseSensitivity cs);
    void findNext(const QString& str,Qt::CaseSensitivity cs);

private slots:
    void enableFind(const QString& str);
    void closeWindow();
    void find();

private:
    QLabel *findLabel;
    QLineEdit *lineEdit;
    QCheckBox *matchBox;
    QCheckBox *searchBox;
    QPushButton *findButton;
    QPushButton *closeButton;
};

#endif // FINDDIALOG_H
