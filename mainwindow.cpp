#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMenu>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(800, 600);

    newAction = new QAction(tr("打开文件"), this);
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("打开新文件"));


    QMenu *menu = menuBar()->addMenu(tr("文件"));
    menu->addAction(newAction);





}

void MainWindow::closeEvent(QCloseEvent *event)
{

}

void MainWindow::newFile()
{

}

void MainWindow::open()
{

}

bool MainWindow::save()
{
    return true;
}

