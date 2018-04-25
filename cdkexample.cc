/* Project:	Program 6
 * File:	cdkexample.cc
 * Name:	Hepson Sanchez
 * Net-ID:	hms160230
 * Course:	CS 3377.002
 * Date:	4/24/2018
 */

#include <iostream>
#include "cdk.h"
#include <stdint.h>
#include <fstream>
#include <sstream>
#include <string>

#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 18
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;

class BinaryFileHeader
{
public:
  uint32_t magicNumber;
  uint32_t versionNumber;
  uint64_t numRecords;
};

const int maxRecordStringLength = 25;
class BinaryFileRecord
{
public:
  uint8_t strLength;
  char stringBuffer[maxRecordStringLength];
};

int main()
{

  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[] = {"R0", "a", "b", "c", "d", "e"};
  const char 		*columnTitles[] = {"C0", "a", "b", "c", "d", "e"};
  int		boxWidths[] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[] = {vMIXED, vMIXED, vMIXED, vMIXED,  vMIXED,  vMIXED};

  //initialize the Cdk screen.
  window = initscr();
  cdkscreen = initCDKScreen(window);

  //start CDK Colors
  initCDKColor();

  //create the matrix.  Need to manually cast (const char**) to (char **)
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **) columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }

  //display the Matrix
  drawCDKMatrix(myMatrix, true);
  //create input binary file stream
  ifstream binInFile("cs3377.bin", ios::in | ios::binary);

  //display headers---------------------------------------------------------
  BinaryFileHeader *myHeader = new BinaryFileHeader();
  binInFile.read((char *) myHeader, sizeof(BinaryFileHeader));
  //convert magic number to hex and make to char array
  stringstream magNumSS;
  magNumSS << "0x" << hex << uppercase <<  myHeader->magicNumber;
  string magNumString = magNumSS.str();
  char magNumChar[10];
  strcpy(magNumChar, magNumString.c_str());
  //make version number to char array
  char verNum[32];
  sprintf(verNum, "%u", myHeader->versionNumber);
  //make number of records to char array
  char numRec[64];
  sprintf(numRec, "%lu", myHeader->numRecords);
 
  //concatonate labels to all 3 numbers and keep as char arrays
  char magText[17] = "Magic: ";
  for(int i=7; i<17; i++)
  {
    magText[i] = magNumChar[i-7];
  }
  char verText[41] = "Version: ";
  for(int i=9; i<41; i++)
  {
    verText[i] = verNum[i-9];
  }
  char recText[44] = "NumRecords: ";
  for(int i=12; i<44; i++)
  {
    recText[i] = numRec[i-12];
  }

  //add char arrays to matrix
  setCDKMatrixCell(myMatrix, 1, 1, magText);
  setCDKMatrixCell(myMatrix, 1, 2, verText);
  setCDKMatrixCell(myMatrix, 1, 3, recText);

  drawCDKMatrix(myMatrix, true);   //required
  
  //display records---------------------------------------------------------------------------
  for(int i=0; i<4; i++)
  {
    BinaryFileRecord *myRecord = new BinaryFileRecord();
    binInFile.read((char *) myRecord, sizeof(BinaryFileRecord));
    //concatonate strLength with "strlen: " and convert to char array
    stringstream lengthSS;
    lengthSS << "strlen: " << myRecord->strLength;
    string lengthString = lengthSS.str();
    char lengthChar[16];
    strcpy(lengthChar, lengthString.c_str());

    setCDKMatrixCell(myMatrix, i+2, 1, lengthChar);
    setCDKMatrixCell(myMatrix, i+2, 2, myRecord->stringBuffer);
  }

  drawCDKMatrix(myMatrix, true);  //required

  //pause until a key is pressed--------------------------------------------------------------
  unsigned char x;
  cin >> x;

  //cleanup screen
  endCDK();
  
  //cleanup dynamic memory
  delete myHeader;
  return 0;
}
