#include <iostream>
#include <bitset>
#include <vector>

using namespace std;

void generate(int, int);
void list();
int unrank();
int previous();
int next();

const int puissance=4;
const int count = 2 << puissance ;



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

void list(){

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
	if(reste == 0 ){
		return min; // we can return max, it's the same thing
	}
	else {
		if (elem[reste]){
			int bin = binomial(reste, un-1);
			return parcour(elem, reste-1, min+bin , max , zero, un-1);
		}
		else{
			int bin = binomial(reste, zero-1);
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

 	return parcour(elem, puissance, 0, binomial(puissance, puissance-c0), c0, puissance-c0);
}

int unrank(int i, int un){ 
	bitset<puissance> acc;
	int reste = puissance;
	int nbr_un = un;

	while(reste != 0){
		int pivot = binomial(reste, nbr_un);
		if (pivot > i )
		{
			acc[reste]=1;
			reste--;
			nbr_un--;
		}
		else{
			acc[reste]=0;
			reste--;
		}
	}

	return (int)(acc.to_ulong());
}

int previous(){

}

int next(){
	
}

int main(int argc, char const *argv[])
{
	bitset<puissance> test = bitset<puissance> (5);
	bitset<puissance> tmp;
	// generate(puissance, 0, tmp);
	cout << ranka(test) << endl ;
	affiche();
	return 0;
}