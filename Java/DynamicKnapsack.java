/**
 * @author mike briden
 * Implementation of Dynamic Knapsack.
 * hw6ab
 */
import java.util.Arrays;

public class DynamicKnapsack {
	int[][] theData; //local copy of a list of items and their weights
	int[] maxSet; // set of indices of the maximum value set
	int maxValue = 0; // maxvalue of items that weigh less than/equal to maxWeight
	int[][] table; // table for knapsack
	int numElems; // number of elements in knapsack
	int weight = 0; // weight of an item
	int maxWeight; // total weight of knapsack
	/**
	 * creates an instance of DynamicKnapsack and finds the maximum set of items with sum of
	 * weights less than or equal to w
	 * @param a 2xn array of input of values and weights. a[0] stores values a[1] stores weights
	 * @param w the maximum weight that the knapsack can hold
	 */
	public DynamicKnapsack(int[][] a, int w) {
		//instantiate class variables
		theData = a;
		numElems = a[0].length;
		table = new int[numElems+1][w+1];
		maxSet = new int[numElems];
		maxWeight = w;

		// values for instance;
		System.out.println("numElems: " + numElems + " maxWeight: " + maxWeight);

		//do dynamic knapsack
		knapsack();
		//do backtrack
		backTrack();
	}
	/**
	 * create the table with values and weight from a[][]
	 */
	private void knapsack() {

		//fill first column with zeroes
		for(int i = 0; i< numElems; i++ ) {
			table[i][0]=0;
		}

		//fill first row with zeroes
		for(int i = 0; i< maxWeight+1; i++ ) {
			table[0][i]=0;
		}


		for(int i=1; i< numElems+1; i++) {
			for(int j=1; j<maxWeight+1; j++) {
				weight = theData[1][i-1];
				if(weight > j)
					table[i][j] = table[i-1][j];
				else {
					table[i][j] = Math.max(table[i-1][j],
										   table[i-1][j-weight] + theData[0][i-1]);
				}
			}
		}
		for(int i=0; i< numElems+1; i++) {
			for(int j=0; j<maxWeight+1; j++) {
			}
		}

	}

	/**
	 * implements backtrack algorithm for 01dynamicKnapsack
	 */
	private void backTrack() {
		int i = numElems; //row index for table
		int j = maxWeight; // column index for table
		int k = numElems; // index for maxSet array


		while(i>0 && j>0) {
			//item i isn't in the max set
			if(table[i][j] == table[i-1][j]) {
				maxSet[k-1] = 0;

				//advance j through j unitl table[i][j] != table[i-1][j] if necessary
				while(table[i][j] <= table[i-1][j]) {
					i = i-1;
					k--;
					if(i == 0 || j == 0)
						break;
				}
			}
			else {
				maxSet[k-1] = 1;
				i = i - 1;
				j = j - theData[1][k-1];
				k--;
			}
		}
		System.out.println(Arrays.toString(maxSet) + " maxval: " + table[numElems][maxWeight]);
	}
}
