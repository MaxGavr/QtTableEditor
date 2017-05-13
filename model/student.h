#pragma once

#include <QString>
#include <QDate>

class Student
{
public:
    typedef const Student& const_ref;

    Student();
    Student(const QString& first, const QString& second, const QString& middle,
            const QDate& birth, const QDate& enrollment, const QDate& graduation);
    Student(const_ref student);

    QString getFirstName() const;
    void setFirstName(const QString &value);
    QString getSecondName() const;
    void setSecondName(const QString &value);
    QString getMiddleName() const;
    void setMiddleName(const QString &value);

    QString getFullName() const;

    QDate getBirthDate() const;
    QString getBirthDateString() const;
    void setBirthDate(const QDate &value);
    QDate getEnrollmentDate() const;
    QString getEnrollmentDateString() const;
    void setEnrollmentDate(const QDate &value);
    QDate getGraduationDate() const;
    QString getGraduationDateString() const;
    void setGraduationDate(const QDate &value);

    bool operator== (const_ref student) const;
    bool operator!= (const_ref student) const;

private:
    QString capitalizeString(const QString& str);

    QString firstName;
    QString secondName;
    QString middleName;

    QDate birthDate;
    QDate enrollmentDate;
    QDate graduationDate;

    static const QString DATE_FORMAT;
};
