#include <iostream>
#include <bitset>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <set>

using namespace std;

const int puissance=4;
const int count = 2 << puissance-1 ;



vector<vector<bitset<puissance>>> solutions (puissance+1);

template <size_t puissance>


void generate(int run, int endroit,bitset<puissance> acc){
	if (run == 0 ){
		solutions[endroit].push_back(acc);
	}
	else {

		bitset<puissance> un = acc;
		un[run-1]=1;

		generate(run-1, endroit, acc);
		generate(run-1, endroit+1, un);
	}
}

int factorial(int n){
	int tmp = 1;

	for (int i = 1; i <= n; ++i)
	{
		tmp*=i;
	}

	return tmp;
}

int binomial(int n, int k){
	return factorial(n)/(factorial(k)*(factorial(n-k)));
}

int parcour(bitset<puissance> elem, int reste, int min, int max, int zero, int un){

	// works with the lexicographical order


 	if( !zero ){
		return min; 
	}
	else {
		if (elem[reste-1]){
			int bin = binomial(reste-1, un-1);
			return parcour(elem, reste-1, min+binomial(reste-1,un) , max , zero, un-1);
		}
		else{
			int bin = binomial(reste-1, zero-1);
			return parcour(elem, reste-1, min , max-bin , zero-1, un);
		}
				
	}
}

int ranka(bitset<puissance> elem){

	int c0 = 0 ;

	for (int i = 0; i < puissance ; i++){
		if ( elem[i] == 0) {
			c0++;
		}
	}

 	return parcour(elem, puissance, 1, binomial(puissance, puissance-c0), c0, puissance-c0);
}

bitset<puissance> unrank(int i, int un){ 
	i++;
	bitset<puissance> acc;
	int reste = puissance;

	while ( reste ){

		int pivot = binomial(reste-1, un);

		if (i <= pivot){
			reste--;
		}
		else{
			acc[reste-1]=1;
			i-=binomial(reste-1,un);
			un--;
			reste--;
			
		}
	}

	if ( un ){
		acc[0]=1;
	}

	return acc;
}

bitset<puissance> previous(bitset<puissance> elem){

	int pos1=-1;
	bool zero=false;
	std::vector<int> uns; 

	for (int i = 0 ; i < puissance; i++)
	{
		if (elem[i] && zero){
			pos1=i;
			break;
		}
		else if (elem[i]){
			uns.push_back(i);
		}
		else if (!elem[i]){
			zero=true;
		}
	}

	int c=1;

	for (int i : uns)
	{
		if ( (pos1-1) - i > 1 && !elem[pos1-c-1] ){

			elem[pos1-c-1]=1;
			elem[i]=0;
			c++;
		}
	}

	elem[pos1]=0;
	elem[pos1-1]=1;

	return elem;
}

bitset<puissance> next(bitset<puissance> elem){

	bitset<puissance> prec = elem;

	if(prec == 0){ // ugly
		return 0;
	}


	int pos1=-1;
	std::vector<int> uns; 
	bool un=false;

	for (int i = 0; i < puissance; i++)
	{
		if (elem[i] && !un){
			un=true;
			pos1=i;
		}
		else if (!elem[i] && un){
			break;
		}
		else if (elem[i]){
			uns.push_back(pos1);
			pos1=i;
		}

	}

	int c=0;

	for (int i : uns)
	{
		elem[i]=0;
		elem[c]=1;
		c++;
	}

	elem[pos1]=0;
	elem[pos1+1]=1;

	int actuel = (int)(elem.to_ulong());

	if(actuel >= count){
		return prec;
	}
	else{
		return elem;
	}
}

bitset<puissance> aleatoire(int un){
	srand (time(NULL));

	int r = rand() % (binomial(puissance, un));

	return bitset<puissance> (unrank(r, un));
}

void list(int i){
	bitset<puissance> premier (unrank(0,i));
	bitset<puissance> tmp;
	bitset<puissance> suivant;

	 do {

	 	tmp = premier;
	 	suivant = next(tmp);

	 	premier = suivant;
	 	cout << tmp << endl;

	 } while( suivant != tmp);
}

void list(){
	for (int i = 0; i <= puissance; i++)
	{
		list(i);
		cout << endl << endl ;
	}
}

bitset<puissance> superieur(vector<bitset<puissance>> ensemble){
	bitset<puissance> max (count - 1);
	bitset<puissance> tmp (0);

	for (bitset<puissance> elem : ensemble)
	{
		tmp = tmp | elem;

		if(tmp == max){
			return tmp;
		}
	}

	return tmp;
}

bitset<puissance> inferieur(vector<bitset<puissance>> ensemble){
	bitset<puissance> tmp (count - 1);
	bitset<puissance> min (0);

	for (bitset<puissance> elem : ensemble)
	{
		tmp = tmp & elem;
		if(tmp == min){
			return tmp;
		}
	}

	return tmp;
}

int main(int argc, char const *argv[])
{
	
	bitset<puissance> test = bitset<puissance> (0);
	bitset<puissance> tmp;
	 generate(puissance, 0, tmp);
	 cout << ranka(test) << endl;
	cout << unrank(3,3) << endl;
	cout << next(test) << endl ;
	list(1);
	list();
	cout << next(test) << endl ;
	cout << aleatoire(2) << endl ;
	

	///////////////// tests inf et sup /////////////////

	vector< bitset<puissance> > ensemble_test (
	{
	bitset<puissance> (1), 
	bitset<puissance> (5), 
	bitset<puissance> (9)
	});
	

	cout << " elem sup de l'ensemble test est " << superieur(ensemble_test) << endl;
	cout << " elem inf de l'ensemble test est " << inferieur(ensemble_test) << endl;

	return 0;
}