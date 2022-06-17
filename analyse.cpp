// C++ program to demonstrate stock analysis in tech industry
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
using namespace std;

// Date, High, Low, Open, Close, Volume, AdjClose, companyName
struct techStock
{
public:
    // Initialise an empty element of TechStock Data
    techStock()
    {
        High = 0;
        Low = 0;
        Open = 0;
        Close = 0;
        Volume = 0;
        AdjClose = 0;
        Date = "Null";
        CompanyName = "Null";
    }
    // Constructor function to assign values.
    techStock(
        float high,
        float low,
        float open,
        float close,
        float volume,
        float adjClose,
        string date,
        string companyName)
    {
        // insert values
        High = high;
        Low = low;
        Open = open;
        Close = close;
        Volume = volume;
        AdjClose = adjClose;
        Date = date;
        CompanyName = companyName;
    }

    // helper function to access private variables
    string getDate() { return Date; }
    float getHigh() { return High; }
    float getLow() { return Low; }
    float getOpen() { return Open; }
    float getClose() { return Close; }
    float getVolume() { return Volume; }
    float getAdjClose() { return AdjClose; }
    string getCompanyName() { return CompanyName; }

    // helper function to display records
    void display()
    {
        cout << CompanyName << ":" << Date << ":" << High << ":" << Low << ":" << Open << ":" << Close
             << ":" << Volume << ":" << AdjClose << endl;
    }

private:
    float High;
    float Low;
    float Open;
    float Close;
    float Volume;
    float AdjClose;
    string Date;
    string CompanyName;
};

// function initialisation
void removeduplicate(vector<string> &vec);
int findIndex(vector<string> uniqueCompany, string code);
vector<vector<techStock>> sortEntries(vector<techStock> allDatabase, vector<string> uniqueCompany);
void getMarketcap(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get12MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get24MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get50MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get100MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);

int main()
{

    // opening file
    ifstream fil;
    fil.open("./historic.csv");

    // check file is loaded properly
    if (fil.fail())
    {
        cerr << "unable to open file" << endl;
        return 1;
    }

    string line = "";
    vector<techStock> allDatabases;
    vector<string> uniqueCompany;

    while (getline(fil, line))
    {
        stringstream inputString(line);
        vector<string> result;
        while (inputString.good())
        {
            string substring;
            getline(inputString, substring, ',');

            result.push_back(substring);
        }
        float High = float(stoi(result[0]));
        float Low = float(stoi(result[1]));
        float Open = float(stoi(result[2]));
        float Close = float(stoi(result[3]));
        float Volume = float(stoi(result[4]));
        float AdjClose = float(stoi(result[5]));
        string Date = result[6];
        string CompanyName = result[7];

        uniqueCompany.push_back(CompanyName);

        techStock stockdata(High, Low, Open, Close, Volume, AdjClose, Date, CompanyName);

        allDatabases.push_back(stockdata);
    }

    removeduplicate(uniqueCompany);
    vector<vector<techStock>> sortedData = sortEntries(allDatabases, uniqueCompany);
    int choice;
    do
    {
        cout << " What do you want to calculate \n 1-Find Market Cap \n 2-find 12 day moving Average \n 3-Mean time between tick changes \n 4-Median time betwwen tick changes \n 5-Longest time between trade \n 6-Longest time between tick change \n 7-Mean bid ask spread \n 8-Median bid ask spread \n 9-Examples of round number effect \n press 0 to exit \n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            getMarketcap(sortedData, uniqueCompany);
            break;
        case 2:
            get12MovingAvg(sortedData, uniqueCompany);
            break;
            // case 3:
            //     break;
            // case 4:

            //     break;
            // case 5:

            //     break;
            // case 6:

            //     break;
            // case 7:

            //     break;
            // case 8:

            //     break;
            // case 9:

            //     break;
            // case 10:
            //     generateReport(sortedData, uniqueCompany);
        }
    } while (choice != 0);

    fil.close();

    return 0;
}

// Helper function to remove duplicate entries from a vector
void removeduplicate(vector<string> &vec)
{
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());
}
// helper function to return index of companyName in vector
int findIndex(vector<string> uniqueCompany, string code)
{
    for (int i = 0; i < uniqueCompany.size(); i++)
    {
        if (uniqueCompany[i] == code)
        {
            return i;
        }
    }
    return 0;
}

// helper function to arrange stocks into vector
vector<vector<techStock>> sortEntries(vector<techStock> allDatabase, vector<string> uniqueCompany)
{

    techStock EmptyData; // create a dummy value
    vector<vector<techStock>> sortedEntries(uniqueCompany.size(), vector<techStock>(1, EmptyData));
    for (int i = 0; i < allDatabase.size(); i++)
    {
        string code = allDatabase[i].getCompanyName();
        int index = findIndex(uniqueCompany, code);
        techStock data = allDatabase[i];
        if (sortedEntries[i].size() == 1)
        {
            sortedEntries[i].pop_back();
            sortedEntries[index].push_back(data);
        }
        sortedEntries[index].push_back(data);
    }
    return sortedEntries;
}

// helper function to find market cap of stocks
void getMarketcap(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    vector<vector<float>> marketCapStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<float> marketCap;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            marketCap.push_back(allStocks[i][j].getOpen() * allStocks[i][j].getVolume());
        }
        marketCapStack.push_back(marketCap);
    }
}

// -------------------------------- MOVING AVERAGE FUNCTIONS -------------------------------- //

// helper function to get 12 day moving average
void get12MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    int period = 12;
    vector<vector<float>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<float> average;
        int sum = 0;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum += allStocks[i][j].getClose();
                average.push_back(0);
            }
            else
            {
                sum += allStocks[i][j].getClose();
                sum -= allStocks[i][j - period].getClose();
                average.push_back(sum / period);
            }
        }
        movingAverageStack.push_back(average);
    }

    // for (int i = 0; i < movingAverageStack.size(); i++)
    // {
    //     cout << "uniqueCompany:" << uniqueCompany[i] << "12 day moving average" << endl;
    //     for (int j = 0; j < allStocks[i].size(); j++)
    //     {
    //         cout << movingAverageStack[i][j] << ":";
    //     }
    //     cout << endl;
    // }
}
// helper function to get 26 day moving average
void get26MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    int period = 26;
    vector<vector<float>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<float> average;
        int sum = 0;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum += allStocks[i][j].getClose();
                average.push_back(0);
            }
            else
            {
                sum += allStocks[i][j].getClose();
                sum -= allStocks[i][j - period].getClose();
                average.push_back(sum / period);
            }
        }
        movingAverageStack.push_back(average);
    }
}
// helper function to get 50 day moving average
void get50MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    int period = 50;
    vector<vector<float>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<float> average;
        int sum = 0;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum += allStocks[i][j].getClose();
                average.push_back(0);
            }
            else
            {
                sum += allStocks[i][j].getClose();
                sum -= allStocks[i][j - period].getClose();
                average.push_back(sum / period);
            }
        }
        movingAverageStack.push_back(average);
    }
}
// helper function to get 200 day moving average
void get200MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    int period = 200;
    vector<vector<float>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<float> average;
        int sum = 0;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum += allStocks[i][j].getClose();
                average.push_back(0);
            }
            else
            {
                sum += allStocks[i][j].getClose();
                sum -= allStocks[i][j - period].getClose();
                average.push_back(sum / period);
            }
        }
        movingAverageStack.push_back(average);
    }
}