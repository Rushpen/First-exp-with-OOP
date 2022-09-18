#include <iostream>

using namespace std;

//Creating structures
struct pipe
{
    float lenght = 0;
    float diam = 0;
    bool repairing = false;
};

struct CS
{
    string name = "";
    int workshops_num = 0;
    int workshops_num_run = 0;
    float efficiency = 0;
};

//while (true) 
//{
 //   cout<<"" << ;
//}

int main()
{
    int num_option(-1), workshops_num, workshops_num_run;
    float lenght, diam, efficiency;
    bool status;
    string cs_name;

    while (num_option) {
        cout << "Choose option:\n 1.Add pipe  2.Add CS  3.Show all objects  4.Edit Pipe  5.Edit CS  6.Save  7.Load  0.Exit\n";
        cin >> num_option;
        if (num_option == 1) 
        {
            cout << "\nInput lenght: ";
            cin >> lenght;
            cout << "\nInput diameter: ";
            cin >> diam;
            cout << "\n Choose status:\n 0.In repair\n 1.In work:\n ";
            cin >> status;
            if (status == 0) {
                cout << "In repair\n";
            }
            else {
                cout << "In work\n";
            }
        }
        if (num_option == 2) 
        {
            cout << "\nInput CS_Name: ";
            cin >> cs_name;
            cout << "\nNumber of workshops:";
            cin >> workshops_num;
            cout << "\nWorkshops at work: ";
            cin >> workshops_num_run;
            cout << "\nEfficiency:  ";
            cin >> workshops_num;
        }
        

    }
    return 0;
}

