#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = 0);

protected:
    void closeEvent(QCloseEvent *event);

signals:

private slots:
    void newFile();
    void open();
    bool save();

private:
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
};

#endif // MAINWINDOW_H
