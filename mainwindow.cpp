#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QMessageBox>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(800, 600);

    createActions();
    createMenus();



}

void MainWindow::createActions()
{
    newAction = new QAction(tr("新建文件(&N)"), this);
    newAction->setIcon(QIcon(":/image/new"));
    newAction->setShortcut(QKeySequence::New);
    newAction->setStatusTip(tr("新建文件"));
    connect(newAction,SIGNAL(triggered()),this,SLOT(newFile()));


    openAction = new QAction(tr("打开文件(&O)"), this);
    openAction->setIcon(QIcon(":/image/new"));
    openAction->setShortcut(QKeySequence::Open);
    openAction->setStatusTip(tr("打开文件"));
    connect(openAction,SIGNAL(triggered()),this,SLOT(open()));

    saveAction = new QAction(tr("保存文件(&S)"), this);
    saveAction->setIcon(QIcon(":/image/new"));
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip(tr("保存文件"));
    connect(saveAction,SIGNAL(triggered()),this,SLOT(save()));

    saveAsAction = new QAction(tr("另存为(&A)..."), this);
    saveAsAction->setIcon(QIcon(":/image/new"));
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("保存文件"));
    connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));


}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
}


void MainWindow::closeEvent(QCloseEvent *event)
{

}

void MainWindow::newFile()
{
    QMessageBox::information(NULL, tr("新建文件"),tr("新建文件"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
}

void MainWindow::open()
{
    QMessageBox::information(NULL, tr("打开文件"),tr("打开文件"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
}

bool MainWindow::save()
{
    QMessageBox::information(NULL, tr("保存文件"),tr("保存文件"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    return true;
}
bool MainWindow::saveAs()
{
    QMessageBox::information(NULL, tr("保存文件"),tr("保存文件"),QMessageBox::Yes | QMessageBox::No,QMessageBox::Yes);
    return true;
}

