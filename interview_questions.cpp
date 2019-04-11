// interview_questions.cpp : This file contains the 'main' function. Program execution begins and ends there.
/*
You are building an educational website and want to create a simple calculator for students to use. The calculator will only allow addition and subtraction of positive integers.
Given an expression string using the "+" and "-" operators like "5+16-2", write a function to find the total.

Sample input/output:
calculate("6+9-12")  => 3
calculate("1+2-3+4-5+6-7") => -2
calculate("255") => 255
 */
#include <iostream>
#include <string>

using namespace std;

void evaluate(std::string& str)
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
    cout << "SUM: " << sum << endl;
}

int main() {
    string expression1 = "6+9-12"; // = 3
    string expression2 = "1+2-3+4-5+6-7"; // = -2
    string expression3 = "255"; // = 255

    evaluate(expression3);

    return 0;
}

