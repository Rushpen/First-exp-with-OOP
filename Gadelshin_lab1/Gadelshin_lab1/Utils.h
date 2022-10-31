#pragma once
#include <iostream>
#include <unordered_map>
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

template <typename T>
int id_check(unordered_map<int, T> id_map) {
    int b = 0;
    while (((cin >> b).fail()) || (cin.peek() != '\n') || (b <= 0) || (!id_map.contains(b)))
    {
        cout << "Error!\nInput normal index!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return b;
}