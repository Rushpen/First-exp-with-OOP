#include <iostream>
#include <fstream>
#include <string>
using namespace std;

//Создание структур
struct Pipe 
{
    float lenght = 0;
    float diam = 0;
    bool status = false;
};
struct CS
{
    string name = "";
    int workshops_num = 0, workshops_num_run = 0;
    float efficiency = 0;
};

//Создание функций
void p_status(bool status_p)
{
    if (status_p == false) {
        cout << "Status: Pipe in repair\n";
    }
    else {
        cout << "Status: Pipe is ready for operation\n";
    }
}

float checking(float check_var)
{
    while (((cin >> check_var).fail()) || (cin.peek() != '\n') || check_var <=0)
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return check_var;
}

int check_menu(int check_var)
{
    while (((cin >> check_var).fail()) || (cin.peek() != '\n'))
    {
        cout << "\nERROR! Choose one of the options below!\n\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return check_var;
}

bool checking_status(bool check_st)
{
    while (((cin >> check_st).fail()) || (cin.peek() != '\n'))
    {
        cout << "Error!\nInput one of the predefined states:\n 0.In repair\n 1.In work\n ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return check_st;
}

float f_efficiency(int work_num_run, int work_num)
{
    return (100 * (float(work_num_run) / float(work_num)));
}

int check_work_shops(int w)
{
    while (((cin >> w).fail()) || (cin.peek() != '\n') || (w < 0))
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return w;
}

int check_working(int work_run, int work)
{
    while (((cin >> work_run).fail()) || (cin.peek() != '\n') || (work_run < 0) || (work_run>work))
    {
        cout << "Error!\nInput number of working shops not exceeding the total number of shops: \n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return work_run;
}

void create_pipe(Pipe& p) {
    cout << "\n pipe lenght: ";
    p.lenght = checking(p.lenght);
    cout << "\n pipe diameter: ";
    p.diam = checking(p.diam);
    cout << "\n Choose pipe status:\n 0.In repair\n 1.In work\n ";
    p.status = checking_status(p.status);
    p_status(p.status);
}

void create_cs(CS& cs) {
    cout << "\nCS Name: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "\nNumber of workshops:";
    cs.workshops_num = check_work_shops(cs.workshops_num);
    cout << "\nWorkshops at work: ";
    cs.workshops_num_run = check_working(cs.workshops_num_run, cs.workshops_num);
    cout << "\nEfficiency:";
    cout << f_efficiency(cs.workshops_num_run, cs.workshops_num) << "%\n";
}

void show_all(const Pipe& p, CS& cs) {

    if (p.lenght != 0 && p.diam != 0) {
        p_status(p.status);
        cout << "\nPipe \nLenght: " << p.lenght << "\nDiameter: " << p.diam << endl;
        p_status(p.status);
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
    if (file_1.is_open()) 
    {
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
    else 
        cout << "\nError!Failed to open file!";
}


int main() {
   Pipe P; CS CS;
   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Create pipe  2.Create CS  3.Show all objects " <<
            " 4.Edit Pipe  5.Edit CS  6.Save  7.Load  8.Exit\n";
        num_option = check_menu(num_option);
        switch (num_option)     {
        case 1: {
            create_pipe(P);
            break;
            }
        case 2: {
            create_cs(CS);
            break;
            }
        case 3: {
                show_all(P, CS);
                break;
            }
        case 4: {
                if (P.lenght == 0 || P.diam == 0)
                    cout << "\nThere is no pipe to change!" << endl;
                else  {
                    cout << "\nInput pipe status: \n";
                    P.status = checking_status(P.status);
                    cout << "\nNew Pipe status: " << P.status;
                    cout << "\nChanges accepted!" << endl;
                }
                break;
            }
        case 5: {
                if (CS.workshops_num == 0)
                    cout << "\nThere is no CS to change!" << endl;
                else {
                    cout << "\nNew number of workshops in work: \n";
                    CS.workshops_num_run = check_work_shops(CS.workshops_num_run);
                    check_working(CS.workshops_num_run, CS.workshops_num);
                }
                break;
            }
        case 6: {
                save_file(P, CS);
                break;
            }
        case 7: {
                load_file(P, CS);
                break;
            }
        case 0: {
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

