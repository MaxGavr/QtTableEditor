from lxml import etree
from random import randint, choice
from datetime import date
import sys

amount = 1000
date_format = "%d.%m.%Y"

XML_TAGS = {'name': 'name',
            'surname': 'surname',
            'middle_name': 'middleName',
            'birth_date': 'birth',
            'enroll_date': 'enrollment',
            'graduate_date': 'graduation'}

name_file = "names.txt"
surname_file = "surnames.txt"
middle_names_file = "middle_names.txt"

def load_names():
    file = open(name_file)
    names = []
    for name in file:
        names.append(name.strip())
    file.close()

    file = open(surname_file)
    surnames = []
    for surname in file:
        surnames.append(surname.strip())
    file.close()

    file = open(middle_names_file)
    middle_names = []
    for middle_name in file:
        middle_names.append(middle_name.strip())
    file.close()

    return (names, surnames, middle_names)


def generate_dates():
    year = randint(1950, date.today().year - 18)
    month = randint(1, 12)
    day = randint(1, 28)
    birth_date = date(year, month, day)

    year = randint(birth_date.year + 1, date.today().year)
    month = randint(1, 12)
    day = randint(1, 28)
    enroll_date = date(year, month, day)

    year = randint(enroll_date.year, date.today().year)
    month = randint(1, 12)
    day = randint(1, 28)
    graduate_date = date(year, month, day)

    return [d.strftime(date_format) for d in [birth_date, enroll_date, graduate_date]]

def write_student(root, student):
    student_element = etree.Element('student')
    
    element = etree.Element(XML_TAGS['name'])
    element.text = student[XML_TAGS['name']]
    student_element.append(element)
    element = etree.Element(XML_TAGS['surname'])
    element.text = student[XML_TAGS['surname']]
    student_element.append(element)
    element = etree.Element(XML_TAGS['middle_name'])
    element.text = student[XML_TAGS['middle_name']]
    student_element.append(element)

    dates_element = etree.Element('dates')
    student_element.append(dates_element)

    element = etree.Element(XML_TAGS['birth_date'])
    element.text = student[XML_TAGS['birth_date']]
    dates_element.append(element)
    element = etree.Element(XML_TAGS['enroll_date'])
    element.text = student[XML_TAGS['enroll_date']]
    dates_element.append(element)
    element = etree.Element(XML_TAGS['graduate_date'])
    element.text = student[XML_TAGS['graduate_date']]
    dates_element.append(element)

    root.append(student_element)

amount = int(sys.argv[1])

root = etree.Element('students')

names, surnames, middle_names = load_names()
for i in range(amount):
    student = {}
    student[XML_TAGS['name']] = choice(names)
    student[XML_TAGS['surname']] = choice(surnames)
    student[XML_TAGS['middle_name']] = choice(middle_names)
    student[XML_TAGS['birth_date']], student[XML_TAGS['enroll_date']], student[XML_TAGS['graduate_date']] = generate_dates()

    write_student(root, student)

output_file = open(sys.argv[2], "w")
output_file.write(etree.tostring(root, encoding='utf-8', pretty_print=True).decode("utf-8"))
output_file.close()
