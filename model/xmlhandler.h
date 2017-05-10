#pragma once

#include <QString>
#include <QDate>

class StudentDatabase;

class XmlHandler
{
public:
    XmlHandler(StudentDatabase *db);

    bool readFromFile(const QString& fileName);

private:
    QDate parseData(const QString& stringData);

    StudentDatabase *database;

    static const QString XML_TAG_STUDENT;
    static const QString XML_TAG_NAME;
    static const QString XML_TAG_SURNAME;
    static const QString XML_TAG_MIDDLE_NAME;
    static const QString XML_TAG_DATES;
    static const QString XML_TAG_BIRTH_DATE;
    static const QString XML_TAG_ENROLL_DATE;
    static const QString XML_TAG_GRADUATE_DATE;
};
