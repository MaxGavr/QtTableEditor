#include "table.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

MultipageTable::MultipageTable(const StudentDatabase &db, QWidget *parent)
    : QWidget(parent), database(db)
{
    initTable();

    setCurrentPage(0);
    setStudentsPerPage(DEFAULT_STUDENTS_PER_PAGE);

    createPageControl();
    manageLayouts();

    getPage();
    connect(&database, SIGNAL(studentAdded()), this, SLOT(getPage()));
    connect(&database, SIGNAL(studentDeleted()), this, SLOT(getPage()));
}

void MultipageTable::getPage()
{
    clearTable();
    StudentDatabase::StudentSet page = database.getSetOfStudents(getCurrentPage(),
                                                                 getStudentsPerPage());
    foreach (Student::const_ref student, page)
    {
        writeStudentInTable(student, page.indexOf(student));
    }
}

void MultipageTable::initTable()
{
    table = new QTableWidget(this);

    table->setColumnCount(TOTAL_COLUMNS);
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem *firstColumnTitle = new QTableWidgetItem(tr("ФИО"));
    QTableWidgetItem *secondColumnTitle = new QTableWidgetItem(tr("Дата рождения"));
    QTableWidgetItem *thirdColumnTitle = new QTableWidgetItem(tr("Дата поступления"));
    QTableWidgetItem *fourthColumnTitle = new QTableWidgetItem(tr("Дата окончания"));
    table->setHorizontalHeaderItem(0, firstColumnTitle);
    table->setHorizontalHeaderItem(1, secondColumnTitle);
    table->setHorizontalHeaderItem(2, thirdColumnTitle);
    table->setHorizontalHeaderItem(3, fourthColumnTitle);

    fitTableToContents();
}

void MultipageTable::manageLayouts()
{
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->addWidget(firstPageButton);
    buttonLayout->addWidget(prevPageButton);
    buttonLayout->addWidget(pageSizeInput);
    buttonLayout->addWidget(currentPageLabel);
    buttonLayout->addWidget(nextPageButton);
    buttonLayout->addWidget(lastPageButton);

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addWidget(table);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void MultipageTable::createPageControl()
{
    nextPageButton = new QPushButton(tr("->"), this);
    prevPageButton = new QPushButton(tr("<-"), this);
    lastPageButton = new QPushButton(tr("-->"), this);
    firstPageButton = new QPushButton(tr("<--"), this);

    pageSizeInput = new QLineEdit(tr("Кол-во записей:"), this);
    currentPageLabel = new QLabel(tr("/"), this);
}

void MultipageTable::fitTableToContents()
{
    table->resizeColumnsToContents();
    table->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

int MultipageTable::getCurrentPage() const
{
    return currentPage;
}

void MultipageTable::setCurrentPage(int value)
{
    currentPage = value;
}

int MultipageTable::getStudentsPerPage() const
{
    return studentsPerPage;
}

void MultipageTable::setStudentsPerPage(int value)
{
    studentsPerPage = value;
}

void MultipageTable::writeStudentInTable(Student::const_ref student, int row)
{
    if (table->rowCount() <= row)
        table->insertRow(row);

    QTableWidgetItem *name = new QTableWidgetItem(student.getFullName());
    QTableWidgetItem *birth = new QTableWidgetItem(student.getBirthDate().toString(Qt::ISODate));
    QTableWidgetItem *enroll = new QTableWidgetItem(student.getEnrollmentDate().toString(Qt::ISODate));
    QTableWidgetItem *graduate = new QTableWidgetItem(student.getGraduationDate().toString(Qt::ISODate));

    table->setItem(row, Name, name);
    table->setItem(row, BirthDate, birth);
    table->setItem(row, EnrollmentDate, enroll);
    table->setItem(row, GraduationDate, graduate);

    fitTableToContents();
}

void MultipageTable::clearTable()
{
    table->clearContents();
    table->setRowCount(countStudents());
}

int MultipageTable::countStudents() const
{
    return students.count();
}
