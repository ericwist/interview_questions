// interview_questions.cpp : This file contains the 'main' function. Program execution begins and ends there.

#define STUDENT_CALCULATOR  //See Question# 1  
//#define SAFE_ROOM         //See Question# 2  
//#define CLICK_COUNTS      //See Question# 3  

#if defined(STUDENT_CALCULATOR)
  #undef SAFE_ROOM
  #undef CLICK_COUNTS
#else
  #if defined(SAFE_ROOM)
    #undef STUDENT_CALCULATOR
    #undef CLICK_COUNTS
  #else
    #if defined(CLICK_COUNTS)
      #undef STUDENT_CALCULATOR
      #undef SAFE_ROOM
    #endif
  #endif
#endif

#include <iostream>

using namespace std;


#if defined(STUDENT_CALCULATOR)
/*
Question #1 (STUDENT_CALCULATOR):
==============
You are building an educational website and want to create a simple calculator 
for students to use. The calculator will only allow addition and subtraction of
positive integers. Given an expression string using the "+" and "-" operators like
"5+16-2", write a function to find the total.

Sample input/output:
calculate("6+9-12")  => 3
calculate("1+2-3+4-5+6-7") => -2
calculate("255") => 255
*/
#include <string>
#include <vector>
void evaluate(std::string& str, int i)
{
    int sum = 0;
    char delim[2] = { 0 };
    delim[0] = '+';
    delim[1] = '-';
    int lastFound = 0;
    string::size_type found = 0;

    while (string::npos != (found = str.find_first_of(delim, found + 1)))
    {
        sum += stoi(str.substr(lastFound, found));
        lastFound = found;
    }

    sum += stoi(str.substr(lastFound, str.length()));
    cout << "SUM OF EXPRESSION# " << i << " is " << sum << endl;
}

int main()
{
    //Declare some test expressions
    vector<string> expression = { "6+9-12",/*=3*/
                         "1+2-3+4-5+6-7",/*=-2*/
                         "255" };/*=255*/
    //evaluate expressions
    int i = 0;
    vector<string>::iterator iter;
    for(iter = expression.begin(); iter != expression.end(); ++iter)
    {
        evaluate(*iter, ++i);
    }
    return 0;
}
#endif
#if defined(SAFE_ROOM)
/*
Question #2
===========
It is only safe to enter a room if ALL three dimensions of it are 
NOT prime numbers and are also NOT prime numbers raised to a power.
assume: none of the numbers can be higher than 1000

 Steps:
 1. pre-compute all primes from 1 to 1000.
 2. pre-compute all primes raised to a power up to 1000.
 3. check if any of the three dimensions of the room are in the 
    merged primes and primes2ppower list.
*/

#include <iomanip>
#include <set>

void findPrimesForRange(int max, set<int>& primes) {
    int num,i;
    bool bPrime;
    for (num = 1; num <= max; ++num)
    {
        bPrime = true;
        for (i = 2; i <= num/2; ++i)
        {
            if (num%i == 0)
            {
                bPrime = false;
                break;
            }
        }
        if (bPrime && num != 1)
        {
#if _DEBUG
            cout << num << setw(3) << "\n";
#endif
            primes.insert(num);
        }
    }
    cout << "PRIMES COUNT: " << primes.size() << setw(5) << endl;
}

void findPrimesToAPowerForRange(int max,const set<int>& primes, set<int>& primesToAPower) {
    int result = 0;
    set<int>::const_iterator piter;
    for (piter = primes.begin(); piter != primes.end(); ++piter)
    {
        result = 1;
        while (max >= (result *= *piter))
        {
#if _DEBUG
            cout << result << setw(3) << "\n";
#endif
            primesToAPower.insert(result);
        }
    }
    cout << "PRIME-2-POWER COUNT: " << primesToAPower.size() << setw(5) << endl;
}

bool isNumberInSet(int num,const set<int>& numSet)
{
    set<int>::const_iterator iter;
    for (iter = numSet.begin(); iter != numSet.end(); ++iter)
    {
        if (num == *iter)
        {
            return true;
        }
    }
    return false;
}

int main() {
    // Declare two sets
    set<int> resultSet,setOfPrimesToAPower;

    // Pre-calculate primes
    findPrimesForRange(1000, resultSet);
#if _DEBUG
    cout << "Done with primes. Press <enter> to continue..." << endl;
    getchar();
#endif
    // Pre-calculate primes to a power using the primes
    findPrimesToAPowerForRange(1000, resultSet, setOfPrimesToAPower);
#if _DEBUG
    cout << "Done with primes to power. Press <enter> to continue..." << endl;
    getchar();
#endif
    // Merge the sets in resultSet
    resultSet.insert(begin(setOfPrimesToAPower), end(setOfPrimesToAPower));

    // Print resulting set
    set<int>::const_iterator iter;
    for (iter = resultSet.begin(); iter != resultSet.end(); ++iter)
    {
#if _DEBUG
        cout << *iter << setw(3) << "\n";
#endif
    }
    cout << "MERGED FULL COUNT: " << resultSet.size() << setw(5) << endl;
    
    // Is the room safe to enter, do four different rooms
    int dim[4][3] = { { 972, 973, 992 },/*safe*/
                       { 4, 330, 997 },/*NOT safe*/
                       { 1, 74, 626 }, /*safe*/
                       { 49, 74, 626 } };/*NOT safe*/
    bool bSafe;
    for (int i = 0; i < 4; ++i)
    {
        bSafe = true;
        for (int j = 0; j < 3; ++j)
        {
            if (isNumberInSet(dim[i][j], resultSet))
            {
                bSafe = false;
                break;
            }
        }
        if (bSafe)
        {
            cout << "Room " << i + 1 << " is safe to enter!" << endl;
        }
        else
        {
            cout << "Room " << i + 1 << " is NOT to enter!" << endl;
        }
    }
    return 0;
}

#endif

#if defined(CLICK_COUNTS)
    /*
Question# 3
===========
You are in charge of a display advertising program. Your ads are displayed on websites all over
the internet. You have some CSV input data that counts how many times that users have clicked 
on an ad on each individual domain. Every line consists of a click count and a domain name, 
like this:

counts = [ "900,google.com",
     "60,mail.yahoo.com",
     "10,mobile.sports.yahoo.com",
     "40,sports.yahoo.com",
     "300,yahoo.com",
     "10,stackoverflow.com",
     "2,en.wikipedia.org",
     "1,es.wikipedia.org",
     "1,mobile.sports" ]

Write a function that takes this input as a parameter and returns a data structure containing 
the number of clicks that were recorded on each domain AND each subdomain under it. For 
example, a click on "mail.yahoo.com" counts toward the totals for "mail.yahoo.com", "yahoo.com",
and "com". (Subdomains are added to the left of their parent domain. So "mail" and "mail.yahoo"
are not valid domains. Note that "mobile.sports" appears as a separate domain as the last item 
of the input.)

Sample output (in any order/format):

calculateClicksByDomain(counts)
1320    com
 900    google.com
 410    yahoo.com
  60    mail.yahoo.com
  10    mobile.sports.yahoo.com
  50    sports.yahoo.com
  10    stackoverflow.com
   3    org
   3    wikipedia.org
   2    en.wikipedia.org
   1    es.wikipedia.org
   1    mobile.sports
   1    sports
    */
#include <string>
#include <vector>
#include <set>
#include <iomanip>
#include <algorithm>
class CClickData
{
#define ACCESSOR_STR( member ) string& Get##member() { return m_##member; } void Set##member(const string& s) { m_##member = s; }
#define ACCESSOR_INT( member ) int Get##member() { return m_##member; } void Set##member(const int& n) { m_##member = n; }
public:
    CClickData(string& address, int& clicks):
        m_Address(address),
        m_Clicks(clicks)
    {
    }
    ~CClickData()
    {}
    ACCESSOR_STR(Address)
    ACCESSOR_INT(Clicks)
private:
    string m_Address;
    int m_Clicks;
};

void createResultSet(string& s, set<string>& strSet)
{
    string::size_type found = 0;
    while (string::npos != (found = s.find_last_of(".", found - 1)))
    {
        string str = s.substr(found, s.length());
        if (str[0] == '.')
        {
            str = str.substr(1, str.length());
        }
        strSet.insert( str );
    }
    //get full string
    strSet.insert(s);
}

void calculateClicksByDomain(const vector<vector<string>>& counts,const set<string>& searchStrings, vector<CClickData*>& clickdata)
{
    int sum_clicks;
    set<string>::const_iterator iter;
    for (iter = searchStrings.begin(); iter != searchStrings.end(); ++iter)
    {
        sum_clicks = 0;
        string::size_type found = string::npos;
        for (int i = 0; i < counts.size(); ++i)
        {
            found = string::npos;
            if (string::npos != (found = counts[i][1].find(*iter)))
            {
                if (counts[i][1].size() - found == (*iter).size())
                {
                    sum_clicks += stoi(counts[i][0]);
                }
            }
        }
        string str = *iter;
        CClickData* clicksbydomain = new CClickData(str, sum_clicks);
        clickdata.push_back(clicksbydomain);
    }
}

bool cmp(CClickData *a, CClickData *b) {
    return (a->GetClicks() > b->GetClicks());
}
int main() {
    vector<vector<string>> counts = {
        {"900","google.com"},
        {"60","mail.yahoo.com"},
        {"10","mobile.sports.yahoo.com"},
        {"40","sports.yahoo.com"},
        {"300","yahoo.com"},
        {"10","stackoverflow.com"},
        {"2","en.wikipedia.org"},
        {"1","es.wikipedia.org"},
        {"1","mobile.sports"}
    };

    set<string> searchStrings;
    vector<CClickData*> vecClickData;
    for (int i = 0; i < counts.size(); ++i) {
        createResultSet(counts[i][1], searchStrings);
    }
    calculateClicksByDomain(counts, searchStrings, vecClickData);
    sort(vecClickData.begin(), vecClickData.end(), cmp);
    vector<CClickData*>::const_iterator iter;
    for (iter = vecClickData.begin(); iter != vecClickData.end(); ++iter)
    {
        cout << (*iter)->GetClicks() << setw(6) << "\t\t\t" << (*iter)->GetAddress() << "\n";
    }
    cout << endl;
    
    for (iter = vecClickData.begin(); iter != vecClickData.end(); ++iter)
    {
        CClickData* pe = *iter;
        delete pe;
    }
    vecClickData.clear();

    return 0;
}

#endif

