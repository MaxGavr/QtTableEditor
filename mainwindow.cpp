#include "mainwindow.h"

MainWindow::MainWindow(const StudentDatabase &db, DatabaseManager *mng, QWidget *parent)
    : QMainWindow(parent), database(db)
{
    setManager(mng);

    createActions();
    createMenus();
    createToolBars();

    table = new MultipageTable(db, this);
    setCentralWidget(table);
    showMaximized();
}

MainWindow::~MainWindow()
{

}

void MainWindow::createActions()
{
    addStudentAction = new QAction(tr("Добавить запись"), this);
    addStudentAction->setShortcut(Qt::Key_1);
    addStudentAction->setStatusTip(tr("Добавить в таблицу новую запись с информацией о студенте"));
    connect(addStudentAction, SIGNAL(triggered(bool)), this, SLOT(showAddDialog()));

    aboutQtAction = new QAction(tr("О Qt"), this);
    aboutQtAction->setStatusTip(tr("Показать справочную информацию о библиотеке Qt"));
    connect(aboutQtAction, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("Файл"));

    editMenu = menuBar()->addMenu(tr("Редактировать"));
    editMenu->addAction(addStudentAction);

    helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    editToolBar = new QToolBar(tr("Редактировать"));
    editToolBar->addAction(addStudentAction);
    addToolBar(editToolBar);
}


DatabaseManager *MainWindow::getManager() const
{
    return manager;
}

void MainWindow::setManager(DatabaseManager *value)
{
    manager = value;
}

void MainWindow::showAddDialog()
{
    AddStudentDialog dialog(getManager(), this);
    dialog.exec();
}
