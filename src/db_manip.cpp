#include <iostream>
#include <iomanip>
#include <cstring>

#include "../include/db_manip.hpp"

void DBmanip::printExecutionTime(const std::chrono::high_resolution_clock::time_point &start)
{
    auto end{std::chrono::high_resolution_clock::now()};
    auto diff{end - start};
    std::cout << "Execution time: " << std::chrono::duration<double, std::milli>{diff}.count()
              << "ms" << std::endl;
}

DBmanip::DBmanip(const std::string &dbname)
{
    // Openning connection
    if (sqlite3_open(dbname.c_str(), &m_db_handler))
    {
        std::cerr << "Error: DBmanip::DBmanip(const std::string &dbname): Can't open database with name "
                  << dbname << '\n'
                  << sqlite3_errmsg(m_db_handler);
    }
}

DBmanip::~DBmanip()
{
    // Closing connection with database
    sqlite3_close(m_db_handler);
}

std::string DBmanip::getDBName() const { return m_dbname; }

void DBmanip::setDBName(const std::string &dbname) { m_dbname = dbname; }

void DBmanip::setSqlQuery(const std::string &query) { m_query = query; }

void DBmanip::execSqlQuery()
{
    char *err = nullptr;
    // Checking if execution of query is OK
    if (sqlite3_exec(m_db_handler, m_query.c_str(), 0, 0, &err) != SQLITE_OK)
    {
        std::cerr << "Error: execSqlQuery(): Can't execute query:\n"
                  << m_query << '\n'
                  << err << "\n\n";

        // Deallocating memory for 'err' ptr if it not points on nullptr
        if (err != nullptr)
            sqlite3_free(err);
    }
}

void DBmanip::execSqlQuery(sqlite3 *dbHandler, const char *sql,
                           int (*callback)(void *, int, char **, char **), void *obj, char **errmsg)
{
    if (sqlite3_exec(dbHandler, sql, callback, static_cast<void *>(&obj), errmsg) != SQLITE_OK)
    {
        std::cerr << "Error: execSqlQuery(): Can't execute query:\n"
                  << sql << '\n'
                  << errmsg << "\n\n";
    }
}

void DBmanip::createPersonTable()
{
    m_query = "CREATE TABLE IF NOT EXISTS Person(ID INTEGER PRIMARY KEY AUTOINCREMENT, " +
              std::string("Surname TEXT NOT NULL, ") +
              std::string("Name TEXT NOT NULL, ") +
              std::string("Patronymic TEXT NOT NULL, ") +
              std::string("Date_of_Birth DATE NOT NULL, ") +
              std::string("Sex CHAR NOT NULL)");
    execSqlQuery();
}

int printPersonsFromDB([[maybe_unused]] void *pObj, int columns, char **values, [[maybe_unused]] char **headers)
{
    // If table contents incorrect count of columns -> return fail status
    /* if (columns != 6)
        return SQLITE_FAIL; */

    for (int i{}; i < columns; i++)
        std::cout << values[i] << std::setw(16 - strlen(values[i])) << std::setfill(' ') << '\t';
    std::endl(std::cout);
    return SQLITE_OK;
}

void DBmanip::printPersonTable()
{
    m_query = "SELECT * FROM Person";
    char *err = nullptr;
    execSqlQuery(m_db_handler, m_query.c_str(), &printPersonsFromDB, 0, &err);
    if (err != nullptr)
        sqlite3_free(err);
}

void DBmanip::printUniqueSNPandDoB()
{
    m_query = "SELECT DISTINCT Surname, Name, Patronymic, Date_of_Birth, " +
              std::string("strftime(\"%Y\", 'now') - strftime(\"%Y\", Date_of_Birth) AS Age ") +
              std::string("FROM Person ") +
              std::string("ORDER BY Surname, Name, Patronymic DESC");
    char *err = nullptr;
    execSqlQuery(m_db_handler, m_query.c_str(), &printPersonsFromDB, 0, &err);
    if (err != nullptr)
        sqlite3_free(err);
}

void DBmanip::printMalePersonWithSurnameFstLetterF()
{
    m_query = "SELECT * FROM (SELECT * " +
              std::string("FROM Person ") +
              std::string("WHERE substr(Surname, 1, 1) == 'F' ") +
              std::string("ORDER BY Sex DESC) ") +
              std::string("WHERE Sex != 'F'");
    char *err = nullptr;
    std::chrono::high_resolution_clock::time_point start{std::chrono::high_resolution_clock::now()};
    execSqlQuery(m_db_handler, m_query.c_str(), &printPersonsFromDB, 0, &err);
    printExecutionTime(start);
    if (err != nullptr)
        sqlite3_free(err);
}

void DBmanip::printMalePersonWithSurnameFstLetterF_quick()
{
    m_query = "SELECT ID, Surname, Name, Patronymic, Date_of_Birth, Sex " +
              std::string("FROM Person WHERE Sex == 'M' AND substr(Surname, 1, 1) == 'F'");
    char *err = nullptr;
    std::chrono::high_resolution_clock::time_point start{std::chrono::high_resolution_clock::now()};
    execSqlQuery(m_db_handler, m_query.c_str(), &printPersonsFromDB, 0, &err);
    printExecutionTime(start);
    if (err != nullptr)
        sqlite3_free(err);
}

void DBmanip::insertPersonToTable(const Person &p)
{
    m_query = "INSERT INTO Person(Surname, Name, Patronymic, Date_of_Birth, Sex) VALUES(\'" + p.getSurname() + "\', \'" + p.getName() + "\', \'" +
              p.getPatronymic() + "\', \'" + p.getDateOfBirth() + "\', \'" + p.getSex() + "\')";
    execSqlQuery();
    std::cout << "Recording person: "
              << p.getSurname() << ' ' << p.getName() << ' ' << p.getPatronymic()
              << " -> \033[1;32mSUCCESS\033[0m\033[1m\n";
}

void DBmanip::fillPersonTable(int recordsCount)
{
    Person p;
    for (int i{}; i < recordsCount; i++)
    {
        std::cout << i << ": generateRandomPerson(): ";
        p.generateRandomPerson();
        insertPersonToTable(p);
    }
}

void DBmanip::fillPersonTableWithMalesWithSurnameStartsWithF(int recordsCount)
{
    Person p;
    for (int i{}; i < recordsCount; i++)
    {
        std::cout << i << ": generateRandomMaleWithSurnameStartsWithF(): ";
        p.generateRandomMaleWithSurnameStartsWithF();
        insertPersonToTable(p);
    }
}

void DBmanip::clearPersonTable()
{
    m_query = "DELETE FROM Person";
    execSqlQuery();
}

void DBmanip::removePersonTable()
{
    m_query = "DROP TABLE IF EXISTS Person";
    execSqlQuery();
}
