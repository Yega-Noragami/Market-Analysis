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
