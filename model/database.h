#pragma once

#include <QObject>
#include <QVector>
#include <QXmlStreamReader>
#include <QFile>

#include "student.h"
#include "xmlhandler.h"

class StudentDatabase : public QObject
{
    Q_OBJECT
public:
    using StudentSet = QVector<Student>;

    explicit StudentDatabase(QObject *parent = 0);

    Student getStudent(int index) const;
    StudentSet getSetOfStudents(int index, int amount) const;

    void addStudent(Student student);
    void removeStudent(Student::const_ref student);

    bool contains(Student::const_ref student) const;
    bool validateStudent(Student::const_ref student) const;
    bool validatePageBounds(int pageIndex, int studentsPerPage) const;

    int countStudents() const;
    int countPages(int studentsPerPage) const;

    XmlHandler *getXmlHandler();

signals:
    void studentAdded();
    void studentDeleted();

private:
    StudentSet students;

    XmlHandler xml;

    const int MIN_AGE = 18;
};
