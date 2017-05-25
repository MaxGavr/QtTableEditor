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
    return getStudents().mid(initialPosition, amount);
}

void StudentDatabase::addStudent(Student student)
void StudentDatabase::setSearchPattern(const StudentSearchPattern &pattern)
{
    if (!contains(student) && validateStudent(student))
    this->pattern = pattern;
    if (!this->pattern.isEmpty())
        filterStudents();
    else
        clearSearchResult();
}

void StudentDatabase::filterStudents()
{
    clearSearchResult();
    foreach (Student::const_ref student, students)
        if (this->pattern(student))
            filteredStudents.append(student);
}

void StudentDatabase::clearSearchResult()
{
    filteredStudents.clear();
}
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
    return getStudents().count();
}

int StudentDatabase::countPages(int studentsPerPage) const
{
    return ceil(countStudents() / (double)studentsPerPage);
}

XmlHandler *StudentDatabase::getXmlHandler()
{
    return &xml;
}

const StudentDatabase::StudentSet &StudentDatabase::getStudents() const
{
    if (this->pattern.isEmpty())
        return students;
    else
        return filteredStudents;
}

void StudentDatabase::clear()
{
    foreach (Student::const_ref student, students) {
        removeStudent(student);
    }
}

bool StudentDatabase::validatePageBounds(int pageIndex, int studentsPerPage) const
{
    return pageIndex < countPages(studentsPerPage);
}


