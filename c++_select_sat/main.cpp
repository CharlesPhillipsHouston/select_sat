//  select sats 1 oct 2022
//  Copyright © 2019 charles phillips. All rights reserved.
//  read in a TLE, all three lines, and getline the individual lines
// generally to just collect a file for a particular satellite though parameters are read
// runs on Mike's computer, on the MacBook Pro, and on the Mac Mini

#include <iostream>
#include <stdio.h>
#include <string> // c++ strings
#include <cstring>
#include <fstream>
#include <stdlib.h> // atoi, atof not used yet
#include <math.h>  // math functions

using namespace::std; // added c++ namespace

// set up constants needed
#define MU  398600.4418  // gravitational parameter
#define min_per_day  1440  // minutes per day
#define sec_per_day  86400   //seconds per day
#define PI        3.141592653589
#define Two_Pi  6.283185307  // 2 times Pi (for use in finding semi-major axis)

string line, *p;  // what is the *p??

string name_card = "a";  // now using c++ strings
string second_card = "b";
string third_card = "c";

// cards all are strings

// parameters start as strings and are converted later
string cardno = "d";
string satno1 = "d"; // this is satno from card 2
string int_des = "e"; // will always be a string
string epoch = "f"; // may convert to time
string inclination = "f";
string mean_anomaly = "h";
string big_eccentricity = "i";


/* define variables, no structure here!!
 used to have variables defined here, now call all of them strings and convert
int card1;
int satno1;
char sat_name[12] = "\0\0\0\0\0\0\0\0\0\0\0"; // name assigned, fill with \0
char int_des;  // char is ok? want to discard blanks
float epoch; // not yet scanned
char card2;  // same as card1
int satno2; // same as satno1
float inclination;
float mean_anomaly;
float big_eccentricity; // format has implied decimal point
float eccentricity;  // divide to get actual value
float arg_perigee; // argument of perigee
float raan;  // Right Ascension of Ascending Node
float mean_motion; // revs per day
float apogee = 0.0; // initial value
float perigee = 0.0; // initial value
float intermediate_one = 0.0;
// (mean motion x2 xpi/sec per day) not squared, inverted
float intermediate_two = 0.0; // intermediate_one, squared
float intermediate_three = 0.0; // intermediate two, cube root
float semi_major = 0.0; // semi-major axis cube root of: mu * intermediate three squared
// set variables as float - intermediate_one, _two, _three
// they were defined as long integers!
 
*/

int main(void)
{
  // string homeDir = getenv("HOME"); // converting to dormer getenv
    string ifname = "/Users/charlesphillips/Desktop/common_files/input_tle.txt";
    
    // Users/charlesphillips/Desktop/common_files/input_tle.txt
    
    string ofname = "/Users/charlesphillips/Desktop/common_files/output_select.txt";
    
    ifstream fin(ifname);  // file in
   ofstream fout(ofname);  // file out
 
    int i = 1;
    
    while (!fin.eof())  // this causes infinite loop
  //  while (i < 9)  // changed this
    
    {
        getline(fin, line);  // get a line from fin
// need to know which line we are scanning
 // with next line, will not read name_card
    string name_card = line.substr(0,80); // try to read name card
        string cardno = line.substr(0);
        
        getline(fin, line);  // get second card??
        string second_card = line.substr(0,80);
   // can only run with 0 in substr
  // without that line, still has default value!
        
 //       cout << "name " << name_card << endl;
 //       cout << "what is this? " << second_card << endl;
        
        fout << "name " << name_card << "cardno " << cardno << endl;
        fout << "second card? " << second_card << "cardno " << cardno << endl;
       i++;
    /*
        if (satno1 == 29249)
        {
            printParameters (spOutput);  //creates file with just 29249
        }
    
        else if (satno1 == 90122)
        {
            printParameters(spOutput90122);
        }
        else if (satno1 == 90103)
        {
            printParameters (spOutput90103);  //creates file
        }
        else if (satno1 == 90097)
        {
            printParameters(spOutput90097);
        }
        else
    
        {
            printParameters(stdout); //debug just print to terminal
            printf("\n");  // if you output to screen add a CR
        }
     */
    } // end while reading input file
    
    fin.close();  // duh close fin
    fout.close();
        
    return 0;
}  // end main, 
