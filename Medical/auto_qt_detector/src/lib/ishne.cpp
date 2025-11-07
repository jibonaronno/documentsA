// This code is an extension/adaptation of the example ISHNE reader at
// http://www.thew-project.org/thew_ecg_format.htm, with the goal of making it
// portable to non-Windows systems.  It was completed in 2014 by Alex Page
// <alex.page@rochester.edu>.  The ISHNE format is described here:
// http://www.thew-project.org/papers/Badilini.ISHNE.Holter.Standard.pdf

#include "ishne.h"

// This function reads and returns the header of an ISHNE ECG file:
ISHNEHeader readIshneHeader(string strFileName)
{
  char		 magicnumber [8];
  unsigned short checksum;
  ISHNEHeader    m_ISHNEHeader;

  try
    {
      std::ifstream br(strFileName.c_str(), std::ios_base::in | std::ios_base::binary);

      // get magic number (i.e. file signature) and checksum. (TODO: use these?)
      br.read(        magicnumber, 8);
      br.read((char*)&checksum,    2);

      ///////////// read header /////////////////////
							
      br.read((char*)&m_ISHNEHeader.Var_length_block_size,   4);
      br.read((char*)&m_ISHNEHeader.Sample_Size_ECG,         4);
      br.read((char*)&m_ISHNEHeader.Offset_var_length_block, 4);
      br.read((char*)&m_ISHNEHeader.Offset_ECG_block,        4);
      br.read((char*)&m_ISHNEHeader.File_Version,            2);
      br.read(        m_ISHNEHeader.First_Name,             40);
      br.read(        m_ISHNEHeader.Last_Name,              40);
      br.read(        m_ISHNEHeader.ID,                     20);
      br.read((char*)&m_ISHNEHeader.Sex,                     2);
      br.read((char*)&m_ISHNEHeader.Race,                    2);
      br.read((char*) m_ISHNEHeader.Birth_Date,            2*3);
      br.read((char*) m_ISHNEHeader.Record_Date,           2*3);
      br.read((char*) m_ISHNEHeader.File_Date,             2*3);
      br.read((char*) m_ISHNEHeader.Start_Time,            2*3);
      br.read((char*)&m_ISHNEHeader.nLeads,                  2);
      br.read((char*) m_ISHNEHeader.Lead_Spec,            2*12);
      br.read((char*) m_ISHNEHeader.Lead_Qual,            2*12);
      br.read((char*) m_ISHNEHeader.Resolution,           2*12);
      br.read((char*)&m_ISHNEHeader.Pacemaker,               2);
      br.read(        m_ISHNEHeader.Recorder,               40);
      br.read((char*)&m_ISHNEHeader.Sampling_Rate,           2);
      br.read(        m_ISHNEHeader.Proprietary,            80);
      br.read(        m_ISHNEHeader.Copyright,              80);
      br.read(        m_ISHNEHeader.Reserved,               88);

      if (m_ISHNEHeader.Var_length_block_size > 0)
	{
	  char varblock [m_ISHNEHeader.Var_length_block_size];
	  br.read(varblock, m_ISHNEHeader.Var_length_block_size);
	  // TODO: then what?  varblock is local here
	}

      /////////// done with header //////////////////

      br.close();
    }
  catch (std::exception& ex)
    {
      fprintf( stderr, "Exception in reading ISHNE file header: %s\n", ex.what() );
    }

  return m_ISHNEHeader;
}

// This writes header and data to strFileName.  It returns true if successful.
// Note that data[i][j] == lead i, sample j.:
bool saveIshneData(ISHNEHeader m_ISHNEHeader, short** data, string strFileName)
{
  char magicnumber [] = "ISHNE1.0";
  unsigned short checksum = 0;  // TODO: set this correctly!  See Appendix B of
				// ISHNE format doc.
  try
    {
      std::ofstream br(strFileName.c_str(), std::ios_base::out | std::ios_base::binary);

      // HEADER:

      br.write(        magicnumber, 8);
      br.write((char*)&checksum,    2);
      br.write((char*)&m_ISHNEHeader.Var_length_block_size,   4);
      br.write((char*)&m_ISHNEHeader.Sample_Size_ECG,         4);
      br.write((char*)&m_ISHNEHeader.Offset_var_length_block, 4);
      br.write((char*)&m_ISHNEHeader.Offset_ECG_block,        4);
      br.write((char*)&m_ISHNEHeader.File_Version,            2);
      br.write(        m_ISHNEHeader.First_Name,             40);
      br.write(        m_ISHNEHeader.Last_Name,              40);
      br.write(        m_ISHNEHeader.ID,                     20);
      br.write((char*)&m_ISHNEHeader.Sex,                     2);
      br.write((char*)&m_ISHNEHeader.Race,                    2);
      br.write((char*) m_ISHNEHeader.Birth_Date,            2*3);
      br.write((char*) m_ISHNEHeader.Record_Date,           2*3);
      br.write((char*) m_ISHNEHeader.File_Date,             2*3);
      br.write((char*) m_ISHNEHeader.Start_Time,            2*3);
      br.write((char*)&m_ISHNEHeader.nLeads,                  2);
      br.write((char*) m_ISHNEHeader.Lead_Spec,            2*12);
      br.write((char*) m_ISHNEHeader.Lead_Qual,            2*12);
      br.write((char*) m_ISHNEHeader.Resolution,           2*12);
      br.write((char*)&m_ISHNEHeader.Pacemaker,               2);
      br.write(        m_ISHNEHeader.Recorder,               40);
      br.write((char*)&m_ISHNEHeader.Sampling_Rate,           2);
      br.write(        m_ISHNEHeader.Proprietary,            80);
      br.write(        m_ISHNEHeader.Copyright,              80);
      br.write(        m_ISHNEHeader.Reserved,               88);
      if (m_ISHNEHeader.Var_length_block_size > 0)
	{
	  char varblock [m_ISHNEHeader.Var_length_block_size];
          // TODO: get+write actual varblock, rather than garbage
	  br.write(varblock, m_ISHNEHeader.Var_length_block_size);
	}

      // DATA:

      int samples_per_lead = m_ISHNEHeader.Sample_Size_ECG / m_ISHNEHeader.nLeads;
      // br.seekg(m_ISHNEHeader.Offset_ECG_block);  // we should already be there
      for (int i = 0; i < samples_per_lead; i++)
      	{
      	  for (int j = 0; j < m_ISHNEHeader.nLeads; j++)
      	    {
      	      br.write((char*)&data[j][i], 2);
	      // TODO: write all at once instead of using loop(s)?
      	    }
      	}

      br.close();
    }
  catch (std::exception& ex)
    {
      fprintf( stderr, "Exception in writing ISHNE file: %s\n", ex.what() );
      return false;
    }

  return true;
}
// TODO: sanitize some of the stuff in the header?  maybe do that before passing it.
// TODO: lots of duplication (br.read vs br.write)... combine somehow?


// This function reads the ISHNE ECG files:
ISHNEData readIshneECG(string strFileName)
{
  int         i, j; 
  ISHNEHeader m_ISHNEHeader;
  ISHNEData   m_ISHNEData;

  try
    {
      // Load the header:
      m_ISHNEHeader = readIshneHeader(strFileName);  // TODO: check valid

      // Find file size:
      FILE *fp;
      fp = fopen(strFileName.c_str(), "r");
      if(fp == NULL) {
	// TODO: fail+return
      }
      long file_size;
      fseek(fp, 0, SEEK_END);
      file_size = ftell(fp);
      if(fp && fp != NULL) {
      	fclose(fp);
      }

      // Prepare the 2D array to receive data:
      // If Sample_Size_ECG is total number of samples:
      //     int samples_per_lead = m_ISHNEHeader.Sample_Size_ECG / m_ISHNEHeader.nLeads;
      // If Sample_Size_ECG is number of samples for a single lead:
      //     int samples_per_lead = m_ISHNEHeader.Sample_Size_ECG;
      // If Sample_Size_ECG is unreliable/nonsense:
      int samples_per_lead = (file_size - m_ISHNEHeader.Offset_ECG_block) / m_ISHNEHeader.nLeads / 2;
      m_ISHNEData.data = new short*[m_ISHNEHeader.nLeads];  // 1st dimension
      for(i = 0; i < m_ISHNEHeader.nLeads; i++) {
	m_ISHNEData.data[i] = new short[samples_per_lead];  // 2nd dimension
      }
      m_ISHNEData.nLeads = m_ISHNEHeader.nLeads;
      m_ISHNEData.samples_per_lead = samples_per_lead;

      // Open the file to read data:
      std::ifstream br(strFileName.c_str(), std::ios_base::in | std::ios_base::binary);

      // Seek to start of ECG data, and read it:
      br.seekg(m_ISHNEHeader.Offset_ECG_block);
      for (i = 0; i < samples_per_lead; i++)
      	{
      	  for (j = 0; j < m_ISHNEHeader.nLeads; j++)
      	    {
	      // Convention: data[i][j] == lead i, sample j
      	      br.read((char*)&m_ISHNEData.data[j][i], 2);
	      // TODO: read all at once instead of using loop(s)?
      	    }
      	}
      // Done reading data.
      br.close();
    }
  catch (std::exception& ex)
    {
      fprintf( stderr, "Exception in reading ISHNE data file: %s\n", ex.what() );
    }

  return m_ISHNEData;
}

// The function reads the binary formatted ISHNE annotation file:
void readIshneAnnotation(string strFileName)
{
  int			loc; 
  char			ann, internalUse;
  unsigned short	RR;
  ISHNEHeader		m_ISHNEHeader;

  try
    {
      // Load the header:
      m_ISHNEHeader = readIshneHeader(strFileName);  // TODO: check valid

      // Open the file to read data:
      std::ifstream br(strFileName.c_str(), std::ios_base::in | std::ios_base::binary);

      // Seek to start of annotation data, and read it:
      br.seekg(m_ISHNEHeader.Offset_ECG_block);
      br.read((char*)&loc, 4);  // read first location
      while (br.peek() != EOF)  // TODO: verify that this is working correctly
      	{
      	  // read ann, internalUse, and RR:
      	  br.read(       &ann,         1);
      	  br.read(       &internalUse, 1);
      	  br.read((char*)&RR,          2);
      	  loc += RR;
	  // TODO: make this not pointless, i.e. return these values
      	}
      // Done reading data.
      br.close();
    }

  catch (std::exception& ex)
    {
      fprintf( stderr, "Exception in reading ISHNE annotation file: %s\n", ex.what() );
    }

  return;
}

// TODO: replace try/catch blocks with proper error checking
