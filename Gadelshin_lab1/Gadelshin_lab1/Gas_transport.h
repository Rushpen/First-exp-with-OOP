#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include "Pipe.h"
#include "CS.h"
using namespace std;
class GTS
{
public:
	Pipe p;
	unordered_map <int, Pipe> p_map;
	CS cs;
	unordered_map <int, CS> cs_map;

	int check_exist(int x);
	int check_graph(int x);
	int check_vert(int x);
	bool check_used(int x, int y);
	bool check_p_ex(int x);
	int def_pid(int x);
	bool check_del_cs(int x);



	struct Trio {
		static int max_ids;
		int id;
		Trio() {
			id = max_ids++;
		}
		int id_ent;
		int id_ex;
		int id_pip;
	};

	Trio tr;

	void save_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map);
	void load_file(unordered_map <int, Pipe>& p_map, unordered_map<int, CS>& cs_map, unordered_map<int, Trio>& gr);
	unordered_set <int> search_pipes(unordered_map <int, Pipe>& p_map);
	unordered_set<int> search_d(unordered_map <int, Pipe>& p_map, double a);
	void delete_pipes(unordered_map <int, Pipe>& p_map);
	void edit_pipe(unordered_map <int, Pipe>& p_map);
	unordered_set <int> search_Css(unordered_map<int, CS>& cs_map);
	void delete_css(unordered_map<int, CS>& cs_map);
	void edit_cs(unordered_map<int, CS>& cs_map);

	void topologicalSortUtil(int V, unordered_map<int, int>& visited, stack<int>& SortedV);
	void topologicalSort();


	vector<double>deikstra(std::vector<std::vector<double>> gr, int src);

	int min_lenght(const unordered_set<int>& spt_set, const vector<double>& distance);
	void shortest_path();

	unordered_map<int, Trio>graph;
	unordered_map <int, list<Trio>> Graph_l;

	void sort();
	void fill_graphl(unordered_map<int, Trio>& sys);




	friend istream& operator>>(istream& in, GTS& gts);
	friend ostream& operator<<(ostream& out, unordered_set<int> s);
	friend ifstream& operator >> (ifstream& fcin, GTS::Trio& tr);

};