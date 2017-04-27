#include "table.h"

MultipageTable::MultipageTable(const StudentDatabase &db, QWidget *parent)
    : QTableWidget(parent), database(db)
{
    setMaxPageRows(DEFAULT_PAGE_ROW_COUNT);
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

    retrieveItems();
    connect(&database, SIGNAL(modelChanged()), this, SLOT(retrieveItems()));
}

void MultipageTable::retrieveItems()
{
    QList<Student> students = database.getStudents();
    foreach (const Student& student, students)
    {
        writeStudentInTable(student, students.indexOf(student));
    }
}

void MultipageTable::fitToContents()
{
    resizeColumnsToContents();
    horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}

int MultipageTable::getMaxPageRows() const
{
    return maxPageRows;
}

void MultipageTable::setMaxPageRows(int value)
{
    maxPageRows = value;
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
