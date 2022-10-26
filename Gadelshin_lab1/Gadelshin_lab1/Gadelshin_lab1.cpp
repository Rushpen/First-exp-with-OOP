#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
int pid = 0;
int csid = 0;
bool ed = 0;
using namespace std;

class CS
{
public:
    string name = "";
    int csid = 0, workshops_num = 0, workshops_num_run = 0;
    float efficiency = 0;
};

class Pipe
{
public:
    string name = "";
    int pid = 0;
    float lenght = 0;
    float diam = 0;
    bool status = false;
};

//Создание функций
void p_status(bool status_p)
{
    if (status_p == false) {
        cout << "status: Pipe in repair\n";
    }
    else {
        cout << "status: Pipe is ready for operation\n";
    }
}

float checking()
{
    float check_var;
    while (((cin >> check_var).fail()) || (cin.peek() != '\n') || check_var <=0)
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return check_var;
}

int check_menu()
{
    int check_var;
    while (((cin >> check_var).fail()) || (cin.peek() != '\n'))
    {
        cout << "\nERROR! Choose one of the options below!\n\n" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return check_var;
}

int check_pid(unordered_map<int, Pipe>& p_map) {
    int c;
    while (((cin >> c).fail()) || (cin.peek() != '\n') || c <= 0 || c > p_map.max_size())
    {
        cout << "Error!\nInput another index" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return c;
}

int check_csid(unordered_map<int, CS>& cs_map) {
    int c;
    while (((cin >> c).fail()) || (cin.peek() != '\n') || c <= 0 || c > cs_map.max_size())
    {
        cout << "Error!\nInput another index" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return c;
}

bool checking_status()
{
    bool check_st;
    while (((cin >> check_st).fail()) || (cin.peek() != '\n'))
    {
        cout << "Error!\nInput one of the predefined states:\n 0.In repair\n 1.In work\n ";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return check_st;
}

int check_edit() {
    bool edi;
    while (((cin >> edi).fail()) || (cin.peek() != '\n'))
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return edi;

}

float f_efficiency(int work_num_run, int work_num)
{
    return (100 * (float(work_num_run) / float(work_num)));
}

int check_work_shops()
{
    int w;
    while (((cin >> w).fail()) || (cin.peek() != '\n') || (w <= 0))
    {
        cout << "Error!\nInput another number!" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return w;
}

int check_working(int work)
{
    int work_run;
    while (((cin >> work_run).fail()) || (cin.peek() != '\n') || (work_run < 0) || (work_run>work))
    {
        cout << "Error!\nInput number of working shops not exceeding the total number of shops: \n";
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return work_run;
}

void create_pipe(Pipe& p) {
    p.pid = ++pid;
    cout << "\nIndex: "<<p.pid;
    cout << "\nName: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, p.name);
    cout << "\nLenght: ";
    p.lenght = checking();
    cout << "\nDiameter: ";
    p.diam = checking();
    cout << "\n Choose pipe status:\n 0.In repair\n 1.In work\n ";
    p.status = checking_status();
    p_status(p.status);
}

void create_cs(CS& cs) {
    cs.csid = ++csid;
    cout << "\nIndex: " << cs.csid;
    cout << "\nName: ";
    cin.clear();
    cin.ignore(INT_MAX, '\n');
    getline(cin, cs.name);
    cout << "\nNumber of workshops:";
    cs.workshops_num = check_work_shops();
    cout << "\nWorkshops at work: ";
    cs.workshops_num_run = check_working(cs.workshops_num);
    cout << "\nEfficiency:";
    cout << f_efficiency(cs.workshops_num_run, cs.workshops_num) << "%\n";
}

void show_all(unordered_map <int, Pipe>& p_map, unordered_map <int, CS>& cs_map) {
    
    for (auto pipe : p_map) {
        if (pipe.second.lenght != 0) {
            cout << "\nPipe "<<pipe.first<<"\nname: " << pipe.second.name << "\nlenght: " 
                << pipe.second.lenght << "\ndiameter: " << pipe.second.diam << endl;
            p_status(pipe.second.status);
        }
        else
            cout << "There is no pipe" << endl;
    }
    for (auto cs : cs_map) {
        if (cs.second.workshops_num != 0) {
            cout << "\nCS "<<cs.first<<"\nname: " << cs.second.name << "\nnumber of workshops: " 
                << cs.second.workshops_num << "\nworkshops at work: " << cs.second.workshops_num_run << endl;
            cout <<"efficiency: "<< f_efficiency(cs.second.workshops_num_run, cs.second.workshops_num) << "%" << endl;
        }
        else
            cout << "There is no CS" << endl;
    }
    }

void edit_pipe(unordered_map <int, Pipe>& p_map, int pid) {
    bool a;
        cout << "\nChange: 1.Edit one pipe  0.Delete pipe" << endl;
        ed = check_edit();
        cout << "Enter index of pipe: ";
        pid = check_pid(p_map);
        if (ed == 1) {
            cout << "\n Choose new pipe status:\n 0.In repair\n 1.In work\n ";
            cin >> a;
            p_status(a);
            auto pipe = p_map.find(pid);
            p_map.at(pid).status = a;
        }
        else {
            auto pipe = p_map.find(pid);
            p_map.erase(pipe);
        }
}

void edit_cs(unordered_map<int, CS>& cs_map, int csid) {
    int b;
    cout << "\nChange: 1.Edit one CS  0.Delete CS" << endl;
    ed = check_edit();
    cout << "Enter index of CS: ";
    csid = check_csid(cs_map);
    if (ed == 1) {
        cout << "\n Input new number of workshops at work: \n ";
        auto cs = cs_map.find(csid);
        b = check_working(cs_map.at(csid).workshops_num);
        cs_map.at(csid).workshops_num_run = b;
    }
    else {
        auto cs = cs_map.find(csid);
        cs_map.erase(cs);
    }
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
    unordered_map<int, Pipe>pipe_map;
    unordered_map<int, CS>cs_map;
   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Create pipe  2.Create CS  3.Show all objects " <<
            " 4.Edit Pipe  5.Edit CS  6.Save  7.Load  0.Exit\n";
        num_option = check_menu();
        switch (num_option)     {
        case 1: {
            Pipe P;
            create_pipe(P);
            pipe_map.insert({ P.pid, P });
            break;
            }
        case 2: {
            CS cs;
            create_cs(cs);
            cs_map.insert({ cs.csid, cs });
            break;
            }
        case 3: {
            show_all(pipe_map, cs_map);
            break;
            }
        case 4: {
            edit_pipe(pipe_map, pid);
            break;
            }
        case 5: {
            edit_cs(cs_map, csid );
            break;
            }
        /**case 6: {
                save_file(P, CS);
                break;
            }
        case 7: {
                load_file(P, CS);
                break;
            }**/
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

