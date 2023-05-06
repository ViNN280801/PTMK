#ifndef DB_MANIP_HPP
#define DB_MANIP_HPP

#include <string>
#include <chrono>

#include "sqlite-amalgamation-3071300/sqlite3.h"
#include "../include/person.hpp"

/// @brief Class represents data base manipulator
/// that can interoperate with sqlite3 data base:
/// connecting to db, creating table, adding records,
/// filling random records and others functionality
class DBmanip
{
private:
    sqlite3 *m_db_handler; // Connection to database handler
    std::string m_dbname;  // Name of the database
    std::string m_query;   // SQL query to execute

protected:
    /// @brief Printing duration of executing some code snippet
    /// At first, where do you want to start the timer, you need to write following line:
    /// auto start{std::chrono::high_resolution_clock::now()};
    /// and then in necessary place where you want to calculate
    /// time of your calculations execute this function
    /// @param start calculation starting time
    void printExecutionTime(const std::chrono::high_resolution_clock::time_point &start);

public:
    /// @brief Defaulted ctor
    explicit DBmanip() = default;

    /// @brief Connecting to database with specified name
    /// @param dbname name of database to connect
    explicit DBmanip(const std::string &dbname);

    /// @brief Defaulted copy ctor
    explicit DBmanip(const DBmanip &) = default;

    /// @brief Defaulted move ctor
    explicit DBmanip(DBmanip &&) = default;

    /// @brief Defaulted copy assignment operator
    DBmanip &operator=(const DBmanip &) = default;

    /// @brief Defaulted move assignment operator
    DBmanip &operator=(DBmanip &&) noexcept = default;

    /// @brief Defaulted virtual dtor
    virtual ~DBmanip();

    /// @brief Getter for name of database
    /// @return Name of database of current object
    std::string getDBName() const;

    /// @brief Setter for name of database
    /// @param dbname new name to replace old name of current object
    void setDBName(const std::string &dbname);

    /// @brief Setter for SQL query string
    /// @param query SQL query string
    void setSqlQuery(const std::string &query);

    /// @brief Executes SQL query from current object
    void execSqlQuery();

    /// @brief Executes specified SQL query from current object
    void execSqlQuery(sqlite3 *, const char *sql, int (*callback)(void *, int, char **, char **),
                      void *, char **errmsg);

    /// @brief Creates table with person data and name 'Person'
    void createPersonTable();

    /// @brief Prints all content of a specified table
    void printPersonTable();

    /// @brief Prints all records with unique surname, name, patronymic (SNP) and
    /// date of birth, sorted by SNP
    void printUniqueSNPandDoB();

    /// @brief Prints all records which are satisfy following requirement:
    /// Person have to be a male and his first letter of surname is 'F'
    void printMalePersonWithSurnameFstLetterF();

    /// @brief Do same work as a 'printMalePersonWithSurnameFstLetterF()', but quicklier
    void printMalePersonWithSurnameFstLetterF_quick();

    /// @brief Inserts specified person object to 'Person' table
    /// @param p object of person to insert
    void insertPersonToTable(const Person &p);

    /// @brief Fills 'Person' table with random data
    /// @param recordsCount count of records (by default is 1 mln)
    void fillPersonTable(int recordsCount = 1'000'000);

    /// @brief Fills 'Person' table with male persons with surname starts with 'F'
    /// @param recordsCount count of records (by default is 100)
    void fillPersonTableWithMalesWithSurnameStartsWithF(int recordsCount = 100);

    /// @brief Removes all content of 'Person' table
    void clearPersonTable();

    /// @brief Removes table with 'Person' name
    void removePersonTable();
};

#endif // DB_MANIP_HPP
