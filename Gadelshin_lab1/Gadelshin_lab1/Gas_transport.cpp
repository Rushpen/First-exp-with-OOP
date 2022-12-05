#include "Gas_transport.h"
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

bool check_p_status(Pipe& p, bool status) {
    return (p.get_stat() == status);
}
bool check_p_name(Pipe& Pp, string p_name) {
    return (Pp.name.find(p_name) != string::npos);
}
bool check_cs_name(CS& cs, string cs_name) {
    return (cs.name.find(cs_name) != string::npos);
}
bool check_unused(CS& cs, float n) {
    return (cs.cs_unused() >= n);
}

/**bool check_diam(Pipe& p, double a) {
    return (p.get_diam() == a);
}*/

int All::check_exist(int x) {
    while (cs_map.find(x) == cs_map.end()) {
        cout << "There isn't exist such CS, input another!" << endl;
        x = get_correct(0, INT_MAX);
    }
    return x;
}

int All::check_p(int x) {
    int j = 0;
    if (graph.size() != 0) {
        for (auto& i : graph) {
            if ((i.second.id_ent == x) or (i.second.id_ex == x))
                j++;
        }
    }
    return j;
}

int All::System::max_ids = 0;

int All::check_graph(int x) {
    while (check_p(x) >= cs_map[x].get_w()) {
        cout << "Choose another Cs!" << endl;
        x = get_correct(0, INT_MAX);

    }
    return x;
}

bool All::check_used(int x, int y) {
    int k = 0;
    for (auto& i : graph) {
        if ((i.second.id_ent == x and i.second.id_ex == y) or (i.second.id_ent == y and i.second.id_ex == x)) {
            k++;
            cout << "\nThis connection is exists!" << endl;
        }
        if (k == 0)
            return true;
        else
            return false;
    }
}

bool All::check_i(int x) {
    int n = 0;
    for (auto& i : graph)
        if (i.second.id_pip == x)
            n++;
    if (n == 0)
        return true;

    else return false;
}

int All::edge(int x) {
    int k = -1;
    for (auto& i : p_map) {
        if (i.second.get_diam() == x) {
            if (check_i(i.first)) {
                k = i.first;
                return k;
            }
        }
    }
    return k;
}

void All::save_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map)
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

void All::load_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map)
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
            fcin >> p;
            p_map.insert({ p.get_pid(), p });
        }
        for (i = 0; i < b; ++i) {
            fcin >> cs;
            cs_map.insert({ cs.get_csid(), cs });
        }
        cout << "The data was successfully loaded from the file!";
    }
    else
        cout << "\nError!Failed to open file!";
    fcin.close();
}

unordered_set <int> All::search_pipes(unordered_map <int, Pipe>& p_map) {
    int a;
    unordered_set<int>v_id;
    if (p_map.size() != 0) {
        cout << "Choose:  0.Filter by name 1.Filter by status " << endl;
        a = get_correct(0, 2);
        if (a == 0) {
            string n;
            cout << "Input name: " << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, n);
            v_id = search_p(p_map, check_p_name, n);
        }
        if (a == 1) {
            bool s;
            cout << "0.In repair  1.In working" << endl;
            s = get_correct(0, 1);
            v_id = search_p(p_map, check_p_status, s);
        }
        if (v_id.size() == 0)
            cout << "\nThere are no such pipes!" << endl;
    }
    else
        cout << "\nPipes not yet avalaible or have been deleted" << endl;

    for (auto& v : v_id)
        cout << p_map.at(v);
    return v_id;
}

/**unordered_set<int> All::search_d(unordered_map <int, Pipe>& p_map, double a) {
    unordered_set<int>d_id;
    if (p_map.size() != 0) {
        d_id = search_p(p_map, check_diam, a);
    }
    return d_id;
}*/


void All::delete_pipes(unordered_map <int, Pipe>& p_map) {
    int id, h;
    bool ed;
    unordered_set<int>ids;
    cout << "Delete: 0.One pipe  1.Pipes" << endl;
    ed = get_correct(0, 1);
    if (ed == 0) {
        cout << "Identifiers: ";
        for (auto& i : p_map)
            cout << i.first << " ";
        cout << "\nInput index of pipe: " << endl;
        id = id_check(p_map);
        auto pipe = p_map.find(id);
        p_map.erase(pipe);
        cout << "\nPipe deleted!" << endl;
    }
    if (ed == 1) {
        cout << "0.By ids  1.By filter" << endl;
        h = get_correct(0, 1);
        if (h == 0) {
            int n, z;
            cout << "Identifiers: ";
            for (auto& i : p_map)
                cout << i.first << " ";
            cout << "How many pipes you want to delete?" << endl;
            n = get_correct(1, int(p_map.size()));
            cout << "Input numbers of pipes: " << endl;
            for (int i = 0; i < n; ++i) {
                z = get_correct(1, int(p_map.size()));
                if (p_map.find(z) != p_map.end())
                    ids.insert(z);
            }
            for (auto& i : ids)
                p_map.erase(i);
            cout << "\nPipes deleted!" << endl;
        }
        if (h == 1) {
            ids = search_pipes(p_map);
            if (ids.size() != 0) {
                for (auto& i : ids)
                    p_map.erase(i);
                cout << "\nPipes deleted!" << endl;
            }
        }
    }
}

void All::edit_pipe(unordered_map <int, Pipe>& p_map) {
    bool a, d;
    int ed, id;
    unordered_set<int>ids;
    if (p_map.size() != 0) {
        cout << "\nChange: 1.Edit one pipe  2.Edit pipes  0.Delete pipe" << endl;
        ed = get_correct(0, 2);
        if (ed == 1) {
            cout << "Identifiers: ";
            for (auto& i : p_map)
                cout << i.first << " ";
            cout << "\nInput index of pipe: " << endl;
            id = id_check(p_map);
            cout << "\n Choose new pipe status:\n 0.In repair\n 1.In work\n ";
            a = get_correct(0, 1);
            auto pipe = p_map.find(id);
            p_map.at(id).set_stat(a);
            cout << "Changes applied!" << endl;
        }
        if (ed == 2) {
            cout << "Choose method: 0.By ids  1.By filter" << endl;
            d = get_correct(0, 1);
            if (d == 0) {
                int n, z;
                cout << "Identifiers: ";
                for (auto& i : p_map)
                    cout << i.first << " ";
                cout << "\nHow many pipes you want to edit?" << endl;
                n = get_correct(1, int(p_map.size()));
                cout << "Input numbers of pipes: " << endl;
                for (int i = 0; i < n; ++i) {
                    z = get_correct(1, int(p_map.size()));
                    if (p_map.find(z) != p_map.end())
                        ids.insert(z);
                }
                cout << "\nInput new status of pipes (0 if repairing, 1 if works)" << endl;
                a = get_correct(0, 1);
                for (auto& i : ids)
                    p_map.at(i).set_stat(a);
                cout << "\nChanges applied!" << endl;
            }
            if (d == 1) {
                ids = search_pipes(p_map);
                if (ids.size() != 0) {
                    cout << "\nEnter new status: 0(in repair), 1(ready for operation)" << endl;
                    a = get_correct(0, 1);
                    for (auto& i : ids)
                        p_map.at(i).set_stat(a);
                    cout << "\nChanges applied!" << endl;
                }
            }
        }
        else if (ed == 0) {
            delete_pipes(p_map);
        }
    }
    else
        cout << "There is no Pipe for edit!" << endl;
}

unordered_set <int> All::search_Css(unordered_map<int, CS>& cs_map) {
    int a;
    unordered_set<int> new_cs;
    if (cs_map.size() != 0)
    {
        cout << "Choose filter:  0.By name 1.By percentage of unused works' " << endl;
        a = get_correct(0, 1);
        if (a == 0)
        {
            string n;
            cout << "Input name: " << endl;
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            getline(cin, n);
            new_cs = search_cs(cs_map, check_cs_name, n);
        }
        else if (a == 1)
        {
            float per;
            cout << "Input percentage of unused works(0-100): " << endl;
            per = get_correct(0, 100);
            new_cs = search_cs(cs_map, check_unused, per);
        }
        if (new_cs.size() == 0)
            cout << "\nThere are no such CSs!" << endl;
    }
    else
        cout << "\nCSs not yet avalaible or have been deleted" << endl;
    for (auto& v : new_cs)
        cout << cs_map[v];
    return new_cs;
}

void All::delete_css(unordered_map<int, CS>& cs_map) {
    int id, h;
    bool ed;
    unordered_set<int>ids;
    cout << "Delete: 0.One cs  1.CSs" << endl;
    ed = get_correct(0, 1);
    if (ed == 0) {
        cout << "Identifiers: ";
        for (auto& i : cs_map)
            cout << i.first << " ";
        cout << "\nInput index of CS: " << endl;
        id = id_check(cs_map);
        auto pipe = cs_map.find(id);
        cs_map.erase(pipe);
        cout << "\nCS deleted" << endl;
    }
    if (ed == 1) {
        cout << "0.By ids  1.By filter" << endl;
        h = get_correct(0, 1);
        if (h == 0) {
            int n, z;
            cout << "Identifiers: ";
            for (auto& i : cs_map)
                cout << i.first << " ";
            cout << "\nHow many CSs you want to delete?" << endl;
            n = get_correct(1, int(cs_map.size()));
            cout << "Input numbers of CSs: " << endl;
            for (int i = 0; i < n; ++i) {
                z = get_correct(1, int(cs_map.size()));
                if (cs_map.find(z) != cs_map.end())
                    ids.insert(z);
            }
            for (auto& i : ids)
                cs_map.erase(i);
            cout << "\nCSs deleted!" << endl;
        }
        if (h == 1) {
            ids = search_Css(cs_map);
            if (ids.size() != 0) {
                for (auto& i : ids)
                    cs_map.erase(i);
                cout << "\nCSs deleted!" << endl;
            }
        }
    }
}

void All::edit_cs(unordered_map<int, CS>& cs_map) {
    int b = 0, ed, id;
    bool d;
    unordered_set<int>idcs;
    if (cs_map.size() != 0)
    {
        cout << "\nChange: 1.Edit one CS  2.Edit >1 CS  0.Delete CS" << endl;
        ed = get_correct(0, 2);
        if (ed == 1) {
            cout << "Identifiers: ";
            for (auto& i : cs_map)
                cout << i.first << " ";
            cout << "\nEnter index of CS: ";
            id = id_check(cs_map);
            cout << "\n Input new number of workshops at work: \n ";
            auto cs = cs_map.find(id);
            b = get_correct(0, cs_map.at(id).get_w());
            cs_map.at(id).set_w_r(b);
            cout << "\nChanges applied" << endl;
        }

        if (ed == 2) {
            cout << "Choose method: 0.By ids  1.By filter" << endl;
            d = get_correct(0, 1);
            if (d == 0) {
                int n, z;
                cout << "Identifiers: ";
                for (auto& i : cs_map)
                    cout << i.first << " ";
                cout << "\nHow many CSs you want to edit?" << endl;
                n = get_correct(1, int(cs_map.size()));
                cout << "Input numbers of CSs: " << endl;
                for (int i = 0; i < n; ++i) {
                    z = get_correct(1, int(cs_map.size()));
                    if (cs_map.find(z) != cs_map.end())
                        idcs.insert(z);
                }
                cout << "\nInput new number of working workshops: " << endl;
                for (auto& ci : idcs) {
                    b = get_correct(0, cs_map[ci].get_w());
                    cs_map.at(ci).set_w_r(b);
                }
                cout << "\nChanges applied" << endl;
            }
            if (d == 1) {
                idcs = search_Css(cs_map);
                if (idcs.size() != 0) {
                    cout << "\nInput new number of working works" << endl;
                    for (auto& ci : idcs) {
                        b = get_correct(0, cs_map[ci].get_w());
                        cs_map.at(ci).set_w_r(b);
                    }
                    cout << "\nChanges applied" << endl;
                }
            }
        }

        else if (ed == 0) {
            delete_css(cs_map);
        }
    }
    else
        cout << "There is no CS for edit!" << endl;
}

ostream& operator<<(ostream& out, unordered_set<int> s) {
    cout << "Free objects: ";
    for (auto& i : s)
        cout << i << " ";
    cout << endl;
    return out;
}

istream& operator >>(istream& in, All& gts) {
    All::System sys;
    cout << gts.cs_map;
    cout << "Choose CS_id on entrance: " << endl;
    sys.id_ent = get_correct(0, INT_MAX);
    sys.id_ent = gts.check_exist(sys.id_ent);
    sys.id_ent = gts.check_graph(sys.id_ent);
    cout << gts.cs_map;
    cout << "Choose CS_id on exit" << endl;
    sys.id_ex = get_correct(0, INT_MAX);
    while (sys.id_ex == sys.id_ent) {
        cout << "Error! Choose another CS to connect" << endl;
        sys.id_ex = get_correct(0, INT_MAX);
    }
    sys.id_ex = gts.check_exist(sys.id_ex);
    sys.id_ex = gts.check_graph(sys.id_ex);
    if (gts.check_used(sys.id_ent, sys.id_ex)) {
        cout << "Choose pipe's diameter from 500 to 1400: " << endl;
        double dia_pipe = get_correct(500.0, 1400.0);
        //cout<<gts.search_d(gts.p_map, dia_pipe);
        int k = gts.edge(dia_pipe);
        while (gts.p_map.find(k) == gts.p_map.end()) {
            cout << "There is no such pipe, 1.Choose another  2.create" << endl;
            int choice = get_correct(1, 2);
            if (choice == 2) {
                Pipe p;
                cin >> p;
                gts.p_map.insert({ p.get_pid(), p });
            }
            cout << "Choose pipe's diameter from 500 to 1400: " << endl;
            dia_pipe = get_correct(0.0, DBL_MAX);
            k = gts.edge(dia_pipe);
            cout << k<< endl;
        }
        sys.id_pip = k;

        gts.graph.insert({ sys.id, sys });
    }
    else {
        return in;
    }
    return in;
}
