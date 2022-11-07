#pragma once
#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "CS.h"
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
        cout << "Error!\nInput number that >"<<min<<" and <"<< max<< endl;
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

template <typename T>
using filter_p = bool (*) (Pipe& p, T par);


template <typename T>
unordered_set <int> search_p(unordered_map <int, Pipe>& pipe_group, filter_p<T> f, T par) {
    unordered_set <int> id;
    for (auto& pipe : pipe_group) {
        if (f(pipe.second, par))
            id.insert(pipe.second.get_pid());
    }
    return id;
}

template <typename T>
using filter_cs = bool(*) (CS& cs, T par);

template <typename T>
unordered_set <int> search_cs(unordered_map <int, CS>& cs_group, filter_cs<T> f, T par) {
    unordered_set <int> id;
    for (auto& cs : cs_group) {
        if (f(cs.second, par))
            id.insert(cs.second.get_csid());
    }
    return id;
}