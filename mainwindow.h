#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QAction;
class QMenu;
class QToolBar;

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
    void about();

    void cut();
    void copy();


    void openRecentFiles();


private:
    void createActions();
    void createMenus();
    void createContextMenu();
    void createToolBars();
    void createStatusBar();

    void readSettings();

    QAction *separatorAction;
    QAction *newAction;
    QAction *openAction;
    QAction *saveAction;
    QAction *saveAsAction;
    enum {MaxRecentFiles = 5};
    QAction *recentFileActions[MaxRecentFiles];
    QAction *quitAction;

    QAction *cutAction;
    QAction *copyAction;
    QAction *pasteAction;
    QAction *deleteActon;
    QMenu *selectMenu;
    QAction *rowAction;
    QAction *columnAction;
    QAction *allAction;
    QAction *findAction;
    QAction *gotocellAction;

    QAction *reCalAction;
    QAction *sortAction;

    QAction *showgridAction;
    QAction *autoCalAction;

    QAction *aboutAction;
    QAction *aboutQtAction;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *toolMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QToolBar *fileToolBar;
    QToolBar *editToolBar;
};

#endif // MAINWINDOW_H
