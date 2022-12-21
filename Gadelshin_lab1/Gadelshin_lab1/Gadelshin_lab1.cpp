#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
#include "Gas_transport.h"

using namespace std;

void create_graph(GTS& c);

int main() 
{
    GTS new_c;

   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Add pipe 2.Add CS 3.Show objects" <<
            " 4.Edit Pipe 5.Edit CS 6.Save 7.Load 8.Filter_pipe 9.Filter_CS 10.Gas-Transport net 11.Deikstra  0.Exit\n";
        num_option = get_correct(0, 11);
        switch (num_option)    {
        case 1: {
            cin >> new_c.p;
            new_c.p_map.insert({new_c.p.get_pid(), new_c.p });
            break;
            }
        case 2: {
            cin >> new_c.cs;
            new_c.cs_map.insert({new_c.cs.get_csid(), new_c.cs });
            break;
            }
        case 3: {
            new_c.p.show_pipe(new_c.p_map);
            new_c.cs.show_cs(new_c.cs_map);
            break;
            }
        case 4: {
            new_c.edit_pipe(new_c.p_map);
            break;
            }
        case 5: {
            new_c.edit_cs(new_c.cs_map);
            break;
            }
        case 6: {
            new_c.save_file(new_c.p_map, new_c.cs_map);
            break;
            }
        case 7: {
            new_c.load_file(new_c.p_map, new_c.cs_map, new_c.graph);
            new_c.p.max_id = new_c.p_map.size();
            new_c.cs.max_idd = new_c.cs_map.size();
            new_c.tr.max_ids = new_c.graph.size();
            break;
           }
        case 8: {
            new_c.search_pipes(new_c.p_map);
            break;
        }
        case 9: {
            new_c.search_Css(new_c.cs_map);
            break;
        }
        case 10: {
            create_graph(new_c);
            break;
        }
        case 11: {
            new_c.shortest_path();
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

void create_graph(GTS& c) {
    if (c.graph.size() != 0) {
        cout << "Existing systems: " << endl;
        for (auto& [i, j] : c.graph)
            cout << i << ") " << j.id_ent << " " << j.id_ex << " " << j.id_pip << endl;
    }

    cout << "\nChoose: 1.Connect  2. Topologic sort  0.Disconnect " << endl;
    int chose = get_correct(0, 2);
    if (chose == 1) {
        if ((c.cs_map.size() < 2) or (c.p_map.size() < 1))
            cout << "There is no enough obj to create system!" << endl;
        else
            cin >> c;
    }
    else if (chose == 2) {
        c.fill_graphl(c.graph);
        c.sort();
    }

    else if (chose == 0)
        if (c.graph.size() != 0) {
            cout << "Input number of CS on entrance: " << endl;
            int ent = get_correct(0, CS::max_idd);
            cout << "Input number of CS on exit" << endl;
            int ext = get_correct(0, CS::max_idd);
            if (ent == ext) {
                cout << "Choose another CS on exit!: ";
                ext = get_correct(0, CS::max_idd);
            }
            auto a = c.graph.cbegin();
            while (a != c.graph.cend()) {
                if (((*a).second.id_ent == ent) and ((*a).second.id_ex == ext)) {
                    c.graph.erase(a);
                    break;
                }
                a++;
            }

        }
        else
            cout << "There is no systems!" << endl;

}