#include "searchpattern.h"

StudentSearchPattern::StudentSearchPattern()
{
    criteria = QVector<bool>(NUMBER_OF_CRITERIA, false);
    comparators = QVector<Comparator>(NUMBER_OF_CRITERIA);

    comparators[Student::KEYS::FIRST_NAME] = [this](QString name){
        return name == this->firstName;
    };
    comparators[Student::KEYS::SECOND_NAME] = [this](QString name){
        return name == this->secondName;
    };
    comparators[Student::KEYS::MIDDLE_NAME] = [this](QString name){
        return name == this->middleName;
    };

    comparators[Student::KEYS::BIRTH_DATE] = [this](QString dateString){
        QDate date = QDate::fromString(dateString, Student::DATE_FORMAT);
        return (date >= birthDateLowerBound) && (date <= birthDateHigherBound);
    };
    comparators[Student::KEYS::ENROLL_DATE] = [this](QString dateString){
        QDate date = QDate::fromString(dateString, Student::DATE_FORMAT);
        return (date >= enrollDateLowerBound) && (date <= enrollDateHigherBound);
    };
    comparators[Student::KEYS::GRADUATE_DATE] = [this](QString dateString){
        QDate date = QDate::fromString(dateString, Student::DATE_FORMAT);
        return (date >= graduateDateLowerBound) && (date <= graduateDateHigherBound);
    };
}

bool StudentSearchPattern::operator()(Student::const_ref student)
{
    for (int i = Student::KEYS::FIRST_NAME; i != Student::KEYS::GRADUATE_DATE; ++i)
    {
        Student::KEYS key = static_cast<Student::KEYS>(i);
        if (!comparators[key](student.getByKey(key)))
            return false;
    }
    return true;
}

void StudentSearchPattern::setFirstName(const QString &value)
{
    firstName = value;
    criteria[Student::KEYS::FIRST_NAME] = true;
}

void StudentSearchPattern::setSecondName(const QString &value)
{
    secondName = value;
    criteria[Student::KEYS::SECOND_NAME] = true;
}

void StudentSearchPattern::setMiddleName(const QString &value)
{
    middleName = value;
    criteria[Student::KEYS::MIDDLE_NAME] = true;
}

void StudentSearchPattern::setBirthDateBounds(const QDate &lower, const QDate &higher)
{
    birthDateLowerBound = lower;
    birthDateHigherBound = higher;
    criteria[Student::KEYS::BIRTH_DATE] = true;
}

void StudentSearchPattern::setEnrollDateBounds(const QDate &lower, const QDate &higher)
{
    enrollDateLowerBound = lower;
    enrollDateHigherBound = higher;
    criteria[Student::KEYS::ENROLL_DATE] = true;
}

void StudentSearchPattern::setGraduateDateBounds(const QDate &lower, const QDate &higher)
{
    graduateDateLowerBound = lower;
    graduateDateHigherBound = higher;
    criteria[Student::KEYS::GRADUATE_DATE] = true;
}

