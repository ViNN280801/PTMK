#include <iostream>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <chrono>
#include <cctype>
#include <ctime>
#include <cstring>

#include "../include/person.hpp"

void Person::clear(Person &p)
{
    p.m_surname.clear();
    p.m_name.clear();
    p.m_patronymic.clear();
    p.m_dob = "01/01/1970";
    p.m_sex = 'F';
}

void Person::copy(const Person &p)
{
    m_surname = p.m_surname;
    m_name = p.m_name;
    m_patronymic = p.m_patronymic;
    m_dob = p.m_dob;
    m_sex = p.m_sex;
}

std::string Person::generateRandomSNP() const
{
    // Initializing english alphabet and declaring variable of surname, name and patronymics
    std::string engAlphabet("abcdefghijklmnopqrstuvwxyz"), snp;

    // Generating surname, name or patronymics with random length
    for (int i{}; i < (rand() % 15 + 2); i++)
        snp += engAlphabet.at(rand() % engAlphabet.length());

    // Capitalize all first letters
    snp.at(0) = static_cast<unsigned char>(std::toupper(snp.at(0)));
    return snp;
}

Person::Person()
{
    // Using current date as a parameter to generate random number
    srand(time(nullptr));
    clear(*this);
}

Person::Person(const std::string &surname, const std::string &name, const std::string &patronymics,
               const std::string &dob, char sex) : m_surname(surname), m_name(name),
                                                   m_patronymic(patronymics), m_dob(dob),
                                                   m_sex(sex) {}

Person::Person(const Person &p) { copy(p); }

Person::Person(Person &&p) { *this = std::move(p); }

Person &Person::operator=(const Person &p)
{
    if (this == &p)
        return *this;
    copy(p);
    return *this;
}

Person &Person::operator=(Person &&p) noexcept
{
    if (this == &p)
        return *this;
    *this = std::move(p);
    return *this;
}

Person::~Person() { clear(*this); }

void Person::setSurname(const std::string &surname)
{
    // Check of string validity before assign 'surname' to surname of current object
    if (isSurnameNameOrPatronymicValid(surname))
        m_surname = surname;
    else
        std::cerr << "Warning: setSurname(): No changes have been made\n";
}

void Person::setName(const std::string &name)
{
    if (isSurnameNameOrPatronymicValid(name))
        m_name = name;
    else
        std::cerr << "Warning: setName(): No changes have been made\n";
}

void Person::setPatronymic(const std::string &patronymic)
{
    if (isSurnameNameOrPatronymicValid(patronymic))
        m_patronymic = patronymic;
    else
        std::cerr << "Warning: setPatronymic(): No changes have been made\n";
}

void Person::setDateOfBirth(const std::string &dob)
{
    if (isDateOfBirthValid(dob))
        m_dob = dob;
    else
        std::cerr << "Warning: setDateOfBirth(): No changes have been made\n";
}

void Person::setSex(char sex)
{
    if (sex != 'M' && sex != 'F')
    {
        std::cerr << "Warning: setSex(): No changes have been made\n";
        return;
    }
    m_sex = sex;
}

bool Person::isSurnameNameOrPatronymicValid(const std::string &s) const
{
    // Surname, name or patronymics can't contains punctuation symbols, special symbols or digits
    // and all of first letters have to be in uppercase
    return std::ranges::none_of(s, [](const auto &ch)
                                { return std::ispunct(ch) || std::isdigit(ch); }) &&
           std::isupper(*std::cbegin(s)) &&
           std::isupper(s.at(s.find_first_of(' ') + 1)) &&
           std::isupper(s.at(s.find_last_of(' ') + 1));
}

bool Person::isDateOfBirthValid(const std::string &s) const
{
    struct std::tm tm_;
    return (!strptime(s.c_str(), "%YYYY-%mm-%dd", &tm_));
}

void Person::generateRandomSurname() { m_surname = generateRandomSNP(); }

void Person::generateRandomName() { m_name = generateRandomSNP(); }

void Person::generateRandomPatronymic() { m_patronymic = generateRandomSNP(); }

void Person::generateRandomDateOfBirth(int lowestAge, int highestAge)
{
    std::chrono::system_clock::time_point tp(std::chrono::system_clock::now());
    std::time_t tt{std::chrono::system_clock::to_time_t(tp)};
    struct std::tm tm_;
    int currentYear{(*std::localtime(&tt)).tm_year + 1900}, randomAge{};
    tm_.tm_mday = rand() % 31 + 1;
    tm_.tm_mon = rand() % 12 + 1;
    while (randomAge < lowestAge || randomAge > highestAge)
        randomAge = rand() % highestAge + lowestAge;
    tm_.tm_year = currentYear - randomAge;

    // Adding zeros if day or month contains 1 digit
    // To avoid problems with format
    std::string day(std::to_string(tm_.tm_mday)), month(std::to_string(tm_.tm_mon));
    if (day.length() == 1)
        day.insert(day.cbegin(), '0');
    if (month.length() == 1)
        month.insert(month.cbegin(), '0');

    m_dob = std::to_string(tm_.tm_year) + '-' + month + '-' + day;
}

void Person::generateRandomSex()
{
    std::string sex("MF");
    m_sex = sex.at(rand() % 2);
}

void Person::generateRandomPerson()
{
    generateRandomSurname();
    generateRandomName();
    generateRandomPatronymic();
    generateRandomDateOfBirth();
    generateRandomSex();
}

void Person::generateRandomMaleWithSurnameStartsWithF()
{
    generateRandomSurname();
    m_surname.at(0) = 'F';
    generateRandomName();
    generateRandomPatronymic();
    generateRandomDateOfBirth();
    m_sex = 'M';
}

void Person::printPersonInfo() const
{
    std::cout << "Surname: " << m_surname
              << "\nName: " << m_name
              << "\nPatronymic: " << m_patronymic
              << "\nDate of birth: " << m_dob
              << "\nSex: " << m_sex << "\n\n";
}
