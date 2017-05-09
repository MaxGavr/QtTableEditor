#include "table.h"

MultipageTable::MultipageTable(const StudentDatabase &db, QWidget *parent)
    : QTableWidget(parent), database(db)
{
    setCurrentPage(0);
    setStudentsPerPage(DEFAULT_STUDENTS_PER_PAGE);
    setColumnCount(TOTAL_COLUMNS);
    setEditTriggers(QAbstractItemView::NoEditTriggers);

    QTableWidgetItem *firstColumnTitle = new QTableWidgetItem(tr("ФИО"));
    QTableWidgetItem *secondColumnTitle = new QTableWidgetItem(tr("Дата рождения"));
    QTableWidgetItem *thirdColumnTitle = new QTableWidgetItem(tr("Дата поступления"));
    QTableWidgetItem *fourthColumnTitle = new QTableWidgetItem(tr("Дата окончания"));
    setHorizontalHeaderItem(0, firstColumnTitle);
    setHorizontalHeaderItem(1, secondColumnTitle);
    setHorizontalHeaderItem(2, thirdColumnTitle);
    setHorizontalHeaderItem(3, fourthColumnTitle);
    fitToContents();

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

void MultipageTable::fitToContents()
{
    resizeColumnsToContents();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
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

void MultipageTable::writeStudentInTable(const Student &student, int row)
{
    if (rowCount() <= row)
        insertRow(row);

    QTableWidgetItem *name = new QTableWidgetItem(student.getFullName());
    QTableWidgetItem *birth = new QTableWidgetItem(student.getBirthDate().toString(Qt::ISODate));
    QTableWidgetItem *enroll = new QTableWidgetItem(student.getEnrollmentDate().toString(Qt::ISODate));
    QTableWidgetItem *graduate = new QTableWidgetItem(student.getGraduationDate().toString(Qt::ISODate));

    setItem(row, Name, name);
    setItem(row, BirthDate, birth);
    setItem(row, EnrollmentDate, enroll);
    setItem(row, GraduationDate, graduate);

    fitToContents();
}

void MultipageTable::clearTable()
{
    clearContents();
    setRowCount(countStudents());
}

int MultipageTable::countStudents() const
{
    return students.count();
}
