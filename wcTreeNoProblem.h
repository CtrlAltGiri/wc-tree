#include "modules.h"

int checkIfTrue(NODE, unsigned long int);
int checkIfTrueL(LNODE root, unsigned long int no){
	if(root == NULL)
		return 0;

	checkIfTrue(root -> right, no);
	root -> val = (double)((long int)(root -> val * L)) / (double)no;
	checkIfTrueL(root -> Lright, no);
	checkIfTrueL(root -> Lchild, no);
}


int checkIfTrue(NODE root, unsigned long int no){
	if(root == NULL)
		return 0;
	checkIfTrue(root -> child, no);
	checkIfTrue(root -> right, no);
	checkIfTrueL(root -> Lchild, no);
	checkIfTrueL(root -> Lright, no);
}


void replaceAllLNodes(unsigned long int no){
	NODE traverse = start;
	if(traverse -> child)
		checkIfTrue(traverse -> child, no);
	else
		checkIfTrueL(traverse -> Lchild, no);
}


LNODE createLNode(unsigned long int no){

	if(no > L){
		replaceAllLNodes(no);
		L = no;
		LNODE newNode = (LNODE)malloc(sizeof(struct Lnode));
		newNode -> val = 1;
		newNode -> qty = 1;
		newNode -> right = NULL;
		newNode -> Lright = newNode -> Lchild = NULL;
		return newNode;
	}

	else{
		LNODE newNode = (LNODE)malloc(sizeof(struct Lnode));
		newNode -> val = (double)((double)no / (double)L);
		newNode -> qty = 1;
		newNode -> right = NULL;
		newNode -> Lright = newNode -> Lchild = NULL;
		return newNode;
	}

}

void insertIntoTree(NODE root, unsigned int no){
	if(root -> child == NULL && root -> Lchild == NULL){
		// first value enter
		NODE newNode = (NODE)malloc(sizeof(struct node));
		newNode -> val = no;
		newNode -> qty = 1;
		newNode -> child = newNode -> right = NULL;
		newNode -> Lchild = newNode -> Lright = NULL;

		root -> child = newNode;
	}

	else{
		NODE traverse = NULL, prev = root;
		LNODE Ltraverse = NULL, Lprev = NULL;

		if(root -> child)
			traverse = root -> child;
		else
			Ltraverse = root -> Lchild;

		int complete = 0, finalNo;

		while(!complete){

			if( (traverse) && (!(traverse -> val % no) || !(no % traverse -> val)) ){

				while((traverse -> child != NULL && !(no % traverse -> val)) && (traverse -> val % no) && !(traverse -> val == no)){ //major key alert
					prev = traverse;
					traverse = traverse -> child;
					Ltraverse = NULL;
				}

				if(traverse -> val == no){ // 1. Node already present
					traverse -> qty++;
					complete = 1;
					return;
				}

				if( !(no % traverse->val) && traverse -> Lchild && isDivisible(no, traverse -> Lchild) == 1){
					prev = traverse;
					Ltraverse = traverse -> Lchild;
					traverse = NULL;
					continue;
				}
				// 3 cases
				int divisible = !(traverse -> val % no) || !(no % traverse -> val);

				if(traverse -> val == no){ // 1. Node already present
					traverse -> qty++;
					complete = 1;
					return;
				}

				else if(divisible){ // 2. divisble

					NODE newNode = (NODE)malloc(sizeof(struct node));
					newNode -> val = no;
					newNode -> qty = 1;
					newNode -> child = newNode -> right = NULL;
					newNode -> Lchild = newNode -> Lright = NULL;

					LNODE newNodeL;

					if(no > traverse -> val){
						if(!traverse -> Lchild){
							traverse -> child = newNode;
							return;
						}
						else{
							Ltraverse = traverse -> Lchild;
							prev = traverse;
							traverse = NULL;
							continue;
						}
					}
					else{
						prev -> Lchild = NULL;
						prev -> child = newNode;
						newNode -> child = traverse;
						Ltraverse = NULL;

						moveNonFactorsRight(traverse, Ltraverse, newNode, newNodeL, no);
						return;
					}
				}
				else{
					continue; // 3. not divisible
				}
			}

			else if(Ltraverse && isDivisible(no, Ltraverse) == 1){

				NODE newNode = (NODE)malloc(sizeof(struct node));
				newNode -> val = no;
				newNode -> qty = 1;
				newNode -> child = newNode -> right = NULL;
				newNode -> Lchild = newNode -> Lright = NULL;
				LNODE newNodeL = NULL;

				prev -> Lchild = NULL;

				prev -> child = newNode;
				newNode -> Lchild = Ltraverse;
				traverse = NULL;

				moveNonFactorsRight(traverse, Ltraverse, newNode, newNodeL, no);

				complete = 1;
			}

			else{ // When not divisible, move to the right

				int flag = -1;
				while( flag == -1 && ((traverse && (traverse -> right || traverse -> Lright)) || (Ltraverse && (Ltraverse -> right || Ltraverse -> Lright))) ){

					if(traverse && traverse -> right){
						if(traverse -> right -> val == no){
							traverse -> right -> qty++;
							flag = 0;
							complete = 1;
							return;
						}
						else if(!(traverse -> right -> val % no)){
							flag = 1;
							Ltraverse = NULL;
							break;
						}
						else if(!(no % traverse -> right -> val)){
							flag = 2;
							Ltraverse = NULL;
							break;
						}

						traverse = traverse -> right;
						Ltraverse = NULL;
					}

					else if(traverse && traverse -> Lright){

						if(isDivisible(no, traverse -> Lright) == 1){
							flag = 1;
							Ltraverse = NULL;
							break;
						}

						Ltraverse = traverse -> Lright;
						traverse = NULL;
					}

					else if(Ltraverse -> right){

						if(Ltraverse -> right -> val == no){
							Ltraverse -> right -> qty++;
							flag = 0;
							complete = 1;
							return;
						}
						else if(!(Ltraverse -> right -> val % no)){
							flag = 1;
							traverse = NULL;
							break;
						}
						else if(!(no % Ltraverse -> right -> val)){
							flag = 2;
							traverse = NULL;
							break;
						}

						traverse = Ltraverse -> right;
						Ltraverse = NULL;
					}

					else{
						if(isDivisible(no, Ltraverse -> Lright) == 1){
							flag = 1;
							traverse = NULL;
							break;
						}

						traverse = NULL;
						Ltraverse = Ltraverse -> Lright;
					}
				}

				if(flag){

					NODE newNode = (NODE)malloc(sizeof(struct node));
					newNode -> val = no;
					newNode -> qty = 1;
					newNode -> child = newNode -> right = NULL;
					newNode -> Lchild = newNode -> Lright = NULL;
					LNODE newNodeL;

					switch(flag){
						case -1:
							if(traverse)
								traverse -> right = newNode;
							else
								Ltraverse -> right = newNode;
							complete = 1;
							break;

						case 1:
							if(traverse){
								if(traverse -> right){
									newNode -> child = traverse -> right;
									traverse -> right = newNode;
									traverse = newNode -> child;
									Ltraverse = NULL;
								}
								else{
									newNode -> Lchild = traverse -> Lright;
									traverse -> right = newNode;
									traverse -> Lright = NULL;
									Ltraverse = newNode -> Lchild;
									traverse = NULL;
								}
							}

							else{
								if(Ltraverse -> right){
									newNode -> child = Ltraverse -> right;
									Ltraverse -> right = newNode;
									traverse = newNode -> child;
									Ltraverse = NULL;
								}
								else{
									newNode -> Lchild = Ltraverse -> Lright;
									Ltraverse -> right = newNode;
									Ltraverse -> Lright = NULL;
									Ltraverse = newNode -> Lchild;
									traverse = NULL;
								}
							}

							moveNonFactorsRight(traverse, Ltraverse, newNode, newNodeL, no); //traverse, newNode, no.
							complete = 1;
							break;

						case 2:
								if(traverse)
									prev = traverse -> right;
								else
									prev = Ltraverse -> right;

								if(!(prev -> child) && !(prev -> Lchild)){
									prev -> child = newNode;
									return;
								}
								else if(prev -> child){
									traverse = prev -> child;
									Ltraverse = NULL;
								}

								else if(prev -> Lchild){
									traverse = NULL;
									Ltraverse = prev -> Lchild;
								}

								if(newNode)
									free(newNode);
								if(newNodeL)
									free(newNodeL);

								continue;
					}
				}
			}
		}
	}
}

void insertIntoTreeLNode(NODE root, unsigned long int no){

	if(root -> child == NULL && root -> Lchild == NULL){
		// first value enter
		LNODE newNode = createLNode(no);

		root -> Lchild = newNode;
	}

	else{
		NODE traverse = NULL, prev = root;
		LNODE Ltraverse = NULL, Lprev = NULL;

		if(root -> child)
			traverse = root -> child;
		else
			Ltraverse = root -> Lchild;

		int complete = 0, finalNo;

		while(!complete){

			if( ((traverse) && (!(traverse -> val % no) || !(no % traverse -> val))) || ((Ltraverse) && isDivisible(no,Ltraverse) ) ){

					while(traverse && (traverse -> child != NULL && !(no % traverse -> val)) && (traverse -> val % no) && !(traverse -> val == no)){ //major key alert
						prev = traverse;
						traverse = traverse -> child;
						Ltraverse = NULL;
					}

					int divisible;

					if(traverse)
						divisible = !(no % traverse -> val);
					else
						divisible = isDivisible(no, Ltraverse);

					if(divisible == -1){ // 1. Node already present
							Ltraverse -> qty++;
							complete = 1;
							return;
						}


					while( (traverse && isDivisible(no, traverse -> Lchild) == 2) || (Ltraverse && isDivisible(no, Ltraverse -> Lchild) == 2) ){
						if(traverse){
							prev = traverse;
							Lprev = NULL;
							Ltraverse = traverse -> Lchild;
							traverse = NULL;
						}
						else{
							Lprev = Ltraverse;
							prev = NULL;
							Ltraverse = Ltraverse -> Lchild;
						}
					}
					// 3 cases

					if(traverse)
						divisible = !(no % traverse -> val);
					else{
						divisible = isDivisible(no, Ltraverse);
						if(divisible){
							if(divisible != -1){
								if(divisible == 1)
									divisible = 2;
								else
									divisible = 1;
							}
						}
					}

					if(divisible){ // 2. divisble

						if(divisible == -1){ // 1. Node already present
							Ltraverse -> qty++;
							complete = 1;
							return;
						}

						NODE newNode = NULL;
						LNODE newNodeL = createLNode(no);


						if(divisible == 1){
							if(traverse && !traverse -> Lchild)
								traverse -> Lchild = newNodeL;
							else if(traverse && traverse -> Lchild){
								Ltraverse = traverse -> Lchild;
								prev = traverse;
								Lprev = NULL;
								traverse = NULL;
								continue;
							}
							else if(Ltraverse && Ltraverse -> Lchild){
								Lprev = Ltraverse;
								Ltraverse = Ltraverse -> Lchild;
								traverse = NULL;
								prev = NULL;
								continue;
							}
							else
								Ltraverse -> Lchild = newNodeL;
							return;
						}

						else{
							if(prev){
								prev -> child = NULL;
								prev -> Lchild = newNodeL;
							}
							else{
								Lprev -> Lchild = newNodeL;
							}

							newNodeL -> Lchild = Ltraverse;

							moveNonFactorsRight(traverse, Ltraverse, newNode, newNodeL, no);
							complete = 1;
						}
					}
					else{
						continue; // 3. not divisible
					}
			}

			else{ // When not divisible, move to the right

				int flag = -1;
				while( flag == -1 && ( (traverse && (traverse -> right || traverse -> Lright) ) || (Ltraverse && (Ltraverse -> right || Ltraverse -> Lright))) ){

					if(traverse && traverse -> right){

						if(!(no % traverse -> right -> val)){
							flag = 2;
							Ltraverse = NULL;
							break;
						}

						traverse = traverse -> right;
						Ltraverse = NULL;
					}

					else if(traverse && traverse -> Lright){

						if(isDivisible(no, traverse -> Lright) == -1){
							traverse -> Lright -> qty++;
							return;
						}

						if(isDivisible(no, traverse -> Lright) == 1){
							flag = 1;
							Ltraverse = NULL;
							break;
						}
						else if(isDivisible(no, traverse -> Lright) == 2){
							flag = 2;
							Ltraverse = NULL;
							break;
						}
						Ltraverse = traverse -> Lright;
						traverse = NULL;
					}

					else if(Ltraverse -> right){

						if(!(no % Ltraverse -> right -> val)){
							flag = 2;
							traverse = NULL;
							break;
						}

						traverse = Ltraverse -> right;
						Ltraverse = NULL;
					}

					else{
						if(isDivisible(no, Ltraverse -> Lright) == -1){
							Ltraverse -> Lright -> qty++;
							return;
						}

						if(isDivisible(no, Ltraverse -> Lright) == 1){
							flag = 1;
							traverse = NULL;
							break;
						}
						else if(isDivisible(no, Ltraverse -> Lright) == 2){
							flag = 2;
							traverse = NULL;
							break;
						}

						Ltraverse = Ltraverse -> Lright;
						traverse = NULL;
					}
				}

				if(flag){

					NODE newNode = NULL;
					LNODE newNodeL = createLNode(no);

					switch(flag){
						case -1:
							if(traverse)
								traverse -> Lright = newNodeL;
							else
								Ltraverse -> Lright = newNodeL;
							complete = 1;
							break;

						case 1:

								if(traverse && traverse -> Lright){
									newNodeL -> Lchild = traverse -> Lright;
									traverse -> Lright = newNodeL;
									traverse -> right = NULL;
									traverse = NULL;
									Ltraverse = newNodeL -> Lchild;
								}
								else if(Ltraverse && Ltraverse -> Lright){
									newNodeL -> Lchild = Ltraverse -> Lright;
									Ltraverse -> Lright = newNodeL;
									Ltraverse -> right = NULL;
									traverse = NULL;
									Ltraverse = newNodeL -> Lchild;
								}

								moveNonFactorsRight(traverse, Ltraverse, newNode, newNodeL, no); //traverse, newNode, no.
								complete = 1;
								break;

						case 2:
								if(traverse){
									if(traverse -> Lright){
										Lprev = traverse -> Lright;
										prev = NULL;
									}
									else{
										prev = traverse -> right;
										Lprev = NULL;
									}
								}
								else{
									if(Ltraverse -> right){
										prev = Ltraverse -> right;
										Lprev = NULL;
									}
									else{
										Lprev = Ltraverse -> Lright;
										prev = NULL;
									}
								}

								if(Lprev){
									if(Lprev -> Lchild){
										Ltraverse = Lprev -> Lchild;
										traverse = NULL;
									}
									else{
										Lprev -> Lchild = newNodeL;
										return;
									}
								}

								else{
									if(prev -> child){
										traverse = prev -> child;
										Ltraverse = NULL;
									}
									else if(prev -> Lchild){
										Ltraverse = prev -> Lchild;
										traverse = NULL;
									}
									else{
										prev -> Lchild = newNodeL;
										return;
									}
								}
								free(newNodeL);
								continue;
					}
				}
			}
		}
	}

}

int main(){

	printf("Enter the number of rows: ");
	scanf("%u", &rows);
	printf("Enter the lower bound: ");
	scanf("%u", &lowerBound);
	printf("Enter the upper bound: ");
	scanf("%u", &upperBound);

	NODE root;
	root = (NODE)malloc(sizeof(struct node));
	root -> val = 0;
	root -> qty = 0;
	root -> child = root -> right = NULL;

	start = root;
	// reading all the primes.
	allPrimes = (int*)malloc(limitPrime * sizeof(int));
	FILE *fp = fopen(primeFile, "r");
	char *line = (char*)malloc(sizeof(char) * 20);

	int x = 0;
	while(x < limitPrime){
		fgets(line, 20000, fp);
		const char* token;
		token = strtok(line, ",");
		allPrimes[x++] = atoi(token);
	}
	free(line);

         clock_t start, end;
         double cpu_time_used;

	start = clock();

	//reading the data
	int *data = (int*)malloc(sizeof(int) * maxCols);

	int cols;
	unsigned int no;
	FILE* stream = fopen(fileName, "r");
	int i = 0, j;
    	line = (char*)malloc(sizeof(char) * 10000);

	//fgets(line, 10000, stream);  // removes first line from the reading

	int mainI = 0;

	for(int i = 0; i < rows; i++){

		if(fgets(line, 10000, stream) == NULL)
			break;
		cols = 0;
		char* tmp = strdup(line);

		const char* tok;
		if(!SKIP){
	    		for (tok = strtok(tmp, ","); tok && *tok; tok = strtok(NULL, ",\n")){
					data[cols++] = allPrimes[atoi(tok)];
			}
		}
		else{
			tok = strtok(tmp, ",");
			for (tok = strtok(NULL, ",\n"); tok && *tok; tok = strtok(NULL, ",\n")){
					data[cols++] = allPrimes[atoi(tok)];
			}
		}


       		free(tmp);

			if(i == 320){				// i - 1 for terminal. mainI - 1 from excel file.
				printf("DAMN");
			}



		no = 1;
		unsigned long int x = 1, y;
		for(int j = 0; j < cols; j++){

			if(INT_MAX / no > data[j])
				no *= data[j];
			else{
				x = no;
				for(int k = j; k < cols; k++){
					if(INT_MAX_FINAL / x > data[k])
						x *= data[k];
					else{
						no = 0;
						break;
					}
				}


				if(no)
					insertIntoTreeLNode(root, x);
				else
					i--;

				//else
					//printf("DROPPED row %d\n", i);
				y = x;
				x = 0;
				break;
			}
		}
		if(x){
			insertIntoTree(root, no);
			insertedRows++;
			//printf("INSERTED %d\n", i);
		}
		else if(no){
			//printf("L-INSERTED %d = %lu\n", i, y);
			//for(int i = 0; i < cols; i++)
			//	printf("%d, ", data[i]);
			//printf("\n");
			insertedRows++;
		}

		mainI++;

	}


	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("\nINSERTION: %lf seconds\n", cpu_time_used);

	upperBound = (upperBound * insertedRows) / 100;
	lowerBound = (lowerBound * insertedRows) / 100;

	initDiscovery();
	fclose(stream);
	if(root -> child)
		discover(root -> child);
	else if(root -> Lchild)
		discoverL(root -> Lchild);


	displayFrequentSets();

	end = clock();
	cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
	printf("INSERTION + MINING: %lf seconds\n\n", cpu_time_used);

	printf("Total Inserted Rows: %d\n", insertedRows);

	printf("Total Memory Usage : %lu bytes\n\n", memUsageTotal);

	printf("Number of LIST nodes : %lu \n", tempMem);

	printf("Actual I : %d\n\n", mainI);

}
