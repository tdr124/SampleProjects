/*Name: Michael Briden
 *01/26/18
 *Project01
 *bugs: the program may crash on certain inputs of message,
 * prefix, and host id. I'm not exactly sure why, but I think
 * it might have something to do with the fact that I instantiated
 * my variables in main to either -1 and 0. I think sometimes -1
 * or 0 will get passed the checks and cause problems. I discovered
 * this kind of late and didn't want to try to make changes in case
 * the changes ended up being drastic.
 */
# include <stdio.h>
#include <math.h>

void decToBinToOutput(int x);
int findOnes(int x);
int findMask(int p1, int p2, int p3, int p4);

int main(void){
	/*variables*/
	int sentinal = 1;
	int promptSent = -1;
	int correctIPSentinal = 1;
	int  prompt=0;
	int isCorrect = 0;
	int generalIP = -1;
	int genIP1 = -1;
	int genIP2 = -1;
	int genIP3 = -1;
	int genIP4 = -1;
	int subnetMask = -1;
	int prefix1 = -1;
	int prefix2 = -1;
	int prefix3 = -1;
	int prefix4 = -1;
	int binToDec1 = -1;
	int binToDec2 = -1;
	int binToDec3 = -1;
	int binToDec4 = -1;
	int snNonStatic = 0;
	int tmp = -1;
	int tmpRemainder1 = -1;
	int tmpRemainder2 = -1;
	int trailingZero = -1;
	int trailingZeroes = -1;
	int decCount = -1;
	int hostID1 = -1;
	int hostID2 = -1;
	int hostID3 = -1;
	int hostID4 = -1;

	char ch;
	char doAgain;
	char host;
	while(sentinal == 1 ){

		/*prompt user for conversion type*/
	   	printf("What type of conversion do you want?\n");
	   	printf("Enter 1 for IP-address and subnet, 2 or the host and network prefix:");
	   	promptSent = scanf("%d", &prompt);

		/*make sure 1 or 2 is entered*/
		if(promptSent == 0 ){
			promptSent = -1;
			prompt = 0;
			/*reset loop sentinals and prompts*/
			do{
				scanf("%c",&ch);
			}while(ch != '\n');
	
			printf("\nWrong input. Try again.\n");
			continue;
		}
		/*1: convert message address to appropriate outputs*/
		if(prompt == 1){

			/* get user input, save input, and check input*/
			while(isCorrect == 0){

				/*get user input, parse, and save*/
				printf("Enter the message address:");
				scanf(" %d", &genIP1);
				scanf(" %c", &ch);
				scanf(" %d", &genIP2);
				scanf(" %c", &ch);
				scanf(" %d", &genIP3);
				scanf(" %c", &ch);
				scanf(" %d", &genIP4);
				scanf(" %c", &ch);
				scanf(" %d", &subnetMask);

				/* check input*/
				if((genIP1 <=255) && (genIP2 <= 255) &&
				   (genIP3 <=255) && (genIP4 <=255) && (subnetMask <=32)){
					
					if((genIP1 >=0) && (genIP2>=0) && (genIP3>=0) &&
					   (genIP4>=0) && (subnetMask >0)){

						/* change sentinal values*/
						prompt = 0;
						isCorrect = 1;

						/*Display the ip address in hex and display*/
						printf("\nThe ip address is %02X%02X%02X%02X",
							 genIP1, genIP2, genIP3, genIP4);
						printf(" in hexidecimal and\n");

						/*convert decimal dot to binary and display*/
						decToBinToOutput(genIP1);
						printf(" ");
						decToBinToOutput(genIP2);
						printf(" ");
						decToBinToOutput(genIP3);
						printf(" ");
						decToBinToOutput(genIP4);
						printf(" in binary\n\n");


						/*Display subnet mask information: */
						tmp = subnetMask / 8;
						decCount = tmp;
						tmpRemainder1 = subnetMask % 8;
						tmpRemainder2 = tmpRemainder1;
						trailingZero = 8;
						trailingZeroes = 4;


						/*instantiate trailing zeroes*/
						if((tmpRemainder1 > 0) &&  (tmp > 0)){
							trailingZeroes = trailingZeroes - tmp -1;
						}
						else if ((tmp > 0) && (tmpRemainder1 == 0)){
							trailingZeroes = trailingZeroes - tmp-1;
						}
						else if ((tmp == 0) && (tmpRemainder1 > 0)){
							trailingZeroes = trailingZeroes -1;
						}

						/* assign a value the binary number that isn't all 1's or all 0's
						/*print off binary number that has ones with trailing zeros*/
						while(tmpRemainder2 > 0){
							tmpRemainder2--;
							snNonStatic += (int) pow (2, 7-tmpRemainder2 );
						}

						/* assign appropriate base10 value to subnet mask*/
						switch(decCount){
						case 4: binToDec1 = 255, binToDec2 = 255, binToDec3 = 255, 
							binToDec4 = 255;
							break;
						case 3: binToDec1 = 255, binToDec2 = 255, 
							binToDec3 = 255, binToDec4 = snNonStatic;
							break;
						case 2: binToDec1 = 255, binToDec2 = 255;
							binToDec3 = snNonStatic, binToDec4 = 0;
							break;
						case 1: binToDec1 = 255; binToDec2 = snNonStatic, 
							binToDec3 = 0, binToDec4 = 0;
							break;
						case 0: binToDec1 = snNonStatic, binToDec2 = 0;
							binToDec3 = 0; binToDec4 = 0;
							break;
						}

						/*Display the subnet mask address in hex*/
						printf("The subnet mask is %02X%02X%02X%02X ",
							 binToDec1, binToDec2, binToDec3, binToDec4);
						printf("in hexidecimal and\n");

						/* print out binary form starting w/  leading 1's if tmp>1*/
						if(tmp > 0){
							while(tmp > 0){
								printf("11111111 ");
								tmp--;
							}
						}

						/*print off binary number that has ones with trailing zeros*/
						while(tmpRemainder1 > 0){
							printf("1");
							tmpRemainder1--;
							trailingZero--;
							/*snNonStatic += (int) pow (2, 7-tmpRemainder );*/
						}
						while(trailingZero > 0){
							printf("0");
							trailingZero--;
						}

						printf(" ");

						/*print off remaining zeroeth binary numbers*/
						while(trailingZeroes > 0){
							printf("00000000 ");
							trailingZeroes --;
						}

						printf("in binary\n");

						/* print out the decimal dot form of subnet mask*/
							printf("subnet in dot-decimal is: %d.%d.%d.%d\n\n", binToDec1, 
								 binToDec2, binToDec3,binToDec4);

						/*compute prefix numbers*/
						prefix1 = genIP1 & binToDec1;
						prefix2 = genIP2 & binToDec2;
						prefix3 = genIP3 & binToDec3;
						prefix4 = genIP4 & binToDec4;

						/* display prefix in hex*/
						printf("The network prefix is: %02X%02X%02X%02X", prefix1,
							prefix2, prefix3, prefix4);
						printf(" in hexidecimal and \n");

						/*display the prefix in binary */
						decToBinToOutput(prefix1);
						printf(" ");
						decToBinToOutput(prefix2);
						printf(" ");
						decToBinToOutput(prefix3);
						printf(" ");
						decToBinToOutput(prefix4);
						printf(" in binary\n");

						/* display prefix in dot-decimal*/
						printf("The network prefix in dot-decimal is: %d.%d.%d.%d\n\n",
							 prefix1, prefix2, prefix3,prefix4);

						/*compute host id components*/
						hostID1 = genIP1 & (~prefix1);
						hostID2 = genIP2 & (~prefix2);
						hostID3 = genIP3 & (~prefix3);
						hostID4 = genIP4 & (~prefix4);

						/*display host id in hexidecimal*/
						printf("the host id is: %02X%02X%02X%02X ",
							hostID1, hostID2, hostID3, hostID4);
						printf(" in hexidecimal and\n");

						/* display host id in binary*/
						decToBinToOutput(hostID1);
						printf(" ");
						decToBinToOutput(hostID2);
						printf(" ");
						decToBinToOutput(hostID3);
						printf(" ");
						decToBinToOutput(hostID4);
						printf(" in binary\n");

						printf("The host id in dot-decimal is %d.%d.%d.%d\n\n",
							hostID1, hostID2, hostID3, hostID4);
					}else{
						printf("Wrong input. Try again. ");
					}

				}else{
					printf("Wrong input. Try again ");
				}

			}
		}
		/* host & prefix to message*/
		else if(prompt == 2){
			/*read in host id*/
			printf("Enter host:");
			scanf("%d.%d.%d.%d", &hostID1, &hostID2, &hostID3, &hostID4);
			
			/* check host input*/
			if( (hostID1 <=255) && (hostID2 <= 255) && (hostID3 <=255) 
		            && (hostID4 <=255) ) {					
				if( (hostID1 >=0) && (hostID2>=0) && (hostID3>=0) &&
			            (hostID4>=0) ){

					/*read in prefix*/
					printf("\nenter the network prefix:");
					scanf("%d.%d.%d.%d", &prefix1, &prefix2, &prefix3,&prefix4);

					/* check prefix input*/
					if( (prefix1 <=255) && (prefix2 <= 255) && (prefix3 <=255) 
		            		    && (prefix4 <=255) ) {					
						if( (prefix1 >=0) && (prefix2>=0) && (prefix3>=0) &&
					            (prefix4>=0) ){
	
							/*compute ip address*/
							genIP1 = prefix1 | hostID1;
							genIP2 = prefix2 | hostID2;
							genIP3 = prefix3 | hostID3;
							genIP4 = prefix4 | hostID4;

							/*display*/
							printf("The message is: %d.%d.%d.%d/%d\n\n", genIP1, genIP2, genIP3, genIP4,
								findMask(prefix1, prefix2, prefix3, prefix4));
						}else{
							printf("\n Wrong input. Try again\n");
						}					
					}else{
						printf("\n Wrong input. Try again\n");
					}
				}else{
					printf("\n Wrong input. Try again\n");
					continue;
				}
			}else{
				printf("\nWrong input. Try again.\n");
				continue;
			}		
		}

		/*reset loop sentinals and prompts*/
		do{
			scanf("%c",&ch);
		}while(ch != '\n');

		/*ask use to repeat*/
		printf("Enter r to repeat, q to quit\n");
		scanf(" %c", &doAgain);
		if(doAgain=='q'){
			sentinal = 0;
		}
		else{
			prompt = 0;
			promptSent = -1;
			isCorrect = 0;
		}
	}
}

/*converts a base-10 number to base 2 and prints to standard output*/
void  decToBinToOutput(int x){
	int binNum1 = -1;
	int binNum2 = -1;
	int binNum3 = -1;
	int binNum4 = -1;
	int binNum5 = -1;
	int binNum6 = -1;
	int binNum7 = -1;
	int binNum8 = -1;
	int tmp = x;
	int count = 7;

	/*calculate binary form of x and save as single digits*/
	binNum1 = tmp%2;
	tmp = tmp/2;

	binNum2 = tmp%2;
	tmp = tmp/2;

	binNum3 = tmp%2;
	tmp = tmp/2;

	binNum4 = tmp%2;
	tmp = tmp/2;

	binNum5 = tmp%2;
	tmp = tmp/2;

	binNum6 =  tmp%2;
	tmp = tmp/2;

	binNum7 = tmp%2;
	tmp = tmp/2;

	binNum8 = tmp%2;

	/*print x in base 2*/
	printf("%d%d%d%d%d%d%d%d",binNum8,binNum7,binNum6,binNum5,
				  binNum4,binNum3, binNum2,binNum1);
}

/* find the first occurance of 1 one in an 8 bit binary number from left to right*/
int findOnes(int x){
	int binNum1 = -1;
	int binNum2 = -1;
	int binNum3 = -1;
	int binNum4 = -1;
	int binNum5 = -1;
	int binNum6 = -1;
	int binNum7 = -1;
	int binNum8 = -1;
	int tmp = x;
	int count = -1;
	
	/* calculate binary number and save as single components*/
	binNum1 = tmp%2;
	tmp = tmp/2;

	binNum2 = tmp%2;
	tmp = tmp/2;

	binNum3 = tmp%2;
	tmp = tmp/2;

	binNum4 = tmp%2;
	tmp = tmp/2;

	binNum5 = tmp%2;
	tmp = tmp/2;

	binNum6 =  tmp%2;
	tmp = tmp/2;

	binNum7 = tmp%2;
	tmp = tmp/2;

	binNum8 = tmp%2;

	if(binNum1 == 1)
		count = 1;
	else if( binNum2 == 1)
		count = 2;
	else if( binNum3 == 1)
		count = 3;
	else if( binNum4 == 1)
		count = 4;
	else if( binNum5 == 1)
		count = 5;
	else if( binNum6 == 1)
		count = 6;
	else if( binNum7 == 1)
		count = 7;
	else if(binNum8 == 1)
		count = 8;
	return count;	
}

/*computes the first occurance of a one, from left to right, in a 4-part 32bit number */
int findMask( int p1, int p2, int p3, int p4){
	int count =0;
	int x1 = 0;
	int x2 = 0;
	int x3 = 0;
	int x4 = 0;

	x1 = findOnes(p4);
	x2 = findOnes(p3);
	x3 = findOnes(p2);
	x4 = findOnes(p1);

	if(x1 > 0){
		count = 32-x1+1;
	}
	else if(x2 > 0){
		count = 24-x2+1;
	}
	else if(x3 > 0){
		count = 16-x3+1;
	}
	else if(x4 > 0){
		count = 8-x4+1;
	}
	else{
		count = 0;
	}
	
	return count;
}
