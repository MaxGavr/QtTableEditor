#include "mainwindow.h"
#include "QMessageBox"
#include "QFileDialog"

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
    openFileAction = new QAction(tr("Открыть файл"), this);
    openFileAction->setShortcut(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Открыть файл с таблицей студентов"));
    connect(openFileAction, SIGNAL(triggered(bool)), this, SLOT(openFileDialog()));

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
    fileMenu->addAction(openFileAction);

    editMenu = menuBar()->addMenu(tr("Редактировать"));
    editMenu->addAction(addStudentAction);

    helpMenu = menuBar()->addMenu(tr("Справка"));
    helpMenu->addAction(aboutQtAction);
}

void MainWindow::createToolBars()
{
    fileToolBar = new QToolBar(tr("Работа с файлом"));
    fileToolBar->addAction(openFileAction);
    addToolBar(fileToolBar);

    editToolBar = new QToolBar(tr("Редактировать"));
    editToolBar->addAction(addStudentAction);
    addToolBar(Qt::LeftToolBarArea, editToolBar);
}

bool MainWindow::saveConfirmation()
{
    int respond = QMessageBox::warning(this, tr("Сохранить файл"),
                                       tr("Вы хотите сохранить изменения?"),
                                       QMessageBox::Yes | QMessageBox::No |
                                       QMessageBox::Cancel);
    if (respond == QMessageBox::Yes)
        return true;
    else if (respond == QMessageBox::Cancel)
        return false;
    return true;
}

void MainWindow::openFileDialog()
{
    if (saveConfirmation())
    {
        QString openFile = QFileDialog::getOpenFileName(this, tr("Открыть файл"),
                                                        QString(),
                                                        "Student table (*.xml)");
        getManager()->loadDatabaseFromFile(openFile);
        currentFile = openFile;
    }
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
