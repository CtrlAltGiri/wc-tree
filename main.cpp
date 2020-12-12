#include <iostream>
#include <vector>
#include <map>
#include <fstream>

extern "C"{
    #include "wcTree.h"
}

using namespace std;

void mineTree(NODE, map<vector<int>, int>&);
void mineLTree(LNODE, map<vector<int>, int>&);

void findAllCombinations(vector<int> arr, int size, int reqLen, vector<vector<int>> &allCombinations, int start, int currLen, vector<bool> check){

	if(currLen > reqLen){
		return;
	}

 	if (currLen == reqLen){
        allCombinations.push_back({});
        int index = allCombinations.size() - 1;
		for(int i = 0; i < size; i++){
			if(check[i]){
				allCombinations[index].push_back(arr[i]);
			}
		}
		return;
	}

	if (start == size){
		return;
	}

	// For every index we have two options.
	// First is, we select it, means put true in check[] and increment currLen and start.
	check[start] = true;
	findAllCombinations(arr, size, reqLen, allCombinations, start + 1, currLen + 1, check);

	// Second is, we don't select it, means put false in check[] and only start incremented.
	check[start] = false;
	findAllCombinations(arr, size, reqLen, allCombinations, start + 1, currLen, check);
}

void powerSet(vector<int> mulPrimes, int n, int qty, map<vector<int>, int> &allCombinations){

    vector<vector<int>> allMulPrimeCombinations;
    for(int i = 1; i <= n; i++){
        vector<bool> check(n);
        findAllCombinations(mulPrimes, n, i, allMulPrimeCombinations, 0, 0, check);
    }

    for(int i = 0; i < allMulPrimeCombinations.size(); i++){
        allCombinations[allMulPrimeCombinations[i]] += qty;
    }
}

void findAllPrimeFactors(unsigned long int finals, int &j, vector<int> &MulPrimes){

	for(int i = 0; i < limitPrime && finals > 1; i++){
		if(finals % allPrimes[i] == 0){
			finals /= allPrimes[i];
			MulPrimes.push_back(allPrimes[i]);
			i--;
		}
	}
    j = MulPrimes.size();
}

void mineTree(NODE root, map<vector<int>, int> &allCombinations){
    if(root == NULL){
		return;
	}

    memUsageTotal += 32;
	tempMem++;

    int n;
    vector<int> mulPrimes;
	findAllPrimeFactors(root -> val, n, mulPrimes);

    powerSet(mulPrimes, n, root -> qty, allCombinations);

    mineTree(root -> child, allCombinations);
	mineTree(root -> right, allCombinations);
	mineLTree(root -> Lright, allCombinations);
	mineLTree(root -> Lchild, allCombinations);
}

void mineLTree(LNODE root, map<vector<int>, int> &allCombinations){
    if(root == NULL){
        return;
    }

    memUsageTotal += 29;
	tempMem++;

    int n;
    vector<int> mulPrimes;
	findAllPrimeFactors((unsigned long int)(round(root -> val * L)), n, mulPrimes);

    powerSet(mulPrimes,n, root -> qty, allCombinations);

    mineTree(root -> right, allCombinations);
	mineLTree(root -> Lright, allCombinations);
	mineLTree(root -> Lchild, allCombinations);
}

int main(){

    int rows, rareThreshold, freqThreshold, insertedRows = 0, freqRows, rareRows;
    map<vector<int>, int> allCombinations, freqTable, rareTable;
    vector<int> prevFactors;

    printf("Enter the number of rows: ");
	scanf("%u", &rows);
	printf("Enter the lower bound: ");
	scanf("%u", &rareThreshold);
	printf("Enter the upper bound: ");
	scanf("%u", &freqThreshold);
    cout << endl;

    clock_t start, end;
    double cpu_time_used;
	start = clock();

    // STEP 1: Construct the tree
    NODE root = wcTreeConstruction(rows, insertedRows);
    freqRows = (freqThreshold * insertedRows) / 100;
	rareRows = (rareThreshold * insertedRows) / 100;

    end = clock();
    cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
    printf("INSERTION: %lf seconds\n", cpu_time_used);

    // STEP 2: Mine the tree
    if(root -> child){
        mineTree(root -> child, allCombinations);
    }
    else{
        mineLTree(root -> Lchild, allCombinations);
    }

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;

	printf("INSERTION + MINING: %lf seconds\n\n", cpu_time_used);
    printf("Total Inserted Rows: %d\n", insertedRows);
    printf("Total Memory Usage : %lu bytes\n\n", memUsageTotal);
    printf("Number of nodes : %lu \n", tempMem);

    // Step 3: Printing the frequent items to a file
    ofstream frequent, rare;
    frequent.open("./output/frequent.txt");
    rare.open("./output/rare.txt");

    int primePos;
    for(auto i : allCombinations){
        if(i.second > freqRows){
            for(int j = 0; j < i.first.size(); j++){
                isPrime(i.first[j], &primePos);
                frequent << primePos << ',';
            }
            frequent << "COUNT = " << i.second << endl;
        }

        else if(i.second > rareRows && i.second < freqRows){
            for(int j = 0; j < i.first.size(); j++){
                isPrime(i.first[j], &primePos);
                rare << primePos << ',';
            }
            rare << "COUNT = " << i.second << endl;
        }
    }
    cout << endl << "Frequent and Rare Itemsets are generated in the output folder." << endl;
}
