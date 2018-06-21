#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;

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
    bool saveAs();

private:
    void createActions();
    void createMenus();

    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;

    QMenu *fileMenu;
};

#endif // MAINWINDOW_H
