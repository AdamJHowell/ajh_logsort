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
const string MENU2 = "Please enter the name of the first file to sort: ";
const string MENU3 = "Please enter the name of the second file to sort: ";
const string HEADER1 = "\n\t\t\t\tElapsed\tElapsed\tOutput";
const string HEADER2 = "Sort Method\tFile#\tTotal\tTicks\tTime\tFile Name";
const string INFILE1 = "infile1.txt";	// Input file 1.
const string INFILE2 = "infile2.txt";	// Input file 2.
const string OUTFILE = "outfile.txt";	// Output file.
const int IGNORE = 4096;				// This is used to clear the input buffer.


int fileCount( ifstream& _handle );							// My file line-counting function.
int fileRead( ifstream& _handle, string _array[] );				// My file reading function.
void printArray( string _array[], int _length );					// My array printing (to screen) function.
void writeArray( string _array[], int _length, string _fileName );	// My array writing (to disc) function.
void insertionSort( string _array[], int _length );				// My Insertion Sort function.
void shellSort( string _array[], int _length );					// My Shell Sort function.
void quickSort( string _array[], int _start, int _length );			// My Quick Sort function.


int main()
{
	string userFile1 = "";		// The first file name.
	string userFile2 = "";		// The second file name.
	int arraySize = 0;			// The number of lines in the current input file.
	int fileCount1 = 0;			// The number of lines read in input file 1.
	int fileCount2 = 0;			// The number of lines read in input file 2.
	int fileCount3 = 0;			// The number of lines read in input file 3.
	double iSort = 0;			// The time in ticks it takes to Insertion Sort.
	double sSort = 0;			// The time in ticks it takes to Shell Sort.
	double qSort = 0;			// The time in ticks it takes to Quick Sort.
	clock_t start;				// A temporary variable to hold the current clock time.
	clock_t end;				// A temporary variable to hold the current clock time.

	// Print the program header.
	cout << MENU1 << endl;
	boost::filesystem::path new_full_path( boost::filesystem::current_path() );
	std::cout << "Current path is:\n" << new_full_path << std::endl;
	cout << MENU2 << endl;
	// Read in the first file name.
	cin >> userFile1;
	// Clear the input buffer.
	cin.ignore( IGNORE, '\n' );
	cout << endl;
	
	cout << MENU3 << endl;
	// Read in the first file name.
	cin >> userFile2;
	// Clear the input buffer.
	cin.ignore( IGNORE, '\n' );
	cout << endl;
	
	cout << "Attempting to open " << userFile1 << endl;
	// Open a filestream for the first file.
	ifstream dataFile1( userFile1 );
	
	cout << "Attempting to open " << userFile2 << endl;
	// Open a filestream for the second file.
	ifstream dataFile2( userFile2 );

	// Test for file error.
	if ( dataFile1.fail() )
	{
		// Announce that we could not open the file.
		cout << "Could not open file \"" << userFile1 << "\" for reading." << endl << endl;
	}
	else if ( dataFile2.fail() )
	{
		// Announce that we could not open the file.
		cout << "Could not open file \"" << userFile2 << "\" for reading." << endl << endl;
	}
	else
	{
		// Test code.
		//cout << "Opened \"" << INFILE1 << "\" for reading." << endl;
		
		// Count the number of lines in the file.
		arraySize = fileCount( dataFile1 );
		dataFile1.clear();						// forget we hit the end of file
		dataFile1.seekg(0, ios::beg);				// move to the start of the file

		// Test code.
		//cout << "Counted " << arraySize << " lines in " << INFILE1 << endl;

		string* arrayi1 = new string[arraySize];	// Create arrayi1 on the heap to hold the lines read from the input file.
		string* arrays1 = new string[arraySize];	// Create arrays1 on the heap to hold the lines read from the input file.
		string* arrayq1 = new string[arraySize];	// Create arrayq1 on the heap to hold the lines read from the input file.

		// Read the file into the array.
		fileCount1 = fileRead( dataFile1, arrayi1 );

		// Test code.
		cout << "Counted " << arraySize << " lines in " << INFILE1 << ", and read " << fileCount1 << " lines in." << endl;

		// Copy the array for Insertion Sort to the arrays for Shell Sort and Quick Sort.
		for (int i = 0; i < arraySize; i++)
		{
			arrays1[i] = arrayi1[i];
			arrayq1[i] = arrayi1[i];
		}

//Insertion Sort
		// Get the starting tick.
		start = clock();
		
		// Sort the array using Insertion Sort.
		insertionSort( arrayi1, arraySize );
		
		// Get the ending tick.
		end = clock();
		// Determine how long it too to read in the third file.
		iSort = end - start;

		// Write the sorted array to the output file.
		writeArray( arrayi1, arraySize, OUTFILE );

		// Print the results to the screen.
		cout << "Insertion Sort of " << OUTFILE << " took " << iSort / CLK_TCK << " seconds (" << iSort << " ticks)." << endl;

//Shell Sort
		// Get the starting tick.
		start = clock();

		// Sort the array using Shell Sort.
		shellSort( arrays1, arraySize );

		// Get the ending tick.
		end = clock();
		// Determine how long it too to read in the third file.
		sSort = end - start;

		// Write the sorted array to the output file.
		writeArray( arrays1, arraySize, OUTFILE );

		// Print the results to the screen.
		cout << "Shell Sort of " << OUTFILE << " took " << sSort / CLK_TCK << " seconds (" << sSort << " ticks)." << endl;

//Quick Sort
		// Get the starting tick.
		start = clock();

		// Sort the array using Quick Sort.
		quickSort( arrayq1, 0, arraySize - 1 );

		// Get the ending tick.
		end = clock();
		// Determine how long it too to read in the third file.
		qSort = end - start;

		// Write the sorted array to the output file.
		writeArray( arrayq1, arraySize, OUTFILE );

		// Print the results to the screen.
		cout << "Quick Sort of " << OUTFILE << " took " << qSort / CLK_TCK << " seconds (" << qSort << " ticks)." << endl;
	}
	// Close the file used for reading.
	dataFile1.close();

	// Pause so the user can read the screen.
	system( "PAUSE" );
	return 0;
}// End main().


// Function name:	fileCount()
// Purpose:		This function will count the number of lines in a file.
// Parameters:		The file handle to read.
// Returns:		The number of lines in the file.
// Preconditions:	none
// Postconditions:	none
int fileCount( ifstream& _handle )
{
	string fileStr = "";	// Variable to temporarily hold the contents read from the file.
	int length = 0;		// Variable to count the lines in the file.

	// Loop until End Of File, reading one number at a time.
	while ( !_handle.eof() )
	{
		// Test code.
		//cout << "Entered the fileCount() while() loop." << endl;

		// Read one line from dataFile1 into fileStr.  I know this is not fast.  I plan to add a buffered approach later.
		getline( _handle, fileStr );

		// Increment length.
		length++;

		// Test code.
		//cout << "Total values read so far: " << length << endl;
	}
	// Test code.
	//cout << "Exited the fileCount() while() loop." << endl;
	return length;
} // End fileCount().


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
		//cout << "Entered the fileRead() while() loop." << endl;

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
	// Test code.
	//cout << "Exited the fileRead() while() loop." << endl;
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

	// Test code.
	//cout << "Starting Insertion Sort" << endl;

	string temp = "";
	int loop = 0;
	for (int i = 0; i < _length; i++)
	{
		// Test code.
		//cout << "Inside the for() loop." << endl;

		loop = i;
		while ( loop > 0 && _array[loop - 1] > _array[loop] )
		{
			// Test code.
			//cout << "Inside the while() loop." << endl;

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
	// Test code.
	//cout << "Exiting Insertion Sort" << endl;
} // End insertionSort().


// Function name:	shellSort()
// Purpose:		This function will sort the contents of an array using the Shell Sort method.
// Parameters:		An array to sort, and the size of that array.
// Returns:		none
// Preconditions:	none
// Postconditions:	none
void shellSort( string _array[], int _length )
{
	//Test code.
	//cout << "Starting Shell sort." << endl;
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
	string temp = "";
	// Test code.
	//cout << temp << endl;

	// Start with a gap size of 1/2 _length, and cut it in half again each time we loop.
	for ( gap = _length/2; gap > 0; gap/= 2 )
	{
		//Test code.
		//cout << "Starting first for() loop." << endl;
		// Start at the current gap size, and increment until the end of the array.
		for ( i = gap; i < _length ; i++ )
		{
			//Test code.
			//cout << "Starting second for() loop." << endl;
			// Put the current array position into temp.
			temp = _array[i];
			// Loop through this section.
			for( j = i; j >= gap ; j-= gap )
			{
				//Test code.
				//cout << "Starting third for() loop." << endl;
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
	string temp = "";		// A temporary variable to use for swapping values.
	string pivot = "";		// The pivot.

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
