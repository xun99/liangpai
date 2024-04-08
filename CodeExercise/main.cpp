// #include "CodeExercise.h"
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include <unordered_map>
using namespace std;

struct Trade
{
    long long timeStamp;
    string symbol;
    int quantity;
    int price;
};

bool compareTrades(const Trade &a, const Trade &b)
{
    return a.timeStamp < b.timeStamp;
}

int main(int argc, char *argv[])
{
    // YourCode.Solution(argc, argv);
    // processTrades("./Tests/input_1.csv");

    string filename = "./Tests/input_1.csv";

    ifstream inputFile(filename);

    std::string line;
    // std::vector<Trade> trades;
    std::unordered_map<std::string, std::vector<Trade>> trades;

    // Open the output file stream to write results to a CSV file
    std::ofstream outputFile("output_test.csv");

    while (getline(inputFile, line))
    {
        stringstream ss(line);
        string value;
        vector<std::string> values;
        while (getline(ss, value, ','))
        {
            values.push_back(value);
        }

        // store values into a struct trade
        Trade trade;
        trade.timeStamp = std::stoll(values[0]);
        trade.symbol = values[1];
        trade.quantity = std::stoi(values[2]);
        trade.price = std::stoi(values[3]);

        // add to map
        trades[trade.symbol].push_back(trade);
    }

    // Process trades for each symbol
    for (auto &pair : trades)
    {
        vector<Trade> &trades = pair.second;
        std::sort(trades.begin(), trades.end(), compareTrades);

        long long maxTimeGap = 0;
        int volume = 0;
        long long PriceSum = 0;
        int maxPrice = 0;

        for (int i = 0; i < trades.size(); i++)
        {
            const Trade &currTrade = trades[i];
            const Trade &prevTrade = (i > 0) ? trades[i - 1] : currTrade;

            // Calculate time gap
            long long timeGap = currTrade.timeStamp - prevTrade.timeStamp;
            maxTimeGap = max(maxTimeGap, timeGap);

            // Calculate total volume
            volume += currTrade.quantity;

            // Calculate sum of price*volume
            PriceSum += currTrade.quantity * currTrade.price;

            // Calculate max price
            maxPrice = max(maxPrice, currTrade.price);
        }

        // Calculate weighted average price
        int weightedAveragePrice = volume > 0 ? PriceSum / volume : 0;

        // Output results
        std::cout << "Symbol: " << pair.first << std::endl;
        std::cout << "Maximum time gap: " << maxTimeGap << std::endl;
        std::cout << "Total volume traded: " << volume << std::endl;
        std::cout << "Weighted average price: " << weightedAveragePrice << std::endl;
        std::cout << "Max price: " << maxPrice << std::endl;
        std::cout << std::endl;
        // Write results to the CSV file
        outputFile << pair.first << "," << maxTimeGap << "," << volume << ","
                   << weightedAveragePrice << "," << maxPrice << "\n";
    }
    outputFile.close();
    return 0;
}
