#include <iostream>
#include <fstream>
#include <string>
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
int checking_status(int check_st)
{
    while ((!check_st) || (check_st > 2) || (check_st < 1))
    {
        cout << "Error!\nInput one of the predefined states:\n 1.In repair\n 2.In work\n ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> check_st;
    }
    return check_st;
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
void save_file(float len, float d, int p_stt, 
    string nam, int wshops, int wshops_run, float effe)
{
    effe = f_efficiency(wshops_run, wshops);
    ofstream output;
    output.open("output_info.txt");
    output <<len <<"\n" <<d<<"\n"<<p_stt<<"\n"<< nam << "\n" << wshops << "\n"<< wshops_run << "\n"<< effe<<"\n";
    output.close();
    cout << "\nData was successfully written to the file\n";
}
void option_3(float leng, float diamet, int sts,
    string name_1, int w_shops, int w_shops_r) {
    cout << "\nPipe \nLenght: " << leng << "\nDiameter: " << diamet << "\nPipe status: " << sts;
    cout << "\n\nCS \nCS Name: " << name_1 << "\nNumber of workshops: " <<
      w_shops << "\nWorkshops at work: " << w_shops_r <<
      "\nEfficiency: " << f_efficiency(w_shops_r, w_shops) << "%\n";
}
void load_file(float& len, float& d, int& p_stt,
    string& nam, int& wshops, int& wshops_run, float& effe) {
    ifstream file_1;
    string line;
    file_1.open("output_info.txt");
    getline(file_1, line);
    len = stof(line);
    getline(file_1, line);
    d = stof(line);
    getline(file_1, line);
    p_stt = stof(line);
    getline(file_1, line);
    nam = line;
    getline(file_1, line);
    wshops = stoi(line);
    getline(file_1, line);
    wshops_run = stoi(line);
    getline(file_1, line);
    effe = stof(line);
}


int main() {
   Pipe p;
   CS cs;
   int num_option(-1);
    while (num_option) {
        menu_choice();
        cin >> num_option;
        switch (num_option) {
        case 0: {
            return 0;
            break;
        }
        case 1: {
                cout << "\n pipe lenght: ";
                cin >> p.lenght;
                p.lenght = checking(p.lenght);
                cout << "\n pipe diameter: ";
                cin >> p.diam;
                p.diam = checking(p.diam);
                cout << "\n Choose pipe status:\n 1.In repair\n 2.In work\n ";
                cin >> p.status;
                p.status = checking_status(p.status);
                p_status(p.status);
                break;
            }
        case 2: {
                cout << "\nCS Name: ";
                cin >> cs.name;
                cout << "\nNumber of workshops:";
                cin >> cs.workshops_num;
                cs.workshops_num = checking(cs.workshops_num);
                cout << "\nWorkshops at work: ";
                cin >> cs.workshops_num_run;
                cs.workshops_num_run = checking(cs.workshops_num_run);
                cs.workshops_num_run = check_workshops(cs.workshops_num_run, cs.workshops_num);
                cout << "\nEfficiency:";
                cout << f_efficiency(cs.workshops_num_run, cs.workshops_num) << "%\n";
                break;
            }
        case 3: {
                option_3(p.lenght, p.diam, p.status, cs.name, cs.workshops_num, cs.workshops_num_run);
                break;
            }
        case 4: {
                if (p.status == -1)
                    cout << "\nThere is no pipe to change!" << endl;
                else if (p.status == 1 || p.status == 2) {
                    cout << "\nInput pipe status: \n";
                    cin >> p.status;
                    checking_status(p.status);
                    cout << "\nNew Pipe status: " << p.status;
                    cout << "\nChanges accepted!";
                }
                break;
            }
        case 5: {
                if (cs.workshops_num == 0)
                    cout << "\nThere is no CS to change!" << endl;
                else {
                    cout << "\nNew number of workshops in work: \n";
                    cin >> cs.workshops_num_run;
                    check_workshops(cs.workshops_num_run, cs.workshops_num);
                }
                break;
            }
        case 6: {
                save_file(p.lenght, p.diam, p.status, cs.name,
                    cs.workshops_num, cs.workshops_num_run, cs.workshops_num_run);
                break;
            }
        case 7: {
                load_file(p.lenght, p.diam, p.status, cs.name, cs.workshops_num, cs.workshops_num_run, cs.efficiency);
                cout << "The data was successfully loaded from the file!";
                break;
            }
        default: {
            cout << "\nERROR! Choose one of the options below!\n\n";
            break;
        }
        }    
    }
}

