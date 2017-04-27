#pragma once

#include "../model/database.h"

class DatabaseManager
{
public:
    DatabaseManager(StudentDatabase *database);

    void setDatabase(StudentDatabase *value);

    void addStudent(const QString &first, const QString &second, const QString &middle,
                    const QDate &birth, const QDate &enrollment, const QDate &graduation);

private:
    StudentDatabase *database;
};
