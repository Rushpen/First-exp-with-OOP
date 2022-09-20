#include <iostream>
#include <fstream>
using namespace std;

struct Pipe
{
    float lenght = 0;
    float diam = 0;
    int status = -1;
};
struct CS
{
    string name = "";
    int workshops_num = 0, workshops_num_run = 0;
    float efficiency = 0;
};

float f_efficiency(int work_num_run, int work_num) 
{

    return (100*(float(work_num_run) / float(work_num)));
}
void p_status(int status_p)
{
    if (status_p == 1) {
        cout << "Status: Pipe in repair\n";
    }
    else {
        cout << "Status: Pipe is ready for operation\n";
    }
}
float checking(float check_var)
{
    while (!check_var || check_var <= 0)
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> check_var;
    }
    return check_var;
}
int checking_status(int c)
{
    while ((!c) || (c > 2) || (c < 1))
    {
        cout << "Error!\nInput one of the predefined states:\n 1.In repair\n 2.In work\n ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> c;
    }
    return c;
}
void menu_choice()
{
    cout << "\nChoose: \n 1.Create pipe  2.Create CS  3.Show all objects" <<
        "4.Edit Pipe  5.Edit CS  6.Save  7.Load  0.Exit\n";
}
int check_workshops(int work_run, int work)
{
    while ((work_run > work) || !work_run || !work)
    {
        cout << "Error!\nInput number of working shops not exceeding the total number of shops: \n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> work_run;
    }
    return work_run;
}
void save_file(float len, float d, int stt, 
    string nam, int wshops, int wshops_run, float effe)
{
    effe = f_efficiency(wshops_run, wshops);
    ofstream output;
    output.open("output_info.txt");
    output << "Pipe \npipe length: " <<len <<"\npipe diameter: " 
        <<d<<"\nstatus work: "<<stt<<"\n"<<"\nCS\nName: "
        << nam << "\nNumber of workshops: " << wshops << "\nWorkshops in work: "
        << wshops_run << "\nEfficiency: "<< effe<<"%";
    output.close();
    cout << "\nData was successfully written to the file\n";
}

int main()
{
    Pipe p;
    CS cs;
    int num_option(-1);

    while (num_option)
    {
        menu_choice();
        cin >> num_option;
        if (num_option < 0 || num_option > 7)
        {
            cout << "\nERROR! Choose one of the options below!\n\n";
        }
        if (num_option == 1)
        {
            cout << "\n pipe lenght: ";
            cin >> p.lenght;
            cout << "\n pipe diameter: ";
            cin >> p.diam;
            cout << "\n Choose pipe status:\n 1.In repair\n 2.In work\n ";
            cin >> p.status;
            p.status = checking_status(p.status);
            p_status(p.status);
        }
        if (num_option == 2)
        {
            cout << "\nCS Name: ";
            cin >> cs.name;
            cout << "\nNumber of workshops:";
            cin >> cs.workshops_num;
            checking(cs.workshops_num);
            cout << "\nWorkshops at work: ";
            cin >> cs.workshops_num_run;
            checking(cs.workshops_num_run);
            cs.workshops_num_run = check_workshops(cs.workshops_num_run, cs.workshops_num);
            cout << "\nEfficiency:";
            cout << f_efficiency(cs.workshops_num_run, cs.workshops_num)<<"%\n";
        }
        if (num_option == 3)
        {
            cout << "\nPipe \nLenght: " << p.lenght << "\nDiameter: " << p.diam << "\nPipe status: " <<p.status;
            cout << "\n\nCS \nCS Name: " << cs.name << "\nNumber of workshops: " <<
                cs.workshops_num << "\nWorkshops at work: " << cs.workshops_num_run <<
                "\nEfficiency: " << f_efficiency(cs.workshops_num_run, cs.workshops_num) << "%\n";
        }
        if (num_option == 4)
        {
            if (p.status == -1)
                cout << "\nThere is no pipe to change!" << endl;
            else if (p.status == 1 || p.status == 2) {
                cout << "\nInput pipe status: \n";
                cin >> p.status;
                checking_status(p.status);
                cout << "\nNew Pipe status: " << p.status;
                cout << "\nChanges accepted!";
            }
        }
        if (num_option == 5) 
        {
            if (cs.workshops_num == 0)
                cout << "\nThere is no CS to change!" << endl;
            else {
                cout << "\nNew number of workshops in work: \n";
                cin >> cs.workshops_num_run;
                check_workshops(cs.workshops_num_run, cs.workshops_num);
            }
        }
        if (num_option == 6) {
            save_file(p.lenght, p.diam, p.status, cs.name,
                cs.workshops_num, cs.workshops_num_run, cs.workshops_num_run);
        }
        if (num_option == 0)
        {
            return 0;
        }
    }
}

