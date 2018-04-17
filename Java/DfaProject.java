/*
 Name: Michael Briden
 Assignment: 1
 Title: Deterministic Finite Automata
 Date: 9/24/15
 Sources consulted: 
 	Sipser, Introduction/Theory of Computation
 	http://www.willamette.edu/~gorr/classes/cs231/lectures/chapter9/arrays2d.htm
 Known Bugs: This program does not handle files of the wrong format
 Program description: This program reads in a user input file to create a dfa
 	and test strings contained within the file.
 Instructions: Run DFA.java, and follow prompts.
*/

import java.io.File;
import java.io.IOException;
import java.util.Scanner;

public class DfaProject {
	int[][] dfaData; // holds all pertinent DFA data
	int startState = -1; // start state of DFA.
	String[] strArr; // holds strings that will be tested
	
	/**
	 * constructor used to create the DFA and test strings
	 * within the user input file
	 * @param fileName the name of the file that the user inputs
	 */
	public DfaProject(String fileName){
		 long to;
		 long t1;
		
		//create dfa
		to = System.currentTimeMillis();
		Readfile(fileName);
		t1 = System.currentTimeMillis();
		System.out.println( "ReadFile run-time: " + (float)(t1-to) / 1000.0  );
		System.out.println(t1-to);
		
		//test strings
		to = System.currentTimeMillis();
		
		try {
		    Thread.sleep(1000);                 //1000 milliseconds is one second.
		} catch(InterruptedException ex) {
		    Thread.currentThread().interrupt();
		}
		
		t1 = System.currentTimeMillis();
		
		testStrings(strArr);
		
	
		
		System.out.println("to: " + to + " t1: " + t1);
		System.out.println( "testString run-time: " + (float)(t1-to) / 1000.0  );
	}
	
	/** 
	 * Readfile reads the input file and instantiates
	 * this String and stateData
	 * @param fileName contains the data needed to create DFA
	 */
	private void Readfile( String fileName){
		//instantiate variables
		int numStates = -1; // number of states in DFA.
		int finalState = -1; // a final state of dfa (dummy var.)
		int aToNext = -1; // the next state in DFA if an "a" is read.
		int bToNext = -1; // the next state in DFA if a "b" is read.
		String dmyString = ""; // dummy string to read in values.
		
		try {
			//create scanner
			File infile = new File (fileName) ;
			Scanner in = new Scanner ( infile);
			Scanner dmyScanner;
			
			//instantiate dfaData given size
			numStates = in.nextInt();
			
			//instantiate dfaData array
			dfaData = new int[4][numStates];
			in.nextLine();
			
			//assign start state
			startState = in.nextInt();
			in.nextLine();
			dfaData[0][startState] = 1;
			
			//read in final states
			dmyString = in.nextLine();
			dmyScanner = new Scanner(dmyString);
			while(dmyScanner.hasNext()){
				finalState = dmyScanner.nextInt();
				//add finalState indicator to dfaData
				dfaData[1][finalState] = 1;
			}
			dmyScanner.close();
			
			//read in transition table
			for(int i=0; i<numStates; i++){
				dmyString = in.nextLine();
				dmyScanner = new Scanner(dmyString);
				aToNext = dmyScanner.nextInt();
				bToNext = dmyScanner.nextInt();
				dfaData[2][i] = aToNext;
				dfaData[3][i] = bToNext;
				dmyScanner.close();
			}
			
			//read in strings
			numStates = in.nextInt();
			in.nextLine();
			strArr = new String[numStates];
			for(int i=0; i<numStates; i++){
				strArr[i] = in.nextLine();
			}
			in.close();	
			System.out.println("DFA created");
		} catch (IOException io ) {
			System.out.println( "file input error: " + io ) ;
		}//catch
	}//readFile
	
	/**
	 * This method tests whether or not the string str is 
	 * accepted by the DFA specified in the input file.
	 * @param str the string that will be tested against DFA
	 */
	private void testString(String str){ 
		int thisState = startState; // points to current state in dfa.
		char[] inputStr = new char[str.length()]; //holds str as a char array
		
		//turn str into an array containing values of str
		for(int i = 0; i<str.length(); i++){
			inputStr[i] = str.charAt(i);
		}
		
		//compute str
		for(int i = 0; i<inputStr.length; i++){
			if(inputStr[i] == 'a')
				thisState = dfaData[2][thisState];
			else
				thisState = dfaData[3][thisState];
		}
		
		//display results
		if(dfaData[1][thisState] == 1)
			System.out.println(str + ": ACCEPT");
		else
			System.out.println(str + ": REJECT");

	}
	
	/**
	 * tests the strings contained in the input file
	 * against the DFA which is also specified in the file
	 * @param stringArr an array containing the string specified
	 * in iput file
	 */
	private void testStrings(String[] stringArr){
		for(int i=0; i<stringArr.length; i++)
			testString(stringArr[i]);
	}
	
	/**
	 * printArray prints out the dfaData array
	 */
	private void printArray(){
		for(int i=0; i < dfaData.length; i++){
			for(int j=0; j < 4; j++)
				System.out.print(dfaData[i][j]);
			System.out.println();
		}//for
	}//printArray
	

}//DFAProject
