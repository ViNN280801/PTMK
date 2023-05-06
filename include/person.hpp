#ifndef PERSON_HPP
#define PERSON_HPP

#include <string>

// Class that describes person with surname, name and patronymics
class Person
{
private:
    std::string m_surname;    // Person's surname
    std::string m_name;       // Person's name
    std::string m_patronymic; // Person's patronymics
    std::string m_dob;        // Person's date of birth in format: "%YYYY-%mm-%dd"
    char m_sex;               // Person's sex: M - male; F - female

protected:
    /// @brief Helper method to zero out all data members
    /// @param p person object to do zero out
    void clear(Person &p);

    /// @brief Helper method to copy all data members from 'p' to current object
    /// @param p new person's date represented as object of Person class
    void copy(const Person &p);

    /// @brief Generates surname, name or patronymics (not matters what exactly)
    /// @return Surname, name or patronymics filled with random english letters
    std::string generateRandomSNP() const;

public:
    /// @brief Default ctor
    explicit Person();

    /// @brief Ctor with all params
    explicit Person(const std::string &, const std::string &, const std::string &, const std::string &, char);

    /// @brief Copy ctor
    explicit Person(const Person &);

    /// @brief Move ctor
    explicit Person(Person &&);

    /// @brief Copy assignment operator
    Person &operator=(const Person &);

    /// @brief Move assignment operator
    Person &operator=(Person &&) noexcept;

    /// @brief Dtor
    virtual ~Person();

    /// @brief Getter for person's surname
    /// @return Person's surname
    constexpr std::string getSurname() const { return m_surname; }

    /// @brief Getter for person's name
    /// @return Person's name
    constexpr std::string getName() const { return m_name; }

    /// @brief Getter for person's patronymic
    /// @return Person's patronymic
    constexpr std::string getPatronymic() const { return m_patronymic; }

    /// @brief Getter for person's date of birth
    /// @return Person's date of birth in format "%YYYY-%mm-%dd"
    constexpr std::string getDateOfBirth() const { return m_dob; }

    /// @brief Getter for person's sex
    /// @return Person's sex: M - male; F - female
    constexpr char getSex() const { return m_sex; }

    /// @brief Setter for person's surname
    /// @param surname new person's surname
    void setSurname(const std::string &surname);

    /// @brief Setter for person's name
    /// @param name new person's name
    void setName(const std::string &name);

    /// @brief Setter for person's patronymic
    /// @param patronymic new person's patronymic
    void setPatronymic(const std::string &patronymic);

    /// @brief Setter for person's date of birth
    /// @param dob new person's date of birth
    void setDateOfBirth(const std::string &dob);

    /// @brief Setter for person's sex
    /// @param sex new person's sex: M - male; F - female
    void setSex(char sex);

    /// @brief Checks if surname, name or patronymics is valid
    /// @param s represents surname, name or patronymics
    /// @return "true" if 's' is valid string
    bool isSurnameNameOrPatronymicValid(const std::string &s) const;

    /// @brief Checks if date of birth represented as a string is valid
    /// @param s represents date of birth
    /// @return "true" if 's' is valid string
    bool isDateOfBirthValid(const std::string &s) const;

    /// @brief Generates surname and assigns it to surname of current person
    void generateRandomSurname();

    /// @brief Generates name and assigns it to name of current person
    void generateRandomName();

    /// @brief Generates patronymic and assigns it to patronymic of current person
    void generateRandomPatronymic();

    /// @brief Generates random date of birth with age in interval [18; 100] (by default)
    /// and assigns it to current date of birth of a person
    /// @param lowestAge lowest age of a person - by default is 18
    /// @param highestAge highest age of a person - by default is 100
    void generateRandomDateOfBirth(int lowestAge = 18, int highestAge = 100);

    /// @brief Generates random sex of a person
    /// and assigns it to current sex of a person
    /// @return Sex of a person represented as a char: M - male; F - female
    void generateRandomSex();

    /// @brief Generates random data of a person
    /// @return Random data about a person
    void generateRandomPerson();

    /// @brief Generates random data of a person, but exactly we know
    /// that this person is a male and his surname starts with 'F' letter
    /// @return Random data about a person
    void generateRandomMaleWithSurnameStartsWithF();

    /// @brief Prints person's data to terminal
    void printPersonInfo() const;
};

#endif // PERSON_HPP