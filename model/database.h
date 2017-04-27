#pragma once

#include <QObject>
#include <QList>

#include "student.h"

class StudentDatabase : public QObject
{
    Q_OBJECT
public:
    explicit StudentDatabase(QObject *parent = 0);

    QList<Student> getStudents() const;

    void addStudent(Student student);
    void removeStudent(Student::const_ref student);

    bool contains(Student::const_ref student) const;
    bool validateStudent(Student::const_ref student) const;

signals:
    void modelChanged();
    void studentAdded(Student newStudent);
    void studentDeleted(Student deletedStudent);
    void duplicateInsertion();
    void invalidInsertion();

private:
    QList<Student> students;

    const int MIN_AGE = 18;
};
