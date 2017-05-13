#pragma once

#include <QObject>
#include <QTableWidget>
#include <QPushButton>
#include <QHeaderView>
#include <QLineEdit>
#include <QLabel>
#include "../model/database.h"

class MultipageTable : public QWidget
{
    Q_OBJECT
public:
    MultipageTable(const StudentDatabase &db, QWidget *parent = 0);

    enum TableField { Name = 0, BirthDate, EnrollmentDate, GraduationDate };

    void writeStudentInTable(Student::const_ref student, int row);
    void clearTable();

    int countStudents() const;
    int maxPages() const;

    int getStudentsPerPage() const;
    void setStudentsPerPage(int value);

    int getCurrentPage() const;
    void setCurrentPage(int value);

public slots:
    void getPage();
    void updatePageLabel();

private:
    void initTable();
    void fitTableToContents();

    void manageLayouts();

    void createPageControl();

    QTableWidget *table;
    QPushButton *nextPageButton;
    QPushButton *prevPageButton;
    QPushButton *lastPageButton;
    QPushButton *firstPageButton;
    QLineEdit *pageSizeInput;
    QLabel *currentPageLabel;

    StudentDatabase::StudentSet students;

    const StudentDatabase &database;

    int currentPage;
    int studentsPerPage;
    const int DEFAULT_STUDENTS_PER_PAGE = 5;
    const int TOTAL_COLUMNS = 4;
};
