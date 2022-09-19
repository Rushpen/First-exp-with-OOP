#include <iostream>

using namespace std;

//Creating structures
struct Pipe
{
    float lenght = 0;
    float diam = 0;
    bool status = false;
};

struct CS
{
    string name = "";
    int workshops_num = 0;
    int workshops_num_run = 0;
    float efficiency = 0;
};

int main()
{
    Pipe p;
    CS cs;

    int num_option(-1);

    while (num_option) {
        cout << "Choose option:\n 1.Add pipe  2.Add CS  3.Show all objects  4.Edit Pipe  5.Edit CS  6.Save  7.Load  0.Exit\n";
        cin >> num_option;

        //Check
        if (num_option < 0) 
        {
            cout << "ERROR!Choose one of the options below!\n";
        }

        if (num_option == 1) 
        {
            cout << "\n pipe lenght: ";
            cin >> p.lenght;
            cout << "\n pipe diameter: ";
            cin >> p.diam;
            cout << "\n Choose status:\n 0.In repair\n 1.In work:\n ";
            cin >> p.status;
            if (p.status == 0) {
                cout << "Pipe in repair\n";
            }
            else {
                cout << "Pipe in work\n";
            }
        }
        if (num_option == 2) 
        {
            cout << "\nCS Name: ";
            cin >> cs.name;
            cout << "\nNumber of workshops:";
            cin >> cs.workshops_num;
            cout << "\nWorkshops at work: ";
            cin >> cs.workshops_num_run;
            cout << "\nEfficiency:  ";
            cin >> cs.efficiency;
        }
        if (num_option == 3)
        {
            cout << "\nPipe \nLenght: "<<p.lenght<<"\nDiameter: "<<p.diam;
            if (p.status==0) 
            {
                cout << "\nPipe in repair\n";
            }
            else 
            {
                cout << "\nPipe in work\n";
            }
            cout << "\nCS \nCS Name: " << cs.name << "\nNumber of workshops: " << cs.workshops_num << "\nWorkshops at work: " << cs.workshops_num_run << "\nEfficiency: " << cs.efficiency << "\n";
        }

        

        if (num_option == 0) 
        {
            return 0;
        }
    }
    return 0;
}

