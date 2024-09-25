#pragma once

#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

#include "operation_strategy.h"
#include "operation_context.h"

class CSVReader_TEST_CLASS
{
public:
    void DoOperationOnTwoColumns(char operand. const std::string& col1, const std::string& col2)
    {
        std::unordered_map<std::string, std::vector<int>> data = ReadFile(filename);
        ColumnOperationContext context;

        // Check if the columns exist
        if (data.find(col1) == data.end() || data.find(col2) == data.end())
        {
            std::cout << "Error: One or both columns do not exist.\n";
            return;
        }

        // Set the correct strategy based on user input
        switch (operation)
        {
            case '+':
                context.SetStrategy(std::make_unique<AdditionStrategy>());
                break;
            case '-':
                context.SetStrategy(std::make_unique<SubtractionStrategy>());
                break;
            case '*':
                context.SetStrategy(std::make_unique<MultiplicationStrategy>());
                break;
            case '/':
                context.SetStrategy(std::make_unique<DivisionStrategy>());
                break;
            default:
                std::cout << "Error: Unsupported operation.\n";
                return;
        }

        std::vector<int> result = context.executeStrategy(data[col1], data[col2]);

        // Display the result
        if (!result.empty())
        {
            std::cout << "Result:\n";
            for (const int &val : result)
            {
                std::cout << val << "\n";
            }
            std::cout << std::endl;
        }
    }

private:
    // Trim white spaces if needed.
    std::string TrimWhiteSpace(const std::string &str)
    {
        size_t first = str.find_first_not_of(' ');
        size_t last = str.find_last_not_of(' ');
        return str.substr(first, (last - first + 1));
    }

    // Function to remove the BOM (Byte Order Mark) from the beginning of a std::string if present.
    inline std::string RemoveBOM(const std::string &str)
    {
        const char* bom = "\xEF\xBB\xBF";  // UTF-8 BOM
        if (str.compare(0, 3, bom) == 0) {
            return str.substr(3);  // Remove BOM
        }
        return str;
    }

    // Function to read the CSV file and store the columns in an std::unordered_map
    std::unordered_map<std::string, std::vector<int>> ReadFile(const std::string &filename)
    {
        std::unordered_map<std::string, std::vector<int>> data;
        std::ifstream file(filename);
        std::string currentLine, colName;

        // get the column names
        std::getline(file, currentLine);
        currentLine = RemoveBOM(currentLine); // Remove byte order marker
        std::stringstream ss(currentLine);
        std::vector<std::string> colNames;

        while (std::getline(ss, colName, ','))
        {
            colNames.push_back(colName);
            data[colName] = {};
        }

        // Read the rest of the file (values)
        while (std::getline(file, currentLine))
        {
            std::stringstream ss(currentLine);
            std::string value;
            for (int i = 0; i < colNames.size(); i++)
            {
                std::getline(ss, value, ',');
                data[colNames[i]].push_back(stoi(value));
            }
        }

        return data;
    }
};

