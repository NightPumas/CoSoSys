// Project.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <vector>
#include <string>
#include <filesystem>

namespace fs = std::filesystem;

int main()
{

    std::string pathInput;
    std::string pathOutput;
    std::string pathDirectoryText;
    std::string dictionary_word;
    std::string search_string;
    std::vector<std::string>* dictionary;
    dictionary = new std::vector<std::string>[50000];
    std::vector<std::string>* filePaths;
    filePaths = new std::vector<std::string>[1000];

    ///test size capacity 
    std::cout
        << "Maximum size of a string is " << dictionary_word.max_size() << " ("
        << std::hex << std::showbase << dictionary_word.max_size()
        << "), pointer size: " << std::dec
        << CHAR_BIT * sizeof(void*) << " bits\n";

    std::cout
        << "Maximum size of a vector is " << dictionary->max_size() << " ("
        << std::hex << std::showbase << dictionary->max_size()
        << "), pointer size: " << std::dec
        << CHAR_BIT * sizeof(void*) << " bits\n";
    ///end test size 


    //hard coded for ease
    // pathInput = "";
    std::cout << "Write the path of the file. - " ;
    std::cin >> pathInput;
    
    //open dictionary file
    std::ifstream inputFile(pathInput);

    if (inputFile.is_open())
    {
        std::cout << "Found dictionary file\n";

        while (getline(inputFile, dictionary_word))
        {
            dictionary->push_back(dictionary_word);
        }
    }
    else
    {
        std::cout << "Could not find dictionary file\n";
        return EXIT_FAILURE;
    }


    //open directory pathand find files
    //hard coded for ease
    //pathDirectoryText = "";
    std::cout << "Write the path of the search directory. - ";
    std::cin >> pathDirectoryText;
    
    const fs::path pathToShow{ pathDirectoryText };

    for (const auto& entry : fs::directory_iterator(pathToShow)) {
        const auto filenameStr = entry.path().filename().string();
        if (entry.is_directory()) {
            std::cout << "Found dir:  " << filenameStr << '\n';
           // filePaths->push_back(filenameStr);
        }
        else if (entry.is_regular_file()) {
            std::cout << "Found Search File: " << filenameStr << '\n';
            filePaths->push_back(filenameStr);
        }
        else {
            std::cout << "??    " << filenameStr << '\n';
            //filePaths->push_back(filenameStr);
        }
    }

    //open outfile file for write
    //hard coded for ease
    //pathOutput = "";
    std::cout << "Write the path of the output file. - " ;
    std::cin >> pathOutput;

    //open output file
    std::ofstream outputFile(pathOutput);

    if (outputFile.is_open())
    {
        std::cout << "Output file found" << "\n";
    }
    else
    {
        std::cout << "Output file cannot be found" << "\n";
        return EXIT_FAILURE ;
    }

    for (auto i = filePaths->begin(); i != filePaths->end(); ++i)
    {
        //std::cout << *i << '*' << "\n"; write current file
        std::ifstream search_file(pathDirectoryText + '\\' + *i);

        if (search_file.is_open())
        {
            std::cout << "Searching in file" << *i << "\n";
        }
        else
        {
            std::cout << "File " << *i << " cannot be open" << "\n";
            continue;
        }

        std::string TextTiWriteInOutFile = "File " + *i + " contains : ";

        for (auto j = dictionary->begin(); j != dictionary->end(); ++j) {
            //std::cout << *j << '~' << "\n";

            while (!search_file.eof())
            {
                std::string search_string = "";
                std::getline(search_file, search_string);
                size_t found = search_string.find(*j);
                if (found != std::string::npos) {
                    TextTiWriteInOutFile += *j + " ; ";
                    break;
                }
            }
            search_file.clear();
            search_file.seekg(0);
        }

        //write the results to output file

        outputFile << TextTiWriteInOutFile << std::endl;
    }

    delete [] dictionary;
    delete [] filePaths ;

    return EXIT_SUCCESS;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu
