#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"

using namespace std;

void save_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map)
{
    string f_n;
    cout << "Input filename: ";
    cin >> f_n;
    ofstream fcout;
    fcout.open(f_n + ".txt");
    if (fcout.is_open())
    {
        fcout << p_map.size() << endl << cs_map.size() << endl;
        for (auto pipe : p_map) {
            fcout << pipe.second;
        }
        for (auto cs : cs_map) {
            fcout << cs.second;
        }
        fcout.close();
        cout << "\nData was successfully written to the file\n";
    }
    else
        cout << "\nError!Failed to open file!";
}
void load_file(unordered_map <int, Pipe>&p_map, unordered_map<int, CS>&cs_map )
{
    int i, a, b;
    CS cs;
    Pipe p;
    ifstream fcin;
    string f_n;
    p_map.clear();
    cs_map.clear();
    cout << "Input name of file: ";
    cin >> f_n;
    fcin.open(f_n + ".txt");
    if (fcin.is_open()) {
        fcin >> a;
        p.set_pid(a);
        fcin >> b;
        cs.set_csid(b);
        for (i = 0; i < a; ++i) {
            fcin>>p;
            p_map.insert({p.get_pid(), p });
        }
        for (i = 0; i < b; ++i) {
            fcin>>cs;
            cs_map.insert({cs.get_csid(), cs });
        }
        cout << "The data was successfully loaded from the file!";
    }
    else
        cout << "\nError!Failed to open file!";
    fcin.close();
}


int main() {
    Pipe P;
    CS cs;
    unordered_map<int, Pipe>pipe_map;
    unordered_map<int, CS>cs_map;
   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Create pipe 2.Create CS 3.Show all objects" <<
            " 4.Edit Pipe 5.Edit CS 6.Save 7.Load 8.Filter pipe 9.Filter CS 10.Exit\n";
        checking(num_option);
        switch (num_option)     {
        case 1: {
            cin >> P;
            pipe_map.insert({P.get_pid(), P });
            break;
            }
        case 2: {
            cin >> cs;
            cs_map.insert({cs.get_csid(), cs });
            break;
            }
        case 3: {
            P.show_pipe(pipe_map);
            cs.show_cs(cs_map);
            break;
            }
        case 4: {
            P.edit_pipe(pipe_map);
            break;
            }
        case 5: {
            cs.edit_cs(cs_map);
            break;
            }
        case 6: {
            save_file(pipe_map, cs_map);
            break;
            }
        case 7: {
            load_file(pipe_map, cs_map);
            break;
           }
        case 8: {
            P.filter_pipe(pipe_map);
            break;
        }
        case 9: {
            cs.Cs_filter(cs_map);
            break;
        }
        case 10:{
            return 0;
            break;
        }
        default: {
            cout << "\nERROR! Choose one of the options below!\n\n";
            break;
        }
        }    
    }
}
