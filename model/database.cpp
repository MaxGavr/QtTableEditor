#include "database.h"
#include <math.h>

StudentDatabase::StudentDatabase(QObject *parent)
    : QObject(parent), xml(this)
{
}

Student StudentDatabase::getStudent(int index) const
{
    Student student;
    if (index < countStudents())
        student = students.at(index);
    return student;
}

StudentDatabase::StudentSet StudentDatabase::getSetOfStudents(int index, int amount) const
{
    if (!validatePageBounds(index, amount))
        return StudentSet();

    int initialPosition = index * amount;
    return students.mid(initialPosition, amount);
}

void StudentDatabase::addStudent(Student student)
{
    if (!contains(student) && validateStudent(student))
    {
        students.append(student);
        emit studentAdded();
    }
}

void StudentDatabase::removeStudent(Student::const_ref student)
{
    if (contains(student))
    {
        students.removeOne(student);
        emit studentDeleted();
    }
}

bool StudentDatabase::contains(Student::const_ref student) const
{
    return students.contains(student);
}

bool StudentDatabase::validateStudent(Student::const_ref student) const
{
    bool isValid = true;
    if (student.getFirstName().isEmpty() || student.getSecondName().isEmpty())
    {
        isValid = false;
    }

    int studentAge = student.getBirthDate().daysTo(QDate::currentDate());
    if ((studentAge / 365) < MIN_AGE)
    {
        isValid = false;
    }

    if (student.getEnrollmentDate() > student.getGraduationDate() ||
            student.getEnrollmentDate() < student.getBirthDate() ||
            student.getGraduationDate() < student.getBirthDate())
    {
        isValid = false;
    }

    return isValid;
}

int StudentDatabase::countStudents() const
{
    return students.count();
}

int StudentDatabase::countPages(int studentsPerPage) const
{
    return ceil(countStudents() / (double)studentsPerPage);
}

bool StudentDatabase::validatePageBounds(int pageIndex, int studentsPerPage) const
{
    return pageIndex < countPages(studentsPerPage);
}


