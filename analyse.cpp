// C++ program to demonstrate stock analysis in tech industry

#include "functions.h"
using namespace std;

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
        cout << " What do you want to calculate \n 1-Find Market Cap \n 2-find 12 day moving Average \n 3-Get Market Volatility \n 4-Get 12 Day Exponential Moving Average \n 5-Get Weekly RSI index \n press 0 to exit \n";
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
            getBiWeeklyRSI(sortedData, uniqueCompany);
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
