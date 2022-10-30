#pragma once
#include <iostream>
using namespace std;


template <typename T>
void checking(T& a) {
    while (((cin >> a).fail()) || (cin.peek() != '\n') || a <= 0)
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
}

template <typename T>
T get_correct(T min, T max) {
    T a = 0;
    while (((cin >> a).fail()) || (cin.peek() != '\n') || (a < min) || (a> max))
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return a;
}