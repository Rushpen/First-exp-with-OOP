#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Создание структур
struct Pipe
{
    float lenght = 0;
    float diam = 0;
    int status = -1;
};
struct CS
{
    string name = "";
    float workshops_num = 0, workshops_num_run = 0;
    float efficiency = 0;
};

//Создание функций
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
    while (!check_var || check_var <= 0 )
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

float f_efficiency(int work_num_run, int work_num)
{

    return (100 * (float(work_num_run) / float(work_num)));
}

void menu_choice()
{
    cout << "\nChoose: \n 1.Create pipe  2.Create CS  3.Show all objects" <<
        "4.Edit Pipe  5.Edit CS  6.Save  7.Load  0.Exit\n";
}

float check_work_shops(float w)
{
    while (!w || w <= 0 || (w - floor(w) != 0))
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
        cin >> w;
    }
    return w;
}

float check_working(float work_run, float work)
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

void create_pipe(Pipe& p) {
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
}

void create_cs(CS& cs) {
    cout << "\nCS Name: ";
    cin >> cs.name;
    cout << "\nNumber of workshops:";
    cin >> cs.workshops_num;
    cs.workshops_num = check_work_shops(cs.workshops_num);
    cout << "\nWorkshops at work: ";
    cin >> cs.workshops_num_run;
    cs.workshops_num_run = check_work_shops(cs.workshops_num_run);
    cs.workshops_num_run = check_working(cs.workshops_num_run, cs.workshops_num);
    cout << "\nEfficiency:";
    cout << f_efficiency(cs.workshops_num_run, cs.workshops_num) << "%\n";
}

void show_all(const Pipe& p, CS& cs) {

    if (p.lenght != 0 && p.diam != 0 && p.status != -1) {
        p_status(p.status);
        cout << "\nPipe \nLenght: " << p.lenght << "\nDiameter: " << p.diam << endl;
    }
    else
        cout << "\nThere is no pipe"<<endl;
    if (cs.name != "" && cs.workshops_num != 0)
        cout << "\nCS \nCS Name: " << cs.name << "\nNumber of workshops: " <<
        cs.workshops_num << "\nWorkshops at work: " << cs.workshops_num_run <<
        "\nEfficiency: " << f_efficiency(cs.workshops_num_run, cs.workshops_num) << "%\n";
    else
        cout << "\nThere is no CS"<< endl;
}

void save_file(const Pipe& p, const CS& cs)
{
    //cs.efficiency = f_efficiency(wshops_run, wshops);
    ofstream output;
    output.open("output_info.txt");
    if (output.is_open())
    {
        output << p.lenght << "\n" << p.diam << "\n" << p.status << "\n" << cs.name << "\n" << cs.workshops_num << "\n" << cs.workshops_num_run << "\n" << f_efficiency(cs.workshops_num_run, cs.workshops_num) << "\n";
        output.close();
        cout << "\nData was successfully written to the file\n";
    }
    else
        cout << "\nError!Failed to open file!";
}

void load_file(Pipe& p, CS& cs) {
    ifstream file_1;
    string line;
    file_1.open("output_info.txt");
    getline(file_1, line);
    p.lenght = stof(line);
    getline(file_1, line);
    p.diam = stof(line);
    getline(file_1, line);
    p.status = stoi(line);
    getline(file_1, line);
    cs.name = line;
    getline(file_1, line);
    cs.workshops_num = stoi(line);
    getline(file_1, line);
    cs.workshops_num_run = stoi(line);
    getline(file_1, line);
    cs.efficiency = stof(line);
    cout << "The data was successfully loaded from the file!";
}


int main() {
   Pipe p; CS cs;
   int num_option(-1);
    while (num_option) {
        menu_choice();
        cin >> num_option;
        switch (num_option)     {
        case 0: 
            return 0;
            break;
        
        case 1: {
            create_pipe(p);
            break;
            }
        case 2: {
            create_cs(cs);
            break;
            }
        case 3: {
                show_all(p, cs);
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
                    cs.workshops_num_run = check_work_shops(cs.workshops_num_run);
                    check_working(cs.workshops_num_run, cs.workshops_num);
                }
                break;
            }
        case 6: {
                save_file(p, cs);
                break;
            }
        case 7: {
                load_file(p, cs);
                break;
            }
        default: {
            cout << "\nERROR! Choose one of the options below!\n\n";
            break;
        }
        }    
    }
}

