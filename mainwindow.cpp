#include "mainwindow.h"

#include <QAction>
#include <QMenuBar>
#include <QMenu>
#include <QToolBar>
#include <QStatusBar>
#include <QMessageBox>
#include <QApplication>
#include <QLabel>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMutableStringListIterator>
#include <QLineEdit>
#include <QSettings>

#include "spreadsheet.h"
#include "finddialog.h"
#include "gotocelldialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    resize(800, 600);
    spreadsheet = new SpreadSheet;
    setCentralWidget(spreadsheet);

    createActions();
    createMenus();
    createContextMenu();
    createToolBars();
    createStatusBar();

    readSettings();

    findDlg = 0;

    setWindowIcon(QIcon(":/image/new"));

}
MainWindow::~MainWindow()
{
    writeSettings();
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
    connect(findAction,SIGNAL(triggered()),this,SLOT(findCell()));

    gotocellAction = new QAction(tr("定位单元(&G)"), this);
    gotocellAction->setIcon(QIcon(":/image/new"));
    gotocellAction->setShortcut(QKeySequence(tr("Ctrl+G")));
    gotocellAction->setStatusTip(tr("定位单元"));
    connect(gotocellAction,SIGNAL(triggered()),this,SLOT(gotoCell()));


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
    separatorAction = fileMenu->addSeparator();
    for(int i = 0; i < MaxRecentFiles; i++){
        fileMenu->addAction(recentFileActions[i]);
    }
    fileMenu->addSeparator();

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
    spreadsheet->addAction(cutAction);
    spreadsheet->addAction(copyAction);
    spreadsheet->addAction(pasteAction);

    spreadsheet->setContextMenuPolicy(Qt::ActionsContextMenu);
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
    locationLabel = new QLabel(tr("W999"));
    locationLabel->setMinimumSize(locationLabel->sizeHint());

    formulaLabel = new QLabel;
    formulaLabel->setIndent(3);

    statusBar()->addWidget(locationLabel);
    statusBar()->addWidget(formulaLabel, 1);

}

void MainWindow::readSettings()
{
    QSettings settings("Software Inc.", "SpreadSheet");

    restoreGeometry(settings.value("geometry").toByteArray());

    recentFiles = settings.value("recentFiles").toStringList();
    updateRecentFileActions();

    showgridAction->setChecked(settings.value("showGrid").toBool());
    reCalAction->setChecked(settings.value("autoRecalc").toBool());

}
void MainWindow::writeSettings()
{
    QSettings settings("Software Inc.", "SpreadSheet");
    settings.setValue("geometry", saveGeometry());
    settings.setValue("recentFiles", recentFiles);
    settings.setValue("showGrid", showgridAction->isChecked());
    settings.setValue("autoRecalc", reCalAction->isChecked());
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(okToContinue()){
        writeSettings();
        event->accept();
    }else
        event->ignore();
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    curFile = fileName;
    setWindowModified(false);

    QString shownName = tr("Untitled");
    if(!curFile.isEmpty()){
        shownName = strippedName(curFile);
        recentFiles.removeAll(curFile);
        recentFiles.prepend(curFile);
        updateRecentFileActions();
    }
    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("SpreadSheet")));
}

void MainWindow::updateRecentFileActions()
{
    QMutableStringListIterator i(recentFiles);
    while(i.hasNext()){
        if(!QFile::exists(i.next())){
            i.remove();
        }
    }

    for(int i=0;i<MaxRecentFiles; i++){
        if(i<recentFiles.count()){
            QString text = tr("&%1 %2")
                            .arg(i+1)
                            .arg(strippedName(recentFiles[i]));
            recentFileActions[i]->setText(text);
            recentFileActions[i]->setData(recentFiles[i]);
            recentFileActions[i]->setVisible(true);
        }else{
            recentFileActions[i]->setVisible(false);
        }
    }
    separatorAction->setVisible(!recentFiles.isEmpty());
}

bool MainWindow::okToContinue()
{
    if(isWindowModified()){
        int r = QMessageBox::warning(this, tr("SpreadSheet"), tr("The document has been modified\n"
                                                         "Do you want to save your changes?"),
                             QMessageBox::Yes | QMessageBox::No | QMessageBox::Cancel);
        if(r == QMessageBox::Yes){
            save();
            return true;
        }
        if(r == QMessageBox::Cancel)
            return false;
    }
    return true;
}

void MainWindow::newFile()
{
    //if(okToContinue()){
       // spreadsheet->clear();
       // setCurrentFile("");

        MainWindow *main = new MainWindow;
        main->show();
   // }
}

bool MainWindow::loadFile(QString fileName)
{
    if(!spreadsheet->readFile(fileName)){
        statusBar()->showMessage(tr("加载文件失败"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("加载成功"), 2000);
    return true;

}

void MainWindow::open()
{
    if(okToContinue()){
        QString fileName = QFileDialog::getOpenFileName(this, tr("打开SpreadSheet文件"),".",
                                     tr("SpreadSheet File(*.sp)"));
        if(!fileName.isEmpty()){
            loadFile(fileName);
        }
    }
}

bool MainWindow::saveFile(QString fileName)
{
    if(!spreadsheet->writeFile(fileName)){
        statusBar()->showMessage(tr("保存文件失败"), 2000);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("保存成功"), 2000);
    return true;

}
bool MainWindow::save()
{
    if(curFile.isEmpty()){
        return saveAs();
    }else{
        return saveFile(curFile);
    }
}

bool MainWindow::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("保存SpreadSheet文件"),".",
                                 tr("SpreadSheet文件(*.sp)"));
    if(fileName.isEmpty()){
        return false;
    }
    return saveFile(fileName);;
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
    QAction *action = qobject_cast<QAction*>(sender());
    if(action){
        loadFile(action->data().toString());
    }
}

void MainWindow::findCell()
{
    if(!findDlg){
        findDlg = new FindDialog(this);
        connect(findDlg, SIGNAL(findPrevious(QString,Qt::CaseSensitivity)),
                spreadsheet, SLOT(findPrevious(QString,Qt::CaseSensitivity)));
        connect(findDlg, SIGNAL(findPrevious(QString,Qt::CaseSensitivity)),
                spreadsheet, SLOT(findPrevious(QString,Qt::CaseSensitivity)));
    }

    findDlg->show();
    findDlg->raise();
    findDlg->activateWindow();
}

void MainWindow::gotoCell()
{
    GotoCellDialog *dlg = new GotoCellDialog(this);
    if(dlg->exec()){
        QString str = dlg->GetString();
        spreadsheet->setCurrentCell(str.mid(1).toInt() - 1,
                                    str[0].unicode() - 'A');
    }
    delete dlg;
}
