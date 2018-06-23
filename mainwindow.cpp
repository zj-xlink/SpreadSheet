#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QMessageBox>
#include <QApplication>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(800, 600);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    setWindowIcon(QIcon(":/image/new"));

}

void MainWindow::createActions()
{
    separatorAction = new QAction(this);
    separatorAction->setSeparator(true);

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
    saveAsAction->setShortcut(QKeySequence::SaveAs);
    saveAsAction->setStatusTip(tr("保存文件"));
    connect(saveAsAction,SIGNAL(triggered()),this,SLOT(saveAs()));

    for(int i = 0; i < MaxRecentFiles; i++){
        recentFileActions[i] = new QAction(this);
        recentFileActions[i]->setVisible(false);
        connect(recentFileActions[i], SIGNAL(triggered()), this ,SLOT(openRecentFiles()));
    }

    quitAction = new QAction(tr("退出(&E)"), this);
    quitAction->setShortcut(QKeySequence(tr("Ctrl+Q")));
    quitAction->setStatusTip(tr("退出"));
    connect(quitAction,SIGNAL(triggered()),this,SLOT(close()));


    cutAction = new QAction(tr("剪切(&T)"), this);
    cutAction->setIcon(QIcon(":/image/new"));
    cutAction->setShortcut(QKeySequence::Cut);
    cutAction->setStatusTip(tr("剪切"));
    connect(cutAction,SIGNAL(triggered()),this,SLOT(cut()));

    copyAction = new QAction(tr("复制(&C)"), this);
    copyAction->setIcon(QIcon(":/image/new"));
    copyAction->setShortcut(QKeySequence::Copy);
    copyAction->setStatusTip(tr("复制"));
    connect(copyAction,SIGNAL(triggered()),this,SLOT(copy()));

    pasteAction = new QAction(tr("粘贴(&P)"), this);
    pasteAction->setIcon(QIcon(":/image/new"));
    pasteAction->setShortcut(QKeySequence::Paste);
    pasteAction->setStatusTip(tr("粘贴"));
    connect(pasteAction,SIGNAL(triggered()),this,SLOT(copy()));

    deleteActon = new QAction(tr("删除(&D)"), this);
    deleteActon->setIcon(QIcon(":/image/new"));
    deleteActon->setShortcut(QKeySequence::Delete);
    deleteActon->setStatusTip(tr("删除"));
    connect(deleteActon,SIGNAL(triggered()),this,SLOT(copy()));

    rowAction = new QAction(tr("行(&R)"), this);
    rowAction->setIcon(QIcon(":/image/new"));
    rowAction->setStatusTip(tr("行"));
    connect(rowAction,SIGNAL(triggered()),this,SLOT(copy()));

    columnAction = new QAction(tr("列(&C)"), this);
    columnAction->setIcon(QIcon(":/image/new"));
    columnAction->setStatusTip(tr("列"));
    connect(columnAction,SIGNAL(triggered()),this,SLOT(copy()));

    allAction = new QAction(tr("行和列(&A)"), this);
    allAction->setIcon(QIcon(":/image/new"));
    allAction->setShortcut(QKeySequence(tr("Ctrl+A")));
    allAction->setStatusTip(tr("行和列"));
    connect(allAction,SIGNAL(triggered()),this,SLOT(copy()));

    findAction = new QAction(tr("查找单元(&F)"), this);
    findAction->setIcon(QIcon(":/image/new"));
    findAction->setShortcut(QKeySequence::Find);
    findAction->setStatusTip(tr("查找单元"));
    connect(findAction,SIGNAL(triggered()),this,SLOT(copy()));

    gotocellAction = new QAction(tr("定位单元(&G)"), this);
    gotocellAction->setIcon(QIcon(":/image/new"));
    gotocellAction->setShortcut(QKeySequence(tr("Ctrl+G")));
    gotocellAction->setStatusTip(tr("定位单元"));
    connect(gotocellAction,SIGNAL(triggered()),this,SLOT(copy()));


    reCalAction = new QAction(tr("重新计算(&R)"), this);
    reCalAction->setIcon(QIcon(":/image/new"));
    reCalAction->setShortcut(QKeySequence(tr("F9")));
    reCalAction->setStatusTip(tr("重新计算"));
    connect(reCalAction,SIGNAL(triggered()),this,SLOT(copy()));

    sortAction = new QAction(tr("排序...(&S)"), this);
    sortAction->setIcon(QIcon(":/image/new"));
    sortAction->setShortcut(QKeySequence(tr("F9")));
    sortAction->setStatusTip(tr("排序"));
    connect(sortAction,SIGNAL(triggered()),this,SLOT(copy()));

    showgridAction = new QAction(tr("显示网格(&S)"), this);
    showgridAction->setCheckable(true);
    showgridAction->setChecked(false);
    connect(showgridAction,SIGNAL(triggered()),this,SLOT(copy()));

    autoCalAction = new QAction(tr("自动计算(&A)"), this);
    autoCalAction->setCheckable(true);
    autoCalAction->setChecked(false);
    connect(autoCalAction,SIGNAL(triggered()),this,SLOT(copy()));

    aboutAction = new QAction(tr("关于(&A)"), this);
    aboutAction->setIcon(QIcon(":/image/new"));
    aboutAction->setStatusTip(tr("关于"));
    connect(aboutAction,SIGNAL(triggered()),this,SLOT(copy()));

    aboutQtAction = new QAction(tr("关于QT(&Q)"), this);
    aboutQtAction->setIcon(QIcon(":/image/new"));
    aboutQtAction->setStatusTip(tr("关于QT"));
    connect(aboutQtAction,SIGNAL(triggered()), qApp, SLOT(aboutQt()));

}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("文件(&F)"));
    fileMenu->addAction(newAction);
    fileMenu->addAction(openAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(saveAsAction);
    fileMenu->addAction(separatorAction);
    fileMenu->addAction(separatorAction);
    fileMenu->addAction(quitAction);

    editMenu = menuBar()->addMenu(tr("编辑(&E)"));
    editMenu->addAction(cutAction);
    editMenu->addAction(copyAction);
    editMenu->addAction(pasteAction);
    editMenu->addAction(deleteActon);
    selectMenu = editMenu->addMenu(tr("选择(&S)"));
    selectMenu->addAction(rowAction);
    selectMenu->addAction(columnAction);
    selectMenu->addAction(allAction);
    editMenu->addAction(separatorAction);
    editMenu->addAction(findAction);
    editMenu->addAction(gotocellAction);

    toolMenu = menuBar()->addMenu(tr("工具(&T)"));
    toolMenu->addAction(reCalAction);
    toolMenu->addAction(sortAction);

    optionMenu = menuBar()->addMenu(tr("选项(&O)"));
    optionMenu->addAction(showgridAction);
    optionMenu->addAction(autoCalAction);

    menuBar()->addSeparator();

    helpMenu = menuBar()->addMenu(tr("帮助(&H)"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

}

void MainWindow::createContextMenu()
{

}

void MainWindow::createToolBars()
{
    fileToolBar = addToolBar(tr("文件"));
    fileToolBar->addAction(newAction);
    fileToolBar->addAction(openAction);
    fileToolBar->addAction(saveAction);

    editToolBar = addToolBar(tr("编辑"));
    editToolBar->addAction(cutAction);
    editToolBar->addAction(copyAction);
    editToolBar->addAction(pasteAction);
    editToolBar->addSeparator();
    editToolBar->addAction(findAction);
    editToolBar->addAction(gotocellAction);
}
void MainWindow::createStatusBar()
{

}

void MainWindow::readSettings()
{

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

void MainWindow::about()
{

}

void MainWindow::cut()
{

}

void MainWindow::copy()
{

}

void MainWindow::openRecentFiles()
{

}
