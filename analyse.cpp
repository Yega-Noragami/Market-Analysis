// C++ program to demonstrate stock analysis in tech industry
#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
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
        double high,
        double low,
        double open,
        double close,
        double volume,
        double adjClose,
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
    double getHigh() { return High; }
    double getLow() { return Low; }
    double getOpen() { return Open; }
    double getClose() { return Close; }
    double getVolume() { return Volume; }
    double getAdjClose() { return AdjClose; }
    string getCompanyName() { return CompanyName; }

    // helper function to display records
    void display()
    {
        cout << CompanyName << ":" << Date << ":" << High << ":" << Low << ":" << Open << ":" << Close
             << ":" << Volume << ":" << AdjClose << endl;
    }

private:
    double High;
    double Low;
    double Open;
    double Close;
    double Volume;
    double AdjClose;
    string Date;
    string CompanyName;
};

// function initialisation
void removeduplicate(vector<string> &vec);
int findIndex(vector<string> uniqueCompany, string code);
vector<vector<techStock>> sortEntries(vector<techStock> allDatabase, vector<string> uniqueCompany);
void getMarketcap(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get12MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get26MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get50MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get200MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void getMarketVolatilityByMonth(vector<vector<techStock>> allStocks, vector<string> uniqueCompany); //-------------------- TO_DO ------------------//
void getMarketVolatilityByYear(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);  // -------------------- TO_DO ---------------- //
void get12ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get24ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get50ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get200ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void getWeeklyRSI(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);

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
        double High = double(stold(result[0]));
        double Low = double(stold(result[1]));
        double Open = double(stold(result[2]));
        double Close = double(stold(result[3]));
        double Volume = double(stold(result[4]));
        double AdjClose = double(stold(result[5]));
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
        cout << " What do you want to calculate \n 1-Find Market Cap \n 2-find 12 day moving Average \n 3-Get Market Volatility \n 4-Get 12 Day Exponential Moving Average \n 5-Get Weekly RSI index \n 6-Longest time between tick change \n 7-Mean bid ask spread \n 8-Median bid ask spread \n 9-Examples of round number effect \n press 0 to exit \n";
        cin >> choice;
        switch (choice)
        {
        case 1:
            getMarketcap(sortedData, uniqueCompany);
            break;
        case 2:
            get12MovingAvg(sortedData, uniqueCompany);
            break;
        case 3:
            getMarketVolatilityByMonth(sortedData, uniqueCompany);
            break;
        case 4:
            get12ExponentialMovingAvg(sortedData, uniqueCompany);
            break;
        case 5:
            getWeeklyRSI(sortedData, uniqueCompany);
            break;
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
    vector<vector<double>> marketCapStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<double> marketCap;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            marketCap.push_back(allStocks[i][j].getOpen() * allStocks[i][j].getVolume());
        }
        marketCapStack.push_back(marketCap);
    }
}

// -------------------------------- MOVING AVERAGE FUNCTIONS -------------------------------- //

// helper function to get 12 day moving average
vector<vector<double>> get12MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    int period = 12;
    vector<vector<double>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<double> average;
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

    return movingAverageStack;
}
// helper function to get 26 day moving average
vector<vector<double>> get26MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    int period = 26;
    vector<vector<double>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<double> average;
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
    return movingAverageStack;
}
// helper function to get 50 day moving average
vector<vector<double>> get50MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    int period = 50;
    vector<vector<double>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<double> average;
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
    return movingAverageStack;
}
// helper function to get 200 day moving average
vector<vector<double>> get200MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{

    int period = 200;
    vector<vector<double>> movingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<double> average;
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
    return movingAverageStack;
}

// -------------------------------- EXPONENTIAL MOVING AVERAGE FUNCTIONS -------------------------------- //

// helper function to get 12 day exponential moving average
void get12ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    vector<vector<double>> movingAverageStack = get12MovingAvg(allStocks, uniqueCompany);
    int period = 12;
    const int smoothingConst = 2;
    vector<vector<double>> exponentialMovingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        cout << "CompanyName:" << allStocks[i][0].getCompanyName() << endl;
        vector<double> expontialavg;
        double EMA = 0, prevEMA = movingAverageStack[i][period + 1];
        // cout << "ExponentialMovingAverage:" << prevEMA << endl;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                expontialavg.push_back(0);
            }
            else
            {
                double tempsmoothing = (2.0 / (1 + period));
                EMA = (allStocks[i][j].getClose() - prevEMA) * tempsmoothing + prevEMA;
                prevEMA = EMA;
            }
        }
        exponentialMovingAverageStack.push_back(expontialavg);
    }
}
// helper function to get 26 day exponential moving averagevoid
void get26ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    vector<vector<double>> movingAverageStack = get26MovingAvg(allStocks, uniqueCompany);
    int period = 26;
    const int smoothingConst = 2;
    vector<vector<double>> exponentialMovingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        cout << "CompanyName:" << allStocks[i][0].getCompanyName() << endl;
        vector<double> expontialavg;
        double EMA = 0, prevEMA = movingAverageStack[i][period + 1];
        // cout << "ExponentialMovingAverage:" << prevEMA << endl;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                expontialavg.push_back(0);
            }
            else
            {
                double tempsmoothing = (2.0 / (1 + period));
                EMA = (allStocks[i][j].getClose() - prevEMA) * tempsmoothing + prevEMA;
                prevEMA = EMA;
            }
        }
        exponentialMovingAverageStack.push_back(expontialavg);
    }
}
// helper function to get 50 day exponential moving averagevoid
void get50ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    vector<vector<double>> movingAverageStack = get50MovingAvg(allStocks, uniqueCompany);
    int period = 50;
    const int smoothingConst = 2;
    vector<vector<double>> exponentialMovingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        cout << "CompanyName:" << allStocks[i][0].getCompanyName() << endl;
        vector<double> expontialavg;
        double EMA = 0, prevEMA = movingAverageStack[i][period + 1];
        // cout << "ExponentialMovingAverage:" << prevEMA << endl;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                expontialavg.push_back(0);
            }
            else
            {
                double tempsmoothing = (2.0 / (1 + period));
                EMA = (allStocks[i][j].getClose() - prevEMA) * tempsmoothing + prevEMA;
                prevEMA = EMA;
            }
        }
        exponentialMovingAverageStack.push_back(expontialavg);
    }
}
// helper function to get 200 day exponential moving averagevoid
void get200ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    vector<vector<double>> movingAverageStack = get200MovingAvg(allStocks, uniqueCompany);
    int period = 200;
    const int smoothingConst = 2;
    vector<vector<double>> exponentialMovingAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        cout << "CompanyName:" << allStocks[i][0].getCompanyName() << endl;
        vector<double> expontialavg;
        double EMA = 0, prevEMA = movingAverageStack[i][period + 1];
        // cout << "ExponentialMovingAverage:" << prevEMA << endl;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                expontialavg.push_back(0);
            }
            else
            {
                double tempsmoothing = (2.0 / (1 + period));
                EMA = (allStocks[i][j].getClose() - prevEMA) * tempsmoothing + prevEMA;
                prevEMA = EMA;
            }
        }
        exponentialMovingAverageStack.push_back(expontialavg);
    }
}

// -------------------------------- RELATIVE STRENGTH INDEX  -------------------------------- //

// helper function to calculate RSI for weekly data
void getWeeklyRSI(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    const int period = 7;

    vector<vector<double>> WeeklyRSIAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        cout << "CompanyName" << allStocks[i][0].getCompanyName() << endl;
        vector<double> RSIweekly;
        double RSIndex, RSI;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            double averagegain;
            double averageloss;
            if (RSIweekly.empty())
            {
                vector<double> gain;
                vector<double> loss;
                for (int k = j; k < j + period; k++)
                {

                    double price = allStocks[i][k + 1].getClose() - allStocks[i][k].getClose();
                    if (price > 0)
                    {
                        gain.push_back(price);
                    }
                    else if (price < 0)
                    {
                        loss.push_back(price);
                    }
                }

                averagegain = accumulate(gain.begin(), gain.end(), 0.0) / 7;
                averageloss = accumulate(loss.begin(), loss.end(), 0.0) / 7;
                RSIndex = averagegain / averageloss;
                RSI = 100 - (100 / (1 + RSIndex));
                RSIweekly.push_back(RSI);
                // cout << RSI;
                j += 6;
            }
            else if (!RSIweekly.empty())
            {
                double current = allStocks[i][j].getClose();
                double previous = allStocks[i][j - 1].getClose();
                double change = current - previous;

                if (change > 0)
                {
                    double newPositive = (averagegain * (period - 1) + change) / period;
                    double newNegative = (averageloss * (period - 1) + 0) / period;
                    RSIndex = newPositive / newNegative;
                    RSI = 100 - (100 / (1 + RSIndex));
                    RSIweekly.push_back(RSI);
                }
                else if (change < 0)
                {
                    double newPositive = (averagegain * (period - 1) + 0) / period;
                    double newNegative = (averageloss * (period - 1) + change) / period;
                    RSIndex = newPositive / newNegative;
                    RSI = 100 - (100 / (1 + RSIndex));
                    RSIweekly.push_back(RSI);
                }
            }
        }
        WeeklyRSIAverageStack.push_back(RSIweekly);
    }

    // for (int i = 0; i < WeeklyRSIAverageStack.size(); i++)
    // {
    //     for (int j = 0; j < WeeklyRSIAverageStack[i].size(); j++)
    //     {
    //         cout << WeeklyRSIAverageStack[i][j] << ":";
    //     }
    //     cout << endl;
    // }
}

//

// -------------------------------------------  VOLATILITY  -----------------------------------------------------

// to finish later
void getMarketVolatilityByMonth(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    vector<double> VolatilityCompanyStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
        vector<double> Volatility; // Variance
        int iterator = 0;

        string startMonth = allStocks[i][0].getDate();
        // cout << "Start Date:" << startMonth << endl;
        startMonth = startMonth.substr(5, 2);
        // cout << "Start month:" << startMonth << endl;
        while (iterator < allStocks[i].size())
        {
            int tempCounter = 0;
            string month = allStocks[i][iterator].getDate();
            month = month.substr(5, 2);
            // cout << ":" << month;

            vector<double> data;
            for (int ptr = iterator; ptr < iterator + 31; ptr++)
            {
                string tempMonth = allStocks[i][ptr].getDate();
                tempMonth = tempMonth.substr(5, 2);
                if (tempMonth == month)
                {
                    cout << allStocks[i][ptr].getClose() << ":";
                    data.push_back(allStocks[i][ptr].getClose());
                }
                else if (tempMonth != month)
                {
                    break;
                }
                cout << endl;
            }

            // for (int i = 0; i < data.size(); i++)
            // {
            //     cout << data[i] << ":";
            // }

            // cout << "Inner temp month start" << endl;

            // double mean = calcMean(data);
            // vector<double> deviation = calcDeviation(data , mean);
            // vector<double> deviationSqu = calcDeviationSqu(deviation);
            // double variance= calcVariance(deviation);

            iterator++;
        }
        cout << endl;
    }
}

// to be implemented
void getMarketVolatilityByYear(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
}