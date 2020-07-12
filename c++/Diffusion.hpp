
#ifndef SRC_DIFFUSION_HPP_
#define SRC_DIFFUSION_HPP_
#include "Graph.hpp"
#include <algorithm>
class Diffusion{
public:
	int N,L; //size
	int D; //dimension
	Graph G; // The structure
	double density;
	int NOPI, NOPC; // num of particle initialized and num of particle currently for one particle because always n_A = n_B
	vector<int> occupationFA1, occupationFB1; //network1 at time t
	vector<int> occupationSA1, occupationSB1; //duplicates at time t+1

	vector<pair<int,double>> density_t_vec;

	Diffusion(int L, double density, int D);
	void mixed_init();
	void seperated_init();
	void move_F(); //move the first round
	void move_S(); //move the second and go back
	void run();
	void write_data(int Test_num, string where_to);

};
Diffusion::Diffusion(int L1,double dens, int D1){ //constructor
	L = L1;
	D = D1;
	N = pow(L,D);
	density = dens;
	NOPI = int(N*dens);
	NOPC = int(N*dens);
	
	G.setGraph(N);
	G.createGraphSLFullnD(L, D);
	G.testConnectivity();

	occupationFA1 = vector<int>(N, 0);
	occupationFB1 = vector<int>(N, 0);
	occupationSA1 = vector<int>(N, 0);
	occupationSB1 = vector<int>(N, 0);
	
	//choose initial conditions
	//mixed_init();
	seperated_init();

}

void Diffusion::mixed_init(){
	int i=0,t;
	while(i<N*density){
		t = G.gen()%(N);
		if(G.connected[t]){
			occupationFA1[t]++;
			i++;
		}
	}

	i=0;
	while(i<N*density){
		t = G.gen()%(N);
		if(G.connected[t]){
			occupationFB1[t]++;
			i++;
		}
	}	
}
void Diffusion::seperated_init(){
	int i=0,t;
	while(i<N*density){
		if(D == 1)
			t = G.gen()%int((L/2));
		if(D == 2)
			t = G.gen()%int((L/2)) + L*(G.gen()%int(L));
		if(D == 3)
			t = G.gen()%int((L/2)) + L*(G.gen()%int(L)) + L*L*(G.gen()%int(L));
		if(G.connected[t]){
			occupationFA1[t]++;
			i++;
		}
	}

	i=0;
	while(i<N*density){
		if(D == 1)
			t = L/2+G.gen()%int((L/2));
		if(D == 2)
			t = L/2+G.gen()%int((L/2)) + L*(G.gen()%int(L));
		if(D == 3)
			t = L/2+G.gen()%int((L/2)) + L*(G.gen()%int(L)) + L*L*(G.gen()%int(L));
		if(G.connected[t]){
			occupationFB1[t]++;
			i++;
		}
	}	
}
void Diffusion::move_F(){

	int size, idx, target;
	for(int i=0;i<N;i++){

		for(int j=0;j<occupationFA1[i];j++){ //first A move, therefor no need to check if B is there!!!
			size = G.v[i].size();
			idx  = G.gen()%size;
			target = G.v[i][idx];
			occupationSA1[target]++;
		}

		occupationFA1[i] = 0;  //now its empty!

	}
	for(int i=0;i<N;i++){

		for(int j=0;j<occupationFB1[i];j++){ //now B moves, need to check if A is on the site!!!
			size = G.v[i].size();
			idx  = G.gen()%size;
			target = G.v[i][idx];
			if(occupationSA1[target] >0){
				occupationSA1[target]--;
				NOPC--;
			}
			else
				occupationSB1[target]++;
		}


		occupationFB1[i] = 0;
	}
}

void Diffusion::move_S(){

	int size, idx, target;
	for(int i=0;i<N;i++){

		for(int j=0;j<occupationSA1[i];j++){ //first A move, therefore no need to check if B is there!!!
			size = G.v[i].size();
			idx  = G.gen()%size;
			target = G.v[i][idx];
			occupationFA1[target]++;
		}

		occupationSA1[i] = 0;  //now its empty!

	}
	for(int i=0;i<N;i++){

		for(int j=0;j<occupationSB1[i];j++){ //now B moves, need to check if A is on the site!!!
			size = G.v[i].size();
			idx  = G.gen()%size;
			target = G.v[i][idx];
			if(occupationFA1[target] >0){
				occupationFA1[target]--;
				NOPC--;
			}
			else
				occupationFB1[target]++;
		}


		occupationSB1[i] = 0;
	}
}
void Diffusion::run(){
	bool flag = true;
	int t = 0;
	while(t<1000000 and NOPC > 1){
		
		if(t%10000 == 0)
			cout<<"t="<<t<<"  NOPC="<<NOPC<<endl;
		if(t%1== 0)
			density_t_vec.push_back(make_pair(t,(double)NOPC/N));
		if(flag){
			move_F();
			flag = false;
		}
		else{
			move_S();
			flag = true;
		}
		t++;
	}
}
void Diffusion::write_data(int Test_num, string where_to){
	ofstream dataInfo;
	stringstream ss;
	const char* cfile;
	string fileR = where_to;
	ss<<Test_num;
	fileR = fileR + ss.str() + ".txt";
	cfile = fileR.c_str();
	dataInfo.open(cfile, ofstream::out);
	for(int i=0; i<density_t_vec.size();i++)
	{
		dataInfo<<density_t_vec[i].first<<"	"<<density_t_vec[i].second<<endl;
	}
	dataInfo.close();
}



#endif /* SRC_DIFFUSION_HPP_ */
