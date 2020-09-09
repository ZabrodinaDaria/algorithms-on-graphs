#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

#define MAX_COST 1000000001

struct vertex{
	int cost;
	vertex(int c){cost = c;}
	vertex(){}
};

class Graph{
	int n; // Number of vertices ≤ 10^5
public: 
	long long TC; // total cost;
	vector<vertex> V;
	//vector<vector<bool> > E; //T — есть ребро, F — нет ребра
	vector<vector<int> > adj_list;
	void add_edge(pair<int, int> p){ 
		adj_list[p.first-1].push_back(p.second-1); adj_list[p.second-1].push_back(p.first-1); 
	}
	Graph(int nn);
	void BFS();
	void printV();
	//void printE();
	vector<int> neighbours(int v){ return adj_list[v]; };
};


/*vector<int> Graph::neighbours(int v){
	vector<int> neigh;
	for(size_t j = 0; j < n; ++j){
		if(E[v][j]){neigh.push_back(j);}
	}
	return neigh;
}*/

void Graph::BFS(){
	queue<int> q;
	vector<bool> touched(n, false);
	for(size_t i = 0; i < n; ++i){		
		int min_cost=0;
		if(!touched[i]){ //BFS starts here
			min_cost = V[i].cost; //MAX_COST;
			q.push(i);
			while( !q.empty() ){
				min_cost = min(min_cost, V[q.front()].cost);
				vector <int> neigh= neighbours(q.front());
				for(vector<int>::iterator it = neigh.begin(); it != neigh.end(); ++it){
					if(!touched[*it]){ q.push(*it); touched[*it] = true;}					
				}
				q.pop();
			}			
		}//BFS ends here
		TC += min_cost;
	}
}

struct DFS{
	Graph *G;
	int n; // Number of vertices
	int t; // Current time
	vector<int> d, f; // d — время открытия; f — время закрытия 
					// d[u] > 0 — вершина открыта.
	long long TC;
	int min_cur;
	
	DFS(Graph *GG){
		G = GG;
		n = G->V.size();
		t = 1; //!!!
		TC = 0;
		vector<int> v_empty(n, 0);
		d= v_empty; f = v_empty;
	}
	
	void search(); // Full DFS;
	void search(int v); // DFS starting from v;
	
};

void DFS::search(){
	for(size_t u = 0; u < n; ++u){
		if(d[u] == 0){ min_cur = MAX_COST; search(u); TC+= min_cur; }
	}
}

void DFS::search(int v){// v — input; u — local
	d[v] = t++;
	min_cur = min(min_cur, G->V[v].cost); // G->V <=> (*G).V
	vector<int> neigh = G->neighbours(v);
	for(vector<int>::iterator pu = neigh.begin() ; pu != neigh.end(); ++pu){
		if(d[*pu] == 0){ search(*pu); }
	}
	f[v] = t++;
}



Graph::Graph(int nn){
	n = nn;
	TC = 0;
	vector<vertex> VV(n, vertex());
	V=VV;
	vector<vector<int> > al(n);
	adj_list = al;
}

void Graph::printV(){
	for(size_t i = 0; i < n; ++i){
		cout << V[i].cost << " ";
	}
	cout << endl << endl;
}



int main (int argc, char const *argv[])
{
	//freopen("t3", "r", stdin);
	int n, m; // n — V, E — 
	
	cin >> n; cin >> m;
	
	Graph G(n);
	
	for(size_t i = 0; i < n; ++i){
		int cost;
		cin >> cost;
		vertex v(cost);
		G.V[i] = v;
	}
	//G.printV();
	
	
	for(size_t i = 0; i < m; ++i){
		pair<int, int> p;
		cin >> p.first; cin >> p.second;
		G.add_edge(p);
	}
	
	
	//G.BFS();
	//cout << G.TC << "\n";
	
	DFS dfs(&G);
	dfs.search();
	cout << dfs.TC << "\n";
	
	return 0;
}