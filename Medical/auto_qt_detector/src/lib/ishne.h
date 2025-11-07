// This code is an extension/adaptation of the example ISHNE reader at
// http://www.thew-project.org/thew_ecg_format.htm, with the goal of making it
// portable to non-Windows systems.  It was completed in 2014 by Alex Page
// <alex.page@rochester.edu>.  The ISHNE format is described here:
// http://www.thew-project.org/papers/Badilini.ISHNE.Holter.Standard.pdf

#ifndef ISHNE_H
#define ISHNE_H

// TODO: use "#pragma once" instead of #include guards?

/////////////////// INCLUDES ////////////////////

#include <string>
#include <iostream>
#include <fstream>

//////////////////// STRUCTS ////////////////////

typedef struct ISHNEHeader{
  // IMPORTANT NOTE: {int=32 bit, short=16 bit, char=8 bit} are required for
  // data to be parsed correctly with this code!
  int 		Var_length_block_size;
  int 		Sample_Size_ECG;
  int		Offset_var_length_block;
  int		Offset_ECG_block;
  short int 	File_Version;
  char  	First_Name[40];
  char 		Last_Name[40];
  char		ID[20];
  short int 	Sex;
  short int 	Race;
  short int   	Birth_Date[3];
  short int   	Record_Date[3];
  short int   	File_Date[3];
  short int  	Start_Time[3];
  short int	nLeads;
  short int   	Lead_Spec[12];
  short int   	Lead_Qual[12];
  short int   	Resolution[12];
  short int   	Pacemaker;
  char		Recorder[40];
  short int	Sampling_Rate;
  char 		Proprietary[80];
  char		Copyright[80];
  char		Reserved[88];
} ISHNEHeader;

typedef struct ISHNEData{
  short int** 	data;
  // ISHNE always uses 16 bits per sample, and data[i][j] will give lead i,
  // sample j.

  // These are just so we have simple access to the size of the data array:
  short int 	nLeads;
  int 		samples_per_lead;

  ~ISHNEData()
  {
    if (data)
      {
	for(int i = 0; i < nLeads; i++) {
	  delete [] data[i];
	}
	delete [] data;
      }
  }
} ISHNEData;

//////////////////// FUNCTIONS ////////////////////

using namespace std;

ISHNEHeader readIshneHeader(string strFileName);
bool        saveIshneData(ISHNEHeader m_ISHNEHeader, short** data, string strFileName);
ISHNEData   readIshneECG(string strFileName);
void        readIshneAnnotation(string strFileName);

#endif  /* ISHNE_H */
