/*
File Prologue
Name: Adam Howell
Project: LogSort
Date: 2014-10-31
Description: This project will merge multiple files into one, and sort based on the timestamp.
Much of this code will come from my UVU CS 2420 project 6, which dealt with sorting.

I declare that the following source code was written by me, or taken from public domain sources.
*/


#include <time.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <array>
#include <boost/filesystem.hpp>


using namespace std;
using namespace boost::filesystem;


const string MENU1 = "Welcome to Adam's logfile sort utility.";
const string MENU2 = "\n";
const string HEADER1 = "\n\t\t\t\tElapsed\tElapsed\tOutput";
const string HEADER2 = "Sort Method\tFile#\tTotal\tTicks\tTime\tFile Name";
const char DELIMITER = '\n';			// The delimiter that I use with getline.
//const int IGNORE = 4096;				// I use this when clearing the input buffer.
const int ARRAYSIZE = 100000;			// The size of the array for the second file.
const string ARRAYDEFAULT = "0";		// The value to initialize array elements to.
const string INFILE1 = "infile1.txt";	// Input file 1.
const string INFILE2 = "infile2.txt";	// Input file 2.
const string OUTFILE = "outfile.txt";	// Output file.


int fileRead( ifstream& _handle, string _array[] );				// My file reading function.
void printArray( string _array[], int _length );					// My array printing (to screen) function.
void writeArray( string _array[], int _length, string _fileName );	// My array writing (to disc) function.
void insertionSort( string _array[], int _length );				// My Insertion Sort function.
void shellSort( string _array[], int _length );					// My Shell Sort function.
void quickSort( string _array[], int _start, int _length );			// My Quick Sort function.


int main()
{
	string fileStr = "";		// A variable to hold the line read from each file before converting to an integer.
	int fileCount1 = 0;			// The number of lines in input file 1.
	int fileCount2 = 0;			// The number of lines in input file 2.
	int fileCount3 = 0;			// The number of lines in input file 3.
	double read1 = 0;			// The time int ticks it takes to read file 1.
	double iSort1 = 0;			// The time int ticks it takes to Insertion Sort file 1.
	double sSort1 = 0;			// The time int ticks it takes to Shell Sort file 1.
	double qSort1 = 0;			// The time int ticks it takes to Quick Sort file 1.
	double read2 = 0;			// The time int ticks it takes to read file 2.
	double iSort2 = 0;			// The time int ticks it takes to Insertion Sort file 2.
	double sSort2 = 0;			// The time int ticks it takes to Shell Sort file 2.
	double qSort2 = 0;			// The time int ticks it takes to Quick Sort file 2.
	double read3 = 0;			// The time int ticks it takes to read file 3.
	double iSort3 = 0;			// The time int ticks it takes to Insertion Sort file 3.
	double sSort3 = 0;			// The time int ticks it takes to Shell Sort file 3.
	double qSort3 = 0;			// The time int ticks it takes to Quick Sort file 3.
	clock_t start;				// A temporary variable to hold the current clock time.
	clock_t end;				// A temporary variable to hold the current clock time.

	// Print the program header.
	cout << MENU1 << endl;

	// Open a filestream for the file, 100,000 records maximum.
	ifstream dataFile1( INFILE1 );

	// Test for file error.
	if ( dataFile1.fail() )
	{
		// Announce that we could not open the file.
		boost::filesystem::path new_full_path( boost::filesystem::current_path() );
		std::cout << "Current path is:\n" << new_full_path << std::endl;
		cout << "Could not open file \"" << INFILE1 << "\" for reading." << endl << endl;
	}
	else
	{
		// Test code.
		//cout << "Opened \"" << INFILE1 << "\" for reading." << endl;

		string* arrayi1 = new string[ARRAYSIZE];
		string* arrays1 = new string[ARRAYSIZE];
		string* arrayq1 = new string[ARRAYSIZE];

		// Get the starting tick.
		start = clock();

		// Read the file into the array
		fileCount3 = fileRead( dataFile1, arrayi1 );

		// Get the ending tick.
		end = clock();
		// Determine how long it too to read in the third file.
		read3 = end - start;

		// Verify that the file size is what we expected.  This is needed to ensure the arrays are large enough to hold the entire file.
		if ( fileCount3 != ARRAYSIZE )
		{
			cout << "The number of entries in " << INFILE1 << " does not match what was expected." << endl;
			cout << "Please check " << INFILE1 << " and restart this program." << endl;
			system( "PAUSE" );
			exit( 1 );
		}

		// Test code.
		//cout << INFILE3 << " had " << fileCount3 << " values/lines, and was read in " << read3 / CLK_TCK << " seconds (" << read3 << " ticks)." << endl;

		// Copy the array for Insertion Sort to the arrays for Shell Sort and Quick Sort.
		for (int i = 0; i < ARRAYSIZE; i++)
		{
			arrays1[i] = arrayi1[i];
			arrayq1[i] = arrayi1[i];
		}

//Insertion Sort 3
		// Get the starting tick.
		start = clock();
		// Sort the array using Insertion Sort.
		insertionSort( arrayi1, ARRAYSIZE );
		// Get the ending tick.
		end = clock();
		// Determine how long Insertion Sort took to sort the third file.
		iSort3 = end - start;

		// Write the sorted array to the output file.
		writeArray( arrayi1, ARRAYSIZE, OUTFILE );

		// Print the results to the screen.
		cout << "Insertion\t3\t" << fileCount3 << "\t" << iSort3 << "\t" << iSort3 / CLK_TCK << "\t" << OUTFILE << endl;

//Shell Sort 3
		// Get the starting tick.
		start = clock();
		// Sort the array using Insertion Sort.
		shellSort( arrays1, ARRAYSIZE );
		// Get the ending tick.
		end = clock();
		// Determine how long Insertion Sort took to sort the third file.
		sSort3 = end - start;

		// Write the sorted array to the output file.
		writeArray( arrays1, ARRAYSIZE, OUTFILE );

		// Print the results to the screen.
		cout << "Shell\t\t3\t" << fileCount3 << "\t" << sSort3 << "\t" << sSort3 / CLK_TCK << "\t" << OUTFILE << endl;
		
//Quick Sort 3
		// Get the starting tick.
		start = clock();
		// Sort the array using Insertion Sort.
		quickSort( arrayq1, 0, ARRAYSIZE - 1 );
		// Get the ending tick.
		end = clock();
		// Determine how long Insertion Sort took to sort the third file.
		qSort3 = end - start;

		// Write the sorted array to the output file.
		writeArray( arrayq1, ARRAYSIZE, OUTFILE );

		// Print the results to the screen.
		cout << "Quick\t\t3\t" << fileCount3 << "\t" << qSort3 << "\t" << qSort3 / CLK_TCK << "\t" << OUTFILE << "\n" << endl;
	}
	// Close the file used for reading.
	dataFile1.close();

	// Pause so the user can read the screen.
	system( "PAUSE" );
	return 0;
}// End main().


// Function name:	fileRead()
// Purpose:		This function will read the content of the provided file handle into an array.
// Parameters:		The file handle to read, and an array to write to.
// Returns:		The length of the file read.
// Preconditions:	none
// Postconditions:	none
int fileRead( ifstream& _handle, string _array[] )
{
	string fileStr = "";	// Variable to temporarily hold the contents read from the file.
	int length = 0;		// Variable to count the lines in the file.

	// Loop until End Of File, reading one number at a time.
	while ( !_handle.eof() )
	{
		// Test code.
		//cout << "Entered the while() loop." << endl;

		// Read one line from dataFile1 into fileStr.
		getline( _handle, fileStr );

		// Test code.
		//cout << "Read line as " << fileStr << endl;

		// Insert the line read from the file into the array.
		_array[length] = fileStr;

		// Increment length.
		length++;

		// Test code.
		//cout << "Total values read so far: " << length << endl;
	}
	return length;
} // End fileRead().


// Function name:	printArray()
// Purpose:		This function will print the content of the provided array to the console.
// Parameters:		An array to print, and the size of that array.
// Returns:		none
// Preconditions:	none
// Postconditions:	none
void printArray( string _array[], int _length )
{
	// Loop through the array, one element at a time.
	for (int i = 0; i < _length; i++)
	{
		// Output the content at the current location.
		cout << _array[i] << " ";
	}
	// Print an extra newline to make the output more presentable.
	cout << "\n" << endl;
} // End printArray().


// Function name:	writeArray()
// Purpose:		This function will write the content of the provided array to the provided file.
// Parameters:		An array to print, the size of that array, and a filename to write to.
// Returns:		none
// Preconditions:	none
// Postconditions:	none
void writeArray( string _array[], int _length, string _fileName )
{
	ofstream writeFile( _fileName, ofstream::out );

	// Test for file error.
	if ( writeFile.fail() )
	{
		// Announce that we could not open the file.
		cout << "\nCould not open file \"" << _fileName << "\" for reading." << endl;
	}
	else
	{
		// Loop through the array, one element at a time.
		for (int i = 0; i < _length; i++)
		{
			// Write the content at the current location to the output file.
			writeFile << _array[i] << endl;
		}
		// Close the file we just wrote to.
		writeFile.close();
	}
} // End writeArray().


// Function name:	insertionSort()
// Purpose:		This function will sort the contents of an array using the Insertion Sort method.
// Parameters:		An array to sort, and the size of that array.
// Returns:		none
// Preconditions:	none
// Postconditions:	none
void insertionSort( string _array[], int _length )
{
	/*
	Insertion Sort finds a value out of place, and inserts it where it should go.
	This involves storing the out of place value in a temp variable, shifting all values to make room, and inserting that temp value in it's proper spot.
	*/
	string temp = 0;
	int loop = 0;
	for (int i = 0; i < _length; i++)
	{
		loop = i;
		while ( loop > 0 && _array[loop - 1] > _array[loop] )
		{
			// Save the current position in the array to temp.
			temp = _array[loop];
			// Assign the current position in the array to the value at the next lower position.
			_array[loop] = _array[loop - 1];
			// Assign the next lower position to the temp variable.
			_array[loop - 1] = temp;
			// Decrement the current position in the array.
			loop--;
		}
	}
} // End insertionSort().


// Function name:	shellSort()
// Purpose:		This function will sort the contents of an array using the Shell Sort method.
// Parameters:		An array to sort, and the size of that array.
// Returns:		none
// Preconditions:	none
// Postconditions:	none
void shellSort( string _array[], int _length )
{
	/*
	Shell Sort is a modified Insertion Sort.
	It divides the list into many sections, and compares the first value in each section against each other, and sorts them.
	The distance between these sections is called the gap.
	Then it compares the second value in each section, and sorts them.
	It then divides the complete list into fewer sections, and repeats the comparisons.
	It continues dividing the complete list, but into fewer sections each time.
	*/

	int i = 0;
	int j = 0;
	int gap = 0;
	string temp = 0;

	// Start with a gap size of 1/2 _length, and cut it in half again each time we loop.
	for ( gap = _length/2; gap > 0; gap/= 2 )
	{
		// Start at the current gap size, and increment until the end of the array.
		for ( i = gap; i < _length ; i++ )
		{
			// Put the current array position into temp.
			temp = _array[i];
			// Loop through this section.
			for( j = i; j >= gap ; j-= gap )
			{
				// Insertion Sort this section.
				if ( temp < _array[j - gap] )
				{
					// Swap the two positions.
					_array[j] = _array[j - gap];
				}
				else
				{
					break;
				}
			}
			// Put temp in it's proper position.
			_array[j] = temp;
		}
	}
} // End shellSort().


// Function name:	quickSort()
// Purpose:		This function will sort the contents of an array using the Quick Sort method.
// Parameters:		An array to sort, the starting point in that array, and the ending point in that array.
// Returns:		none
// Preconditions:	none
// Postconditions:	none
void quickSort( string _array[], int _start, int _end )
{
	int i = _start;	// The lower index.
	int j = _end;		// The upper index.
	string temp = 0;		// A temporary variable to use for swapping values.
	string pivot = 0;		// The pivot.

	pivot = _array[abs( ( _start + ( _end ) ) / 2)];
	// Test code.
	//cout << "Using " << pivot << " as a pivot, " << _start << " as a start, and " << _end << " as an end." << endl;

	// While the lower bound has not reached the upper bound.
	while ( i <= j )
	{
		// While the value at the lower index is less than the pivot.
		while ( _array[i] < pivot )
		{
			// Ignore that value and re-evaluate the while loop.
			i++;
		}
		// While the value at the upper index is greater than the pivot.
		while ( _array[j] > pivot )
		{
			// Ignore that value and re-evaluate the while loop.
			j--;
		}
		// If the lower bound reaches the upper bound.
		if (i <= j)
		{
			// Test code.
			//cout << "Swapping indices " << i << " " << j << ", whose values are " << _array[i] << " " << _array[j] << endl;
			// Swap the two values.
			temp = _array[i];
			_array[i] = _array[j];
			_array[j] = temp;
			i++;
			j--;
			// Test code.
			//printArray( _array, 10 );
		}
	}
	if ( _start < j )
	{
		// Test code.
		//cout << "Lower recusion." << endl;
		quickSort( _array, _start, j );
	}
	if ( i < _end )
	{
		// Test code.
		//cout << "Upper recusion." << endl;
		quickSort( _array, i, _end );
	}
} // End quickSort().
