#pragma once

#include <QObject>
#include <QTableWidget>
#include <QHeaderView>
#include "../model/database.h"

class MultipageTable : public QTableWidget
{
    Q_OBJECT
public:
    explicit MultipageTable(const StudentDatabase &db, QWidget *parent = 0);

    enum TableField { Name = 0, BirthDate, EnrollmentDate, GraduationDate };

    void writeStudentInTable(const Student& student, int row);
    void clearTable();

    int countStudents() const;

    int getStudentsPerPage() const;
    void setStudentsPerPage(int value);

    int getCurrentPage() const;
    void setCurrentPage(int value);

public slots:
    void getPage();

private:
    void fitToContents();

    StudentDatabase::StudentSet students;

    const StudentDatabase &database;

    int currentPage;
    int studentsPerPage;
    const int DEFAULT_STUDENTS_PER_PAGE = 5;
    const int TOTAL_COLUMNS = 4;
};
