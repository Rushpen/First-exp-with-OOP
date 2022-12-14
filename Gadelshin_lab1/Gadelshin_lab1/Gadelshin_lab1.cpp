#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
#include "Gas_transport.h"

using namespace std;

int main() 
{
    GTS new_c;

   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Add pipe 2.Add CS 3.Show objects" <<
            " 4.Edit Pipe 5.Edit CS 6.Save 7.Load 8.Filter_pipe 9.Filter_CS 10.Gas-Transport net 0.Exit\n";
        num_option = get_correct(0, 10);
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
            new_c.create_graph();
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

