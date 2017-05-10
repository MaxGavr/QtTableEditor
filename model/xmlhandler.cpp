#include "xmlhandler.h"
#include "database.h"

const QString XmlHandler::XML_TAG_STUDENT = "student";
const QString XmlHandler::XML_TAG_NAME = "name";
const QString XmlHandler::XML_TAG_SURNAME = "surname";
const QString XmlHandler::XML_TAG_MIDDLE_NAME = "middleName";
const QString XmlHandler::XML_TAG_DATES = "dates";
const QString XmlHandler::XML_TAG_BIRTH_DATE = "birth";
const QString XmlHandler::XML_TAG_ENROLL_DATE = "enrollment";
const QString XmlHandler::XML_TAG_GRADUATE_DATE = "graduation";


XmlHandler::XmlHandler(StudentDatabase *db)
{
    database = db;
}


bool XmlHandler::readFromFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QXmlStreamReader stream(&file);

    Student student;
    while (!stream.atEnd() && !stream.hasError())
    {
        QXmlStreamReader::TokenType token = stream.readNext();
        if (token == QXmlStreamReader::StartElement)
        {

            if (stream.name() == XML_TAG_STUDENT)
                continue;
            else if (stream.name() == XML_TAG_NAME)
                student.setFirstName(stream.readElementText());
            else if (stream.name() == XML_TAG_SURNAME)
                student.setSecondName(stream.readElementText());
            else if (stream.name() == XML_TAG_MIDDLE_NAME)
                student.setMiddleName(stream.readElementText());
            else if (stream.name() == XML_TAG_BIRTH_DATE)
                student.setBirthDate(parseData(stream.readElementText()));
            else if (stream.name() == XML_TAG_ENROLL_DATE)
                student.setEnrollmentDate(parseData(stream.readElementText()));
            else if (stream.name() == XML_TAG_GRADUATE_DATE)
                student.setGraduationDate(parseData(stream.readElementText()));
        }
        if (token == QXmlStreamReader::EndElement)
            if (stream.name() == XML_TAG_STUDENT)
                database->addStudent(student);
    }
    file.close();
    return true;
}

QDate XmlHandler::parseData(const QString &stringData)
{
    QStringList list = stringData.split(".");
    return QDate(list[2].toInt(), list[1].toInt(), list[0].toInt());
}
