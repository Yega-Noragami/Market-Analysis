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
    vector<vector<techStock>> sortedData = sortEntries(allDatabase, uniqueCompany);

    return 0;
}

// Helper function to remove duplicate entries from a vector
void removeduplicate(vector<string> &vec)
{
    sort(vec.begin(), vec.end());
    vec.erase(unique(vec.begin(), vec.end()), vec.end());

    for (int i = 0; i < vec.size(); i++)
    {
        cout << vec[i] << endl;
    }
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