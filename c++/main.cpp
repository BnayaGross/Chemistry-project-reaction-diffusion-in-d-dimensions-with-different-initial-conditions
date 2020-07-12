#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>
#include <string.h>
#include <cmath>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <bitset>
#include <stdexcept>
#include <exception>
#include <map>
#include <cassert>
#include <iomanip>
#include <limits>
#include <cmath>
#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <random>


#include "Graph.hpp"
#include "Diffusion.hpp"

using namespace std;




int main(int argc, char *argv[]){



	
	/*string where_to = "/home/bnaya/Desktop/chimestry/results/mixed/d1/";
	int num_rea = 100;
	int L = 100000;
	double density = 0.25;

	for(int i=0;i<num_rea;i++){
		Diffusion D(L,density,1);
		D.run();
		D.write_data(i,where_to);
	}*/
	
	
	// Here you need to choose the parametes for the simulations, L, density and the dimension
	string where_to = "/home/bnaya/Desktop/chimestry/results/sepereted/d3/";
	int num_rea = 100;
	int L = 47;
	double density = 0.25;

	for(int i=0;i<num_rea;i++){
		Diffusion D(L,density,3);
		D.run();
		D.write_data(i,where_to);
	}

}
