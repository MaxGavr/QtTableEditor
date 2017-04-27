#include "manager.h"

DatabaseManager::DatabaseManager(StudentDatabase *database)
{
    setDatabase(database);
}

void DatabaseManager::setDatabase(StudentDatabase *value)
{
    database = value;
}

void DatabaseManager::addStudent(const QString &first, const QString &second, const QString &middle,
                                 const QDate &birth, const QDate &enrollment, const QDate &graduation)
{
    database->addStudent(Student(first, second, middle, birth, enrollment, graduation));
}
