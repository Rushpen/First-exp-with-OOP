#include <iostream>
#include <fstream>
#include <string>
#include <vector>
int pid = 0;
int csid = 0;
using namespace std;


struct CS
{
    std::string name = "";
    int csid = 0, workshops_num = 0, workshops_num_run = 0;
    float efficiency = 0;
};

struct Pipe
{
    int pid = 0;
    float lenght = 0;
    float diam = 0;
    bool status = false;
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
    cout << "\n Pipe index: "<<p.pid;
    cout << "\n pipe lenght: ";
    p.lenght = checking();
    cout << "\n pipe diameter: ";
    p.diam = checking();
    cout << "\n Choose pipe status:\n 0.In repair\n 1.In work\n ";
    p.status = checking_status();
    p_status(p.status);
}

void create_cs(CS& cs) {
    cs.csid = ++csid;
    cout << "\nCS index: " << cs.csid;
    cout << "\nCS Name: ";
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

int check_pipe_id(vector <Pipe>& g) {
    int x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < 0) || (x > g.size())) {
        cout << "Error!!! Input integer numeric index of existing pipe > 0" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}
int check_cs_id(vector <CS>& g) {
    int x;
    while (((cin >> x).fail()) || (cin.peek() != '\n') || (x < 0) || (x > g.size())) {
        cout << "Error!!! Input integer numeric index of existing CS > 0" << endl;
        cin.clear();
        cin.ignore(INT_MAX, '\n');
    }
    return x;
}

void show_all(vector <Pipe>& p_g, vector<CS>& cs_g) {

    if (p_g.size() !=0) 
    {
        for (int i = 0; i < p_g.size(); i++) {
            cout << "\nPipe: \nIndex: " << p_g[i].pid << "\nLenght: " << p_g[i].lenght << "\nDiameter: " << p_g[i].diam << endl;
            p_status(p_g[i].status);
        }
    }
    else
        cout << "\nThere is no pipe"<<endl;
    if (cs_g.size() != 0)
    {
        for (int i = 0; i<cs_g.size(); i++){
            cout << "\nCS index: "<< cs_g[i].csid << "\nCS Name : " << cs_g[i].name << "\nNumber of workshops : " <<
                cs_g[i].workshops_num << "\nWorkshops at work: " << cs_g[i].workshops_num_run <<
                "\nEfficiency: " << f_efficiency(cs_g[i].workshops_num_run, cs_g[i].workshops_num) << "%\n";
        }
    }
    else
        cout << "\nThere is no CS"<< endl;
}

void edit_pipe(Pipe& p) {
    if (p.lenght == 0 || p.diam == 0)
        cout << "\nThere is no pipe to change!" << endl;
    else {
        cout << "\nInput pipe status: \n";
        p.status = checking_status();
        cout << "\nChanges accepted!" << endl;
    }
}

void edit_cs(CS& cs) {
    if (cs.workshops_num == 0)
        cout << "\nThere is no CS to change!" << endl;
    else {
        cout << "\nNew number of workshops in work: \n";
        cs.workshops_num_run = check_working(cs.workshops_num);
        cout << "\nChanges accepted!" << endl;
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

Pipe& pipe_select(vector <Pipe>& g) {
    cout << "Enter index of pipe ";
    int id = check_pipe_id(g);
    return g[id - 1];

}
CS& cs_select(vector <CS>& g) {
    cout << "Enter index of pipe:  ";
    int id = check_cs_id(g);
    return g[id - 1];

}


int main() {
    vector <Pipe> pipe_group;
    vector <CS> cs_group;
   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Create pipe  2.Create CS  3.Show all objects " <<
            " 4.Edit Pipe  5.Edit CS  6.Save  7.Load  0.Exit\n";
        num_option = check_menu();
        switch (num_option)     {
        case 1: {
            Pipe P;
            create_pipe(P);
            pipe_group.push_back(P);
            break;
            }
        case 2: {
            CS cs;
            create_cs(cs);
            cs_group.push_back(cs);
            break;
            }
        case 3: {
                show_all(pipe_group, cs_group);
                break;
            }
        /**case 4: {
            edit_pipe(P);
            break;
            }
        case 5: {
            edit_cs(CS);
            break;
            }
        case 6: {
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

