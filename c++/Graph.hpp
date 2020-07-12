

#ifndef SRC_MYGRAPH_HPP_
#define SRC_MYGRAPH_HPP_


using namespace std;
#include <queue>
typedef std::mersenne_twister_engine< uint32_t, 32, 351, 175, 19, 0xccab8ee7, 11, 0xffffffff, 7, 0x31b6ab00, 15, 0xffe50000, 17, 1812433253 > mt11213b;

class Graph {
public:
        int n;
        vector<int> components; //used for testconnectivity
        vector<vector<int> > v; //adjacency list
        vector<int> active;
        vector <int> connected;	//connected to the giant

        mt11213b gen;

        Graph();
        ~Graph();
        void setGraph(int size);
        bool isConnected(int, int);
        void addEdge(int , int );
        int getDegree(int);
		void createGraphSLFullnD(int, int );
        int testConnectivity();
};
Graph::Graph() {n=0;} // constructor
void Graph::setGraph(int size) { //this function create the graph
      if (size < 2) n = 2;
      else n = size;
      v.resize(n);
      connected.resize(n);
      components.resize(n);
      active = vector<int>(n,1);
      gen.seed(time(0));
}
Graph::~Graph() { //destructor
  for(int i=0;i<v.size();i++)
	  v[i].clear();
}
bool Graph::isConnected(int u1, int u2) { //check if u1 and u2 are connected
    if(active[u1]==0||active[u2]==0)
    	return false;
    for(int i=0;i<v[u1].size();i++)
    	if(v[u1][i]==u2)
    		return true;
    return false;
}
inline void Graph::addEdge(int u1, int u2) { // add(u1, u2) edge
    v[u1].push_back(u2);
    v[u2].push_back(u1);
}
int Graph::getDegree(int u) //get the degree of node u
{
	return v[u].size();
}

void Graph::createGraphSLFullnD(int L, int D){ // create a grid with linear size L and dimension D
	vector<int> coordinates;
	coordinates.resize(D);
	if(pow(L,D) != n)
		L = L+1;

	for(int i=0;i<pow(L,D);i++)
	{
	    int temp = i;
	    int target = 0;
	    for(int j = 0; j < D; j++){
		coordinates[j] = temp%L;
		temp = int(temp/L);
	    }
	    for(int j = 0; j < D; j++){
		if(coordinates[j] == L-1)
		 	addEdge(i,i - (L-1)*pow(L,j));
		else
			addEdge(i,i + pow(L,j));
	    }
	}
}
int Graph::testConnectivity() // Test the connectivity of the graph and saparate it to components (use BFS algorithm)
{
	queue<int> Q;
	int j, size,expCount=0, cluster_id=0, giant_size=0, giant_id;
	int *explored = new int[n];//0-white, 1-grey, 2-black
	vector<int>* sources = new vector<int>;

	bool flag = true;

	for (int i = 0; i < n; ++i) //initialization explored
	{
		    if (active[i]==0)
		    {
		    	explored[i] = 2;
		    	expCount++;
		    	components[i]=cluster_id++;
		    }
		    else if(getDegree(i)==0)
		    {
		    	explored[i] = 2;
		    	expCount++;
		    	components[i]=cluster_id++;
		    }
		    else
		    	explored[i] = 0;
	}
	j=0;
	cluster_id--;
	while(expCount<n &&flag)
	{
	while(explored[j]!=0) //find a source for BFS algorithm
	{
	    j++;
	}
	cluster_id++;
	Q.push(j);
	components[j]=cluster_id;
	sources->push_back(j);
	size=1;
	explored[j] = 1;
	expCount++;

	while (!Q.empty()) {

	    int u = Q.front();
	    Q.pop();
	    explored[u] = 2;

	for(int i=0;i<v[u].size();i++)
	{
	    if(explored[v[u][i]]==0)
	    {
	    	size++;
	    	Q.push(v[u][i]);
	    	components[v[u][i]] = cluster_id;
	    	explored[v[u][i]] = 1;
	    	expCount++;
	    }
	}

	}
	if(size>giant_size)
	{
		giant_size=size;
		giant_id=cluster_id;
	}
	}
	for(int k=0;k<n;k++)
	{
		if(components[k] == giant_id)
			connected[k] = 1;
		else
			connected[k] = 0;
	}

	delete [] explored;
	return giant_size;
}
#endif
