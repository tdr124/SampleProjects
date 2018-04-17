/*Pr3.c
*Michael Briden 3,11,2018
*implements project 3. I added a find option and method.
* I do not check for correct string lengths so funny things
* may happen if the user enters a name length then enters a 
* string that has a length different from what they specified
*/

#include<stdio.h>
#include <string.h>
#include <stdlib.h>

char** add(int* size, char** nameArr, int nameLen);
int** addTransaction(int size, int** transArr, int numTrans, int *numTransactionsArr);
int* updateNumTransactionsArr(int size, int *numTransactionsArr, int *numTrans);
void displayFull(char **nameArr, int **transArr, int *numTransactionsArr, int size);
void displayCompact(char **nameArr, int **transArr, int *numTransactionsArr, int size);
void findName(char **nameArr, int **transArr, int *numTransactionsArr, int size, int nameLen);

int main(void){
	char slct = 'w';
	int next = 1;
	int size = 0;
	int tmp = -1;
	int numTrans = -1;
	int nameLen = -1;
	char **nameArr = (char**)malloc(sizeof(char*));
	nameArr[0] = (char*)malloc(sizeof(int));
	int **transArr = (int**)malloc(sizeof(int*));
	transArr[0] = (int*)malloc(sizeof(int));
	int *numTransactionsArr=(int*)malloc(sizeof(int));

	
	while( next == 1){
		tmp = -1;
	  	//prompt user for input
		slct = 'w';
	 	while((slct != 'a') && (slct != 'c') && (slct !='l') && (slct != 'q') && (slct != 's')){
	 	 	printf("a to add, l to list(full), c to list(compact), s to find costumer,");
			printf("quit\n" );
			printf("Enter your choice:");
			scanf("%c", &slct);
		
		}

		//display compact list
		if(slct == 'c'){
			printf("%c\n",slct);

			displayCompact(nameArr, transArr, numTransactionsArr, size);			

			slct = 'w';
		}
		//do add
		else if(slct == 'a'){
			printf("%c\n",slct);
		
			while(tmp != 2){
				printf("Enter the customer name length and number of items:");
				if(tmp == -1){
					tmp = scanf("%d%d",&nameLen, &numTrans);
					while(getchar() != '\n');
				}
				else{
					printf("\n Invalid entry, try again: ");
					tmp = scanf("%d%d",&nameLen, &numTrans);
					while(getchar() != '\n');
				}
			}

			//add user to name array and update size
			nameArr = add(&size,nameArr, nameLen);

			//update number of transactions with new user and user's transactions
			numTransactionsArr = updateNumTransactionsArr(size, numTransactionsArr, &numTrans);
			
			//add transaction to transaction array 
			transArr = addTransaction(size, transArr, numTrans, numTransactionsArr);
			slct = 'w';
		}
		//display full list
		else if(slct == 'l'){
			
			displayFull(nameArr, transArr, numTransactionsArr, size);
			slct = 'w';
		}
		//find
		else if(slct == 's'){
			printf("Enter the size of the name:");
			scanf("%d", &nameLen);
			findName( nameArr, transArr, numTransactionsArr, size, nameLen);
			slct = 'w';
			
		}
		//quit
		else if(slct == 'q'){
			printf("%c\n",slct);
			next = 0;
			slct = 'w';
		}

		//clear buffer
		while(getchar() != '\n');
			

	}

	/*free data*/
	int k;
	if( size >= 1 ){
		for(k = 0; k<size;k++){
			free(nameArr[k]);
			free(transArr[k]);
		}
	}
	else{
		free(nameArr[0]);
		free(transArr[0]);
		
	}
	free(transArr);
	free(nameArr);
	free(numTransactionsArr);
	nameArr = NULL;
	numTransactionsArr = NULL;
}

/*
*adds user to nameArr and increase size
*pre: size, nameArr, nameLen defined
*post: size increased by one, string added to nameArr
*/
char** add(int* size, char** nameArr, int nameLen){
	char tmpName[nameLen+1];
	char **tmpnames;

	//prompt user for name
	printf("Enter a name:");
	fgets(tmpName,nameLen+1,stdin);
	while(getchar() != '\n');
	if(*size ==0){
		tmpnames = (char**) malloc(sizeof(char*));
		tmpnames[0] = (char*) malloc(sizeof(char) * (nameLen+1));
		strcpy(tmpnames[0], tmpName);
		*size = *size + 1;	
		free(nameArr[0]);
		free(nameArr);
	}
	//create new dynamic array
	else{
		int i;		
		//allocate space for all strings pointers
		tmpnames = (char**) malloc( sizeof(char*) * (*size+1));

		//initialize data for size-1 strings in tmpnames
		for(i=0; i<*size; i++){
			tmpnames[i] = (char*)malloc(strlen(nameArr[i])+1);
		}


		//copy data from nameArr into tmpnames
		for(i=0; i<*size; i++){
			strcpy(*(tmpnames+i), *(nameArr+i));
		}

		// initialize space and copy new name into tmpnames
		tmpnames[i] = (char*)malloc(sizeof(char) * (nameLen+1));
		strcpy(tmpnames[*size], tmpName);
		*size = *size + 1;

		/* free data*/
		int w;
		for(w=0; w<*size-1;w++){
			free(nameArr[w]);
		}
		free(nameArr);
		nameArr = NULL;
	}
	//prints("%s", *names[0]);
	return tmpnames;
}

/*
*reallocates size of transArr to size+1 and adds the transactions of a new customer
* to transArr
*pre: size, transArr, numTrans, numTransactionsArr are defined
*post: size of transArr increased by one*sizeof(int), array of transactions added to transArr[size-1]
*/
int** addTransaction(int size, int** transArr, int numTrans, int *numTransactionsArr){
	int counter = 0;
	int tmp = -1;
	int isCorrect = -1;
	int *tmpArr = malloc(numTrans * 4);
	int **tmpTrans;
	

	//get input
	printf("Enter prices one at a time");
	for(counter = 0; counter < numTrans; counter++){
		printf("\n%d of %d:", (counter+1), numTrans);		
		//check for correct type		
		scanf("%d", &(tmpArr[counter]));
	}

	//allocate new tmpArr
	if(size == 1){
		tmpTrans = (int**)malloc(sizeof(int*));
		tmpTrans[0] = (int*)malloc(sizeof(int) * (numTrans));
		int j;
		for(j=0; j<numTrans;j++){
			tmpTrans[0][j] = tmpArr[j];
		}

		/* free data */
		for(j=0; j<size;j++){
			free(transArr[j]);
		}
		free(transArr);
		free(tmpArr);
		transArr=NULL;
	}
	//create larger tmpTrans and assign values
	else{
		int i,j;		
		/*allocate space for all array pointers*/
		tmpTrans = (int**) malloc( sizeof(int*) * (size));

		/*initialize data for size-1 strings in tmpnames*/
		for(i=0; i<size; i++){
			tmpTrans[i] = (int*)malloc( 4 * numTransactionsArr[i]);
			tmpTrans[i][0] = 0;
		}
		
		/*save data from transArr into tmpTrans*/
		int q = 0;
		for(i=0; i<size-1; i++){
			q = numTransactionsArr[i];
			for(j=0; j < q; j++){
				tmpTrans[i][j] = transArr[i][j];
			}
		}
		/*assign newest value*/
		for(j=0; j < numTrans; j++){
			tmpTrans[size-1][j] = tmpArr[j];
		}

		/* free data */
		for(j=0; j<size-1;j++){
			free(transArr[j]);
		}
		free(transArr);
		free(tmpArr);
		transArr=NULL;
	}

return tmpTrans;
}

/*
*adds the number of transactions to numTransactionsArr for a newly added customeer
*pre: size, numTransactionsArr, numTrans are defined
*post: numTransactionsArr increased by one. numTrans added to numTransactionsArr[size-1]
*/
int* updateNumTransactionsArr(int size, int *numTransactionsArr, int *numTrans){
	int *tmpArr = NULL;
	
	//initiate new array (possibily redundant)
	if(size == 1){
		tmpArr = (int*)malloc( sizeof(int) );
		tmpArr[0] = *numTrans;
		//free(numTransactionsArr);
	}
	else{
		/*reallocate size*/
		tmpArr = (int*) malloc(4 * size);
		
		/*copy old numbers into tmpArr*/
		int i;
		for(i=0; i<size-1;i++){
			
			tmpArr[i] = numTransactionsArr[i];
		}
		
		/*assign newest value*/
		tmpArr[size-1] = *numTrans;

	

	}	
		free(numTransactionsArr);
		numTransactionsArr = NULL;
		return tmpArr;
}
/*
*displays names in NameArr and transactions in transArr to stdout
* pre: nameArr, transArr, numTransactionsArr, size defined
*post: each string in nameArr printed to stdout followed by the ints stored in transArr
*/
void displayFull(char **nameArr, int **transArr, int *numTransactionsArr, int size){
	if(size == 0){
		printf("No Customers.");
	}
	else{
		int i,j,k;
		for(i=0;i<size;i++){
			//print name
			printf("Name: %s\n",nameArr[i]);
			
			//print transactions
			k = numTransactionsArr[i];
			printf("Transactions: ");
			for(j=0; j<k;j++){
				printf("%d ",transArr[i][j]);
			}
			printf("\n");
		}
	}

}

/*
*displays names in NameArr and the sum of the rows in transArr to stdout
* pre: nameArr, transArr, numTransactionsArr, size defined
*post: each string in nameArr printed to stdout followed by the sum of the rows of transArr
*/
void displayCompact(char **nameArr, int **transArr, int *numTransactionsArr, int size){
	if(size == 0){
		printf("No Customers.");
	}
	else{
		int i,j,k;
		int sum =0;
		for(i=0;i<size;i++){
			//print name
			printf("Name: %s\n",nameArr[i]);
			
			//print transactions
			k = numTransactionsArr[i];
			printf("Sales: ");
			for(j=0; j<k;j++){
				sum += transArr[i][j];
			}
			printf("%d\n", sum);
		}
	}
}

/**
*performs linear search to find if the user defined name is contained in nameArr and returns
* name plus transactions. will return last instance if multiple users w/ same name
*pre: nameArr, transArr, numTransactionsArr, size, nameLen are defined
*post: if name found: name and transactions for name are distplay on stdout
*      else: the string "name not found" displayed on stdout
*/
void findName(char **nameArr, int **transArr, int *numTransactionsArr, int size,int nameLen){
	char tmpName[nameLen+1];
	int i,q,k;
	int index = -1;
	printf("Enter the name:");
	scanf("%s",tmpName);
	if(size > 0){

		/*search*/
		for(i= 0; i<size;i++){
			if(strcmp(nameArr[i],tmpName) == 0){
				index = i;	
			}
		}
		if( (-1<index) && (index <size) ){
			printf("Transactions for %s: ", nameArr[index]);
			q = numTransactionsArr[index];
			for(i=0; i<q;i++){
				printf("%d ",transArr[index][i]);
			}
			printf("\n");
		}
		else
			printf("%s name not found!\n", tmpName);
	}
	else{
		printf("customer list is empty!");
	}

}
