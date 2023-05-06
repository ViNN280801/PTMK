#ifndef MAIN_HANDLER_HPP
#define MAIN_HANDLER_HPP

#include <iostream>
#include <cstring>
#include <fstream>

#include "db_manip.hpp"
#include "person.hpp"

#define PRINT_USAGE_MSG                                                                                                        \
    std::cout << "Usage: " << argv[0] << " [1|2 [Surname Name Patronymic Date_of_birth Sex]|3|4|5]\nView all options below:\n" \
              << "1. Creating table with data of persons: " << argv[0] << " 1\n"                                               \
              << "2. Write record to the database: " << argv[0] << " 2 Surname Name Patronymic Date_of_birth Sex\n"            \
              << "3. Print all unique SNP{*}+DoB{**}: " << argv[0] << " 3\n"                                                   \
              << "4. Generate 1.000.000 random persons and write them to database: " << argv[0] << " 4\n"                      \
              << "5. Print all records with: Sex = M; SNP starts with \'F\': " << argv[0] << " 5\n"                            \
              << "{*} SNP - surname, name and patronymic\n"                                                                    \
              << "{**} DoB - date of birth (format: yyyy-mm-dd)" << std::endl;

#define PRINT_MODE_2_ERROR_MSG_AND_EXIT                                                  \
    std::cout << "Error: Mode 2 requires [Surname Name Patronymic Date_of_birth Sex]\n"; \
    exit(EXIT_FAILURE);

#define PRINT_ERROR_MSG_AND_EXIT                                                                                   \
    {                                                                                                              \
        std::string unknownCommand;                                                                                \
        for (int i = 0; i < argc; i++)                                                                             \
            unknownCommand += argv[i] + std::string(" ");                                                          \
        std::cout << "Error: Command: \"" << unknownCommand << "\" is unknown command\n"                           \
                  << "Run " << argv[0] << " with any of help agruments: \"--h\"; \"-h\"; \"--help\"; \"-help\"\n"; \
        exit(EXIT_FAILURE);                                                                                        \
    }

/// @brief Checks if 2nd passed argument is helper flag
/// @param argv main arguments
/// @return "true" if 2nd passed argument is helper flag
constexpr bool isHelpMode(char **argv)
{
    return strcmp(argv[1], "-h") == 0 || strcmp(argv[1], "--h") == 0 ||
           strcmp(argv[1], "-help") == 0 || strcmp(argv[1], "--help") == 0;
}

/// @brief Checks if file with passed filename exists
/// @param filename name of file to do existance check
/// @return "true" if file exists, otherwise - "false"
bool exists(std::string const &filename)
{
    std::ifstream ifs(filename.c_str());
    return ifs.good();
}

std::string enterToDB()
{
    std::string dbname;
    std::cout << "Enter name of DB: ";
    std::getline(std::cin, dbname, '\n');

    if (!exists(dbname))
    {
        std::cerr << "Error: exists(): File with name " << dbname
                  << " not exists. Can't write to it. Exiting with status \'-1\'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return dbname;
}

void handleMain(int argc, char **argv)
{
    switch (argc)
    {
    case 2:
    {
        if (strcmp(argv[1], "1") == 0)
        {
            std::string dbname;
            std::cout << "Enter name of DB: ";
            std::getline(std::cin, dbname, '\n');

            DBmanip db(dbname);
            db.createPersonTable();
            std::cout << "Database with name \"" << dbname << "\" successfully created\n";
        }
        else if (strcmp(argv[1], "3") == 0)
        {
            DBmanip db(enterToDB());
            db.printUniqueSNPandDoB();
        }
        else if (strcmp(argv[1], "4") == 0)
        {
            DBmanip db(enterToDB());
            db.fillPersonTable(10'000);
            db.fillPersonTableWithMalesWithSurnameStartsWithF();
        }
        else if (strcmp(argv[1], "5") == 0)
        {
            DBmanip db(enterToDB());
            db.printMalePersonWithSurnameFstLetterF();
        }
        else if (strcmp(argv[1], "6") == 0)
        {
            DBmanip db(enterToDB());
            db.printMalePersonWithSurnameFstLetterF_quick();
        }
        else if (isHelpMode(argv))
            PRINT_USAGE_MSG
        else
            PRINT_ERROR_MSG_AND_EXIT
        break;
    }
    case 7:
    {
        if (strcmp(argv[1], "2") == 0)
        {
            if (strlen(argv[6]) > 1)
            {
                std::cerr << "Error: Sex can contains only 1 char: M or F. Exiting with status \'-1\'" << std::endl;
                exit(EXIT_FAILURE);
            }

            Person p;
            p.setSurname(argv[2]);
            p.setName(argv[3]);
            p.setPatronymic(argv[4]);
            p.setDateOfBirth(argv[5]);
            p.setSex(*argv[6]);

            DBmanip db(enterToDB());
            db.insertPersonToTable(p);
        }
        break;
    }
    default:
        PRINT_ERROR_MSG_AND_EXIT
    }
}

#endif // MAIN_HANDLER_HPP
