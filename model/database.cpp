#include "database.h"

StudentDatabase::StudentDatabase(QObject *parent) : QObject(parent)
{   
}

QList<Student> StudentDatabase::getStudents() const
{
    return students;
}

void StudentDatabase::addStudent(Student student)
{
    if (!contains(student))
    {
        if (validateStudent(student))
        {
            students.append(student);
            emit modelChanged();
        }
        else
            emit invalidInsertion();
    }
    else
        emit duplicateInsertion();
}

void StudentDatabase::removeStudent(Student::const_ref student)
{
    if (contains(student))
    {
        emit studentDeleted(student);
        students.removeOne(student);
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


