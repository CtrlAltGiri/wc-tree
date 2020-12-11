#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<limits.h>
#include<math.h>
#include<time.h>

#define MAX_LIMIT 20 // defines the maximum number of products in a particular order
#define HASH_VALUE 1000	// the hash value we gon divide by
#define SECONDARY_HASH 7
#define fileName "Includes/test.csv"
#define primeFile "Includes/primes.csv"
#define limitPrime 20000
#define maxCols 750
#define INT_MAX_FINAL 9007199254740991
#define SKIP 0		// skip the first column


int *allPrimes;
unsigned long int L = INT_MAX;
int rows, upperBound, lowerBound;
unsigned long int memUsageTotal = 0, tempMem = 0;
unsigned int threshold;
int insertedRows = 0;


struct node;
struct Lnode;

typedef struct node{
	unsigned int val;
	unsigned int qty;
	struct node *child, *right;
	struct Lnode *Lchild, *Lright;

}*NODE;

NODE start;

typedef struct Lnode{
	double val;
	unsigned int qty;
	char L;
	struct node *right;
	struct Lnode *Lchild, *Lright;

}*LNODE;

struct list{
	unsigned long int val;
	int *itemSet;
	int noFactors;
	unsigned int qty;
};

struct list **LIST;
struct list *a;
unsigned int LIST_COUNTx, LIST_COUNTy;
unsigned long int MAX_LIMIT_ARRAY;

void initDiscovery(){
	MAX_LIMIT_ARRAY = pow(2,MAX_LIMIT);
	LIST = (struct list**)malloc(sizeof(struct list*) * rows);
	a = (struct list*) malloc(sizeof(struct list) * MAX_LIMIT_ARRAY);
	LIST[0] = a;
	LIST_COUNTx = 0, LIST_COUNTy = 0;
}


int isPrime(int x, int *mid){
	// binary search to check if x is a prime
	int beg = 0, end = limitPrime;

	while(beg <= end){
		*mid = (beg + end) / 2;
		if(allPrimes[*mid] == x)
			return 1;
		if(allPrimes[*mid] < x)
			beg = *mid + 1;
		else
			end = *mid - 1;
	}
	return 0;

}

void findPrimeFactors(unsigned long int finals, int *j, int *MulPrimes){
	//finals is the number you want to find PF for and it will be stored in allPrimes.
	*j = 0;
	//printf("%u factors - ", finals);
	for(int i = 0; i < limitPrime && finals > 1; i++){
		if(finals % allPrimes[i] == 0){
			finals /= allPrimes[i];
			MulPrimes[((*j)++)] = allPrimes[i];
			i--;
		}
	}
}

int addNode(unsigned long int val, unsigned int qty, int *itemSet, int count){

	for(int i = 0; i <= LIST_COUNTy; i++){
		for(int j = 0; j < LIST_COUNTx; j++){
			if(LIST[i][j].val == val){
				LIST[i][j].qty += qty;
				free(itemSet);
				return 1;
			}
		}
	}

	if(LIST_COUNTx == MAX_LIMIT_ARRAY - 1){
		LIST[++LIST_COUNTy] = (struct list*) malloc(sizeof(struct list) * MAX_LIMIT_ARRAY);
		LIST_COUNTx = 0;
	}
	LIST[LIST_COUNTy][LIST_COUNTx].val = val;
	LIST[LIST_COUNTy][LIST_COUNTx].qty = qty;
	LIST[LIST_COUNTy][LIST_COUNTx].itemSet = itemSet;
	LIST[LIST_COUNTy][LIST_COUNTx++].noFactors = count;

}


void powerSet(int *set, int set_size, int qty){
    unsigned long int pow_set_size = 1;
    unsigned long int prod = 1;
    int *sendTable;
    unsigned int howMany;
    unsigned long int counter, j;

    for(int i = 0; i < set_size; i++)
    	pow_set_size *= 2;

    for(counter = 1; counter < pow_set_size; counter++){
		sendTable = (int*)malloc(sizeof(int) * MAX_LIMIT);
		howMany = 0;
		prod = 1;
		for(j = 0; j < set_size; j++){
		  	if(counter & (1<<j)){
				prod *= set[j];
		    		sendTable[howMany++] = set[j];
			}
       		}
		sendTable = (int*)realloc(sendTable, sizeof(int) * howMany);
		for(int i = 0; i < howMany; i++){
			if(i != howMany && sendTable[i] == sendTable[i+1])
				break;
		}
		addNode(prod, qty, sendTable, howMany);
	}
}


void discover(NODE);

void discoverL(LNODE root){
	if(root == NULL)
		return;

	memUsageTotal += 29;
	tempMem++;

	int n, *mulPrimes = (int*)malloc(sizeof(int) * MAX_LIMIT);

	findPrimeFactors( (long int)(round(root -> val * L)), &n, mulPrimes);


	powerSet(mulPrimes, n, root -> qty);

	if(mulPrimes)
		free(mulPrimes);

	discover(root -> right);
	discoverL(root -> Lright);
	discoverL(root -> Lchild);
}

void discover(NODE root){
	if(root == NULL){
		return;
	}

	memUsageTotal += 32;
	tempMem++;

	int n, *mulPrimes = (int*)malloc(sizeof(int) * MAX_LIMIT);

	findPrimeFactors(root -> val, &n, mulPrimes);

	powerSet(mulPrimes,n, root -> qty);

	if(mulPrimes)
		free(mulPrimes);

	discover(root -> child);
	discover(root -> right);
	discoverL(root -> Lright);
	discoverL(root -> Lchild);
}


void displayFrequentSets(){

	int loc;
	FILE *fp = fopen("TABLE", "w+");

	for(int i = 0; i <= LIST_COUNTy; i++){
		for(int j = 0; j < LIST_COUNTx; j++){
			if(LIST[i][j].val == 0){
				return;
			}
			if(lowerBound <= LIST[i][j].qty && upperBound >= LIST[i][j].qty){
				fprintf(fp,"QTY = %u : ", LIST[i][j].qty);
				for(int k = 0; k < LIST[i][j].noFactors; k++){
					isPrime(LIST[i][j].itemSet[k], &loc);
					fprintf(fp, "%d, ", loc);
				}
				fprintf(fp, "\n");
			}
		}
	}
	fprintf(fp, "\n\nNOTE : THERE ARE FEW INACCURACIES DUE TO FLOATING POINT PRECISION\n");
	fclose(fp);
}
