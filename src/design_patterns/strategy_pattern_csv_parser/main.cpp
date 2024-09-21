#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <string>
#include <algorithm>
#include "operation_strategy.h"
#include "operation_context.h"


int main()
{
    std::string filename{};
    std::string col1{};
    std::string col2{};
    char operation;

    std::cout << "Enter the CSV file name: ";
    std::cin >> filename;

    std::unordered_map<std::string, std::vector<int>> data = ReadCSV(filename);
    ColumnOperationContext context;

    while (true)
    {
        std::cout << "Enter first column name (or 'exit' to quit): ";
        std::cin >> col1;

        if (col1 == "exit") break;

        std::cout << "Enter operation (+, -, *, /): ";
        std::cin >> operation;

        std::cout << "Enter second column name: ";
        std::cin >> col2;

        // Check if the columns exist
        if (data.find(col1) == data.end() || data.find(col2) == data.end())
        {
            std::cout << "Error: One or both columns do not exist.\n";
            continue;
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
                continue;
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

    return 0;
}
