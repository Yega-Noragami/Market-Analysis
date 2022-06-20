#include <iostream>
#include <fstream>
#include <string.h>
#include <sstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include "techStock.h"
using namespace std;

// function initialisation
void removeduplicate(vector<string> &vec);
int findIndex(vector<string> uniqueCompany, string code);
vector<vector<techStock>> sortEntries(vector<techStock> allDatabase, vector<string> uniqueCompany);
void getMarketcap(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get12MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get26MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get50MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
vector<vector<double>> get200MovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get12ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get24ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get50ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void get200ExponentialMovingAvg(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);
void getMarketVolatilityByMonth(vector<vector<techStock>> allStocks, vector<string> uniqueCompany); //-------------------- TO_DO ------------------//
void getMarketVolatilityByYear(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);  // -------------------- TO_DO ---------------- //
void getBiWeeklyRSI(vector<vector<techStock>> allStocks, vector<string> uniqueCompany);

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
        vector<double> sum;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum.push_back(allStocks[i][j].getClose());
                average.push_back(0);
            }
            else
            {
                sum.push_back(allStocks[i][j].getClose());
                double newMean = accumulate(sum.begin(), sum.end(), 0.0) / period;
                average.push_back(newMean);
                sum.erase(sum.begin());
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
        vector<double> sum;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum.push_back(allStocks[i][j].getClose());
                average.push_back(0);
            }
            else
            {
                sum.push_back(allStocks[i][j].getClose());
                double newMean = accumulate(sum.begin(), sum.end(), 0.0) / period;
                average.push_back(newMean);
                sum.erase(sum.begin());
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
        vector<double> sum;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum.push_back(allStocks[i][j].getClose());
                average.push_back(0);
            }
            else
            {
                sum.push_back(allStocks[i][j].getClose());
                double newMean = accumulate(sum.begin(), sum.end(), 0.0) / period;
                average.push_back(newMean);
                sum.erase(sum.begin());
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
        vector<double> sum;
        for (int j = 0; j < allStocks[i].size(); j++)
        {
            if (j < period)
            {
                sum.push_back(allStocks[i][j].getClose());
                average.push_back(0);
            }
            else
            {
                sum.push_back(allStocks[i][j].getClose());
                double newMean = accumulate(sum.begin(), sum.end(), 0.0) / period;
                average.push_back(newMean);
                sum.erase(sum.begin());
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

// helper function to calculate RSI for bi-weekly data
void getBiWeeklyRSI(vector<vector<techStock>> allStocks, vector<string> uniqueCompany)
{
    /*
    DEFINITION:

    During an uptrend, the RSI tends to stay above 30 and should frequently hit 70.
    During a downtrend, it is rare to see the RSI exceed 70, and the indicator
    frequently hits 30 or below.

    If the RSI can’t reach 70 on a number of consecutive price swings during an
    uptrend, but then drops below 30, the trend has weakened and could be
    reversing lower.

    The opposite is true for a downtrend. If the downtrend is unable to reach 30
    or below and then rallies above 70, that downtrend has weakened and could be
    reversing to the upside.
    */

    const int period = 14;

    vector<vector<double>> WeeklyRSIAverageStack;
    for (int i = 0; i < allStocks.size(); i++)
    {
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
                        loss.push_back(-1 * price);
                    }
                }

                averagegain = accumulate(gain.begin(), gain.end(), 0.0) / 7;
                averageloss = accumulate(loss.begin(), loss.end(), 0.0) / 7;
                RSIndex = averagegain / averageloss;
                RSI = 100 - (100 / (1 + RSIndex));
                RSIweekly.push_back(RSI);
            }
            else if (!RSIweekly.empty() && j > period)
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
}

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
    cout << "To be implemented" << endl;
}