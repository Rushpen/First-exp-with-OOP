#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include "Pipe.h"
#include "CS.h"
using namespace std;
class All
{
public:
	unordered_map <int, Pipe> p_map;
	unordered_map <int, CS> cs_map;

	int check_exist(int x);
	int check_graph(int x);
	int check_p(int x);
	bool check_used(int x, int y);
	bool check_i(int x);
	int edge(int x);


	void save_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map);
	void load_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map);
	unordered_set <int> search_pipes(unordered_map <int, Pipe>& p_map);
	unordered_set<int> search_d(unordered_map <int, Pipe>& p_map, double a);
	void delete_pipes(unordered_map <int, Pipe>& p_map);
	void edit_pipe(unordered_map <int, Pipe>& p_map);
	unordered_set <int> search_Css(unordered_map<int, CS>& cs_map);
	void delete_css(unordered_map<int, CS>& cs_map);
	void edit_cs(unordered_map<int, CS>& cs_map);

	struct System {
		static int max_ids;
		int id;
		System() {
			id = max_ids++;
		}
		int id_ent;
		int id_ex;
		int id_pip;
	};
	unordered_map <int, System> graph;
	friend istream& operator >> (istream& in, All& gts);
	friend ostream& operator<<(ostream& out, unordered_set<int> s);
};