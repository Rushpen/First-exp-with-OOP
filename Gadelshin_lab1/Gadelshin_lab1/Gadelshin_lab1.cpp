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
    while (((cin >> c).fail()) || (cin.peek() != '\n') || c <= 0 || (!p_map.contains(c)))
    {
        cout << "Error!\nInput another index" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return c;
}

int check_csid(unordered_map<int, CS>& cs_map) {
    int c;
    while (((cin >> c).fail()) || (cin.peek() != '\n') || c <= 0 || (!cs_map.contains(c)))
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

void show_all(unordered_map <int, Pipe>& p_map, unordered_map <int, CS>& cs_map) 
{
        if (p_map.size()!=0) {
            for (auto pipe : p_map) {
                cout << "\nPipe " << pipe.first << "\nname: " << pipe.second.name << "\nlenght: "
                    << pipe.second.lenght << "\ndiameter: " << pipe.second.diam << endl;
                p_status(pipe.second.status);
            }
        }
        else
            cout << "There is no pipe" << endl;

        if (cs_map.size() != 0) {
            for (auto cs : cs_map) {
                cout << "\nCS " << cs.first << "\nname: " << cs.second.name << "\nnumber of workshops: "
                    << cs.second.workshops_num << "\nworkshops at work: " << cs.second.workshops_num_run << endl;
                cout << "efficiency: " << f_efficiency(cs.second.workshops_num_run, cs.second.workshops_num) << "%" << endl;
            }
        }
        else
            cout << "\nThere is no CS" << endl;
 }

void edit_pipe(unordered_map <int, Pipe>& p_map, int pid) {
    bool a;
    if (p_map.size() != 0) {
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
    else
        cout << "There is no Pipe for edit!!"<<endl;
}

void edit_cs(unordered_map<int, CS>& cs_map, int csid) {
    int b, c;
    if (cs_map.size() != 0)
    {
        cout << "\nChange: 1.Edit one CS  0.Delete CS" << endl;
        ed = check_edit();
        cout << "Enter index of CS: ";
        csid = check_csid(cs_map);
        if (ed == 1) {
            cout << "\n Input new number of workshops at work: \n ";
            auto cs = cs_map.find(csid);
            c = cs_map.at(csid).workshops_num;
            b = check_working(c);
            cs_map.at(csid).workshops_num_run = b;
        }
        else {
            auto cs = cs_map.find(csid);
            cs_map.erase(cs);
        }
    }
    else
        cout << "There is no CS for edit!"<<endl;
}

void save_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map)
{
    string f_n;
    cout << "Input filename: ";
    cin >> f_n;
    ofstream output;
    output.open(f_n + ".txt");
    if (output.is_open())
    {
        output << p_map.size() << endl << cs_map.size() << endl;

        for (auto pipe : p_map) {
            output <<pipe.first<<"\n" << pipe.second.name << "\n" << pipe.second.lenght
            << "\n" << pipe.second.diam << "\n" << pipe.second.status << "\n";
        }
        for (auto cs : cs_map) {
            output<< cs.first << "\n"<< cs.second.name << "\n" << cs.second.workshops_num << "\n" << cs.second.workshops_num_run
             << "\n" << f_efficiency(cs.second.workshops_num_run, cs.second.workshops_num) << "\n";
        }
        output.close();
        cout << "\nData was successfully written to the file\n";
    }
    else
        cout << "\nError!Failed to open file!";
}


void load_file(ifstream& fin, unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map)
{
    int a, b, i;
    Pipe p;
    CS cs;
        fin >> a;
        fin >> b;
        for (i = 0; i < a; ++i) {
            fin >> p.pid;
            fin.ignore();
            getline(fin, p.name);
            fin >> p.lenght >> p.diam >> p.status;
            p_map[p.pid] = p;
        }
        for (i = 0; i < b; ++i) {
            fin >> cs.csid;
            fin.ignore();
            getline(fin, cs.name);
            fin >> cs.workshops_num >> cs.workshops_num_run >> cs.efficiency;
            cs_map[cs.csid] = cs;
        }
        cout << "The data was successfully loaded from the file!";
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
        case 6: {
                save_file(pipe_map, cs_map);
                break;
            }
        case 7: {
            ifstream fin;
            string f_n;
            cout << "Input name of file: ";
            cin >> f_n;
            fin.open(f_n+".txt");
            if (fin.is_open()) {
                load_file(fin, pipe_map, cs_map);
            }
            else
                cout << "\nError!Failed to open file!";
                fin.close();
            break;
           }
        case 0:{
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

