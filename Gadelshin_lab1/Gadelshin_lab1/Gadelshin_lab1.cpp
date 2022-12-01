#include <iostream>
#include <fstream>
#include <unordered_map>
#include "Pipe.h"
#include "CS.h"
#include "Utils.h"
#include "Gas_transport.h"

using namespace std;

int main() {
    Pipe P;
    CS cs;
    All new_c;
   int num_option(-1);
    while (num_option) {
        cout << "\nChoose: \n 1.Add pipe 2.Add CS 3.Show objects" <<
            " 4.Edit Pipe 5.Edit CS 6.Save 7.Load 8.Filter_pipe 9.Filter_CS 10.Create Gas-Transport net 0.Exit\n";
        num_option = get_correct(0, 10);
        switch (num_option)    {
        case 1: {
            cin >> P;
            new_c.p_map.insert({P.get_pid(), P });
            break;
            }
        case 2: {
            cin >> cs;
            new_c.cs_map.insert({cs.get_csid(), cs });
            break;
            }
        case 3: {
            P.show_pipe(new_c.p_map);
            cs.show_cs(new_c.cs_map);
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
            new_c.load_file(new_c.p_map, new_c.cs_map);
            P.max_id = new_c.p_map.size();
            cs.max_idd = new_c.cs_map.size();
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
            cout << "Choose: 1.Connect  0.Disconnect" << endl;
            int chose = get_correct(0, 1);
            if (chose == 1) {
                if ((new_c.cs_map.size() < 2) or (new_c.p_map.size() < 1))
                    cout << "There is no enough obj to create system!" << endl;
                else
                    cin >> new_c;

            }
            else
                if (new_c.graph.size() != 0)
                    cout << "\nProverim pozhe";
                else
                    cout << "There is no systems!"<<endl;

            for (auto& [i, j] : new_c.graph)
                cout << i << ") " << j.id_ent << " " << j.id_ex << " " << j.id_pip << endl;

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
