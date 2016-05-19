#include <iostream>
#include <bitset>
#include <vector>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int puissance=4;
const int count = 2 << puissance-1 ;



vector<vector<bitset<puissance>>> solutions (puissance+1);

void affiche () {
	for ( std::vector<bitset<puissance>> elem : solutions){
		for (bitset<puissance> e : elem)
		{
			cout << e << endl ;
		}
	}
}

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

	// cout << " elem : " << elem << endl ;
	// for (int i = 0; i < puissance; ++i)
	// {
	// 	cout << " elem [" << i << "] : " << elem[i] << endl;
	// }
	// cout << " reste : " << reste << endl ;
	// cout << " min : " << min << endl ;
	// cout << " max : " << max << endl ;
	// cout << " zero : " << zero << endl ;
	// cout << " un : " << un << endl << endl << endl ;

	// works with the lexicographical order


 	if( !zero ){
		return min; 
	}
	else {
		if (elem[reste-1]){
			// cout << " passage vrai " << endl;
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

int unrank(int i, int un){ 
	i++;
	bitset<puissance> acc;
	int reste = puissance;

	while ( reste ){

		int pivot = binomial(reste-1, un);

		// cout << " reste : " << reste << endl;
		// cout << " pivot : " << pivot << endl;
		// cout << " i : " << i << endl;
		// cout << " acc " << acc << endl << endl << endl;


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

	// cout << " mot binaire : " << acc << endl ;

	return (int)(acc.to_ulong());
}

int previous(bitset<puissance> elem){

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

	// cout << "previous : " << elem << endl;

	return (int)(elem.to_ulong());
}

int next(bitset<puissance> elem){

	int prec = (int)(elem.to_ulong());

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

	// for (int i : uns)
	// {
	// 	cout << " pos : " << i << endl;
	// }

	for (int i : uns)
	{
		elem[i]=0;
		elem[c]=1;
		c++;
	}

	elem[pos1]=0;
	elem[pos1+1]=1;

	// cout << "next : " << elem << endl;

	int actuel = (int)(elem.to_ulong());

	// cout << " count " << count << " actuel : " << actuel << endl;

	if(actuel >= count){
		return prec;
	}
	else{
		return actuel;
	}

}

int aleatoire(int un){
	srand (time(NULL));

// rand() % 10 + 1;

	int r = rand() % (binomial(puissance, un));

	return unrank(r, un);
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

int main(int argc, char const *argv[])
{
	bitset<puissance> test = bitset<puissance> (0);
	bitset<puissance> tmp;
	// generate(puissance, 0, tmp);
	// cout << ranka(test) << endl;
	//cout << unrank(3,3) << endl;
	//affiche();
	// cout << next(test) << endl ;
	//list(1);
	list();
	//cout << next(test) << endl ;
	cout << aleatoire(2) << endl ;

	return 0;
}