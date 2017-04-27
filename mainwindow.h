#pragma once

#include <QMainWindow>
#include <QAction>
#include <QMenuBar>
#include <QToolBar>
#include <QApplication>

#include "manager/manager.h"
#include "table/table.h"
#include "dialogs/adddialog.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(const StudentDatabase &db, DatabaseManager *mng, QWidget *parent = 0);
    ~MainWindow();

    DatabaseManager *getManager() const;
    void setManager(DatabaseManager *value);

    void createActions();
    void createMenus();
    void createToolBars();

public slots:
    void showAddDialog();

private:
    MultipageTable *table;

    DatabaseManager *manager;
    const StudentDatabase &database;

    QMenu *fileMenu;
    QMenu *editMenu;
    QMenu *helpMenu;
    QToolBar *editToolBar;

    QAction *addStudentAction;
    QAction *aboutQtAction;
};
