#include <iostream>
#include <bitset>

using namespace std;

void generate(int, int);
void list();
void rank();
void unrank();
void previous();

const int puissance=4;
const int count = 2 << puissance ;

bitset<puissance> solutions [count];

void generate(int run, int endroit,bitset<puissance> acc){
	if (run == 0 ){
		solutions[endroit]=acc;
		cout << acc << endl ;
	}
	else {

		bitset<puissance> un = acc;
		un[run-1]=1;

		generate(run-1, endroit, acc);
		generate(run-1, endroit+ (puissance-run) << 1, un);
	}
}

void list(){

}

void rank(){

}

void unrank(){

}

void previous(){

}

int main(int argc, char const *argv[])
{
	bitset<puissance> tmp;
	generate(puissance, 0, tmp);
	return 0;
}