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

    int getMaxPageRows() const;
    void setMaxPageRows(int value);

public slots:
    void retrieveItems();

private:
    void fitToContents();

    QList<Student> students;

    const StudentDatabase &database;

    int maxPageRows;
    const int DEFAULT_PAGE_ROW_COUNT = 5;
    const int TOTAL_COLUMNS = 4;
};
