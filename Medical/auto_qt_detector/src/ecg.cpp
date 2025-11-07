
#include "stdafx.h"
#include "lib/lib.h"
#include <cstring>
// #include <stdio.h>
// #include <string>
// #include <sstream>
// #include <iomanip>

wchar_t params[_MAX_PATH] = L"params";
//char params[_MAX_PATH] = "params";

// void tic();
// void toc();
void help(char*);
int parse_params(class EcgAnnotation &ann);
void change_extension(wchar_t* path, const wchar_t* ext);
void change_extension(char* path, const char* ext);

static wchar_t anncodes [51][10] =  { L"notQRS", L"N",       L"LBBB",    L"RBBB",     L"ABERR", L"PVC",     //  0-5
                                      L"FUSION", L"NPC",     L"APC",     L"SVPB",     L"VESC",  L"NESC",    //  6-11
                                      L"PACE",   L"UNKNOWN", L"NOISE",   L"q",        L"ARFCT", L"Q",       // 12-17
                                      L"STCH",   L"TCH",     L"SYSTOLE", L"DIASTOLE", L"NOTE",  L"MEASURE", // 18-23
                                      L"P",      L"BBB",     L"PACESP",  L"T",        L"RTM",   L"U",       // 24-29
                                      L"LEARN",  L"FLWAV",   L"VFON",    L"VFOFF",    L"AESC",  L"SVESC",   // 30-35
                                      L"LINK",   L"NAPC",    L"PFUSE",   L"(",        L")",     L"RONT",    // 36-41
          //user defined beats//
                                      L"(p",     L"p)",      L"(t",      L"t)",       L"ECT",               // 42-46
                                      L"r",      L"R",       L"s",       L"S"};                             // 47-50
// [39, 40] - [start Q, end S], i.e. 40 is J point
//       46 - ect Ectopic of any origin beat
// So the whole sequence should look like:
//   (P  P  P)  (Q   Q  R  S  S)  (T  T  T):
//   42 24  43  39  15 47 49  40  44 27  45           
//   alternate QRS: 17 48 50

int main(int argc, char* argv[])  // no unicode args
{
  // These are for if we want to save heart rate and annotations to .hrv and .atr files later:
  // wchar_t annName[_MAX_PATH];
  // wchar_t hrvName[_MAX_PATH];
  // This one is for the csv:
  char csvName[_MAX_PATH];

  if (argc < 2) { help(argv[0]); }
  else {
    int leadNumber = 0;
    if (argc >= 2 + 1) {
      wchar_t *end;  // NULL
      leadNumber = wcstol( (const wchar_t*)argv[2], &end, 10 ) - 1;
      if (leadNumber < 0) leadNumber = 0;  // TODO: this arg is now ignored.  remove it.
    }
    
    class Signal signal;
    if (signal.ReadFile(argv[1])) {

      int size = signal.GetLength();
      double sr = signal.GetSR();
      int h, m, s, ms;
      int msec = int(((double)size / sr) * 1000.0);
      signal.mSecToTime(msec, h, m, s, ms);

      wprintf(L"  leads: %d\n", signal.GetLeadsNum());
      wprintf(L"     sr: %.2lf Hz\n", sr);
      wprintf(L"   bits: %d\n", signal.GetBits());
      wprintf(L"    UmV: %d\n", signal.GetUmV());
      wprintf(L" length: %02d:%02d:%02d.%03d\n\n", h, m, s, ms);

      // Find filters directory; assuming it's alongside executable (Linux only!):
      wchar_t filt_path[PATH_MAX];
#ifdef __linux__
      char filt_dir[PATH_MAX];
      readlink("/proc/self/exe", filt_dir, PATH_MAX);  // get binary path
      char* slash_loc = strrchr(filt_dir, '/');
      memcpy(slash_loc, "/filters\0", 9);  // filt_dir now contains full path of filters dir
      mbstowcs(filt_path, filt_dir, PATH_MAX);
#else
      // TODO: make versions for other OSes.  for now we just assume it's in current directory.
      mbstowcs(filt_path, "./filters\0", 10);
#endif

      for (int cur_lead = 0; cur_lead < signal.GetLeadsNum(); cur_lead++)  // annotate all leads
	{
	  // double* data = signal.GetData(leadNumber);
	  double* data = signal.GetData(cur_lead);
	  
	  class EcgAnnotation ann;  //default annotation params
	  if (argc >= 3 + 1) {
	    //wcscpy_s(params, _MAX_PATH, argv[3]);
	    //wcscpy(params, (const wchar_t*)argv[3] );
	    mbstowcs( params, argv[3], PATH_MAX );
	    parse_params(ann);
	  }
	  
	  wprintf(L" working on lead %i.\n", cur_lead+1);
	  wprintf(L" getting QRS complexes... ");
	  //tic();
	  int** qrsAnn = ann.GetQRS(data, size, sr, filt_path);         //get QRS complexes
	  if (qrsAnn) {
	    wprintf(L" %d beats.\n", ann.GetQrsNumber());
	    ann.GetEctopics(qrsAnn, ann.GetQrsNumber(), sr);        //label Ectopic beats
	    
	    wprintf(L" getting P, T waves... ");
	    int annNum = 0;
	    int** ANN = ann.GetPTU(data, size, sr, filt_path, qrsAnn, ann.GetQrsNumber());     //find P,T waves
	    if (ANN) {
	      annNum = ann.GetEcgAnnotationSize();
	      wprintf(L" done.\n");
	      //toc();
	      wprintf(L"\n");

	      //save ECG annotation (.atr file)
	      // mbstowcs( annName, argv[1], PATH_MAX );
	      // change_extension(annName, L".atr");
	      // ann.SaveAnnotation(annName, ANN, annNum);
	    }
	    else {
	      ANN = qrsAnn;
	      annNum = 2 * ann.GetQrsNumber();
	      wprintf(L" failed.\n");
	      //toc();
	      wprintf(L"\n");
	    }
	    
	    // save annotations to a CSV file:
	    strcpy(csvName, argv[1]);
	    change_extension(csvName, ".csv");
	    FILE *fp;
	    if (cur_lead == 0) {
	      fp = fopen(csvName, "w");  // create new file
	      fprintf(fp, "%lf\n", sr);  // first line is the sample rate
	      // TODO: should probably put some other stuff on first line too, like start time
	    }
	    else {
	      fp = fopen(csvName, "a");  // append to existing file
	    }
	    for (int i = 0; i < annNum; i++) {
	      int smpl = ANN[i][0];
	      int type = ANN[i][1];

	      // if you want time from start of recording:
	      //msec = int(((double)smpl / sr) * 1000.0);
	      //signal.mSecToTime(msec, h, m, s, ms);
	      //wprintf(L"%10d %02d:%02d:%02d.%03d   %S\n", smpl, h, m, s, ms, anncodes[type]);
	      
	      fprintf(fp, "%i,%i,%S\n", cur_lead+1, smpl, anncodes[type]);
	      // leadNumber is 0-indexed, but we save it to the csv 1-indexed.
	    }
	    fclose(fp);
	    
	    // saving HR seq:
	    /*
	    vector<double> rrs;
	    vector<int> rrsPos;
	    
	    // wcscpy( hrvName, (const wchar_t*)argv[1] );
	    mbstowcs( hrvName, argv[1], PATH_MAX );
	    change_extension(hrvName, L".hrv");
	    if (ann.GetRRseq(ANN, annNum, sr, &rrs, &rrsPos)) {
	      // Convert name to char* for fopen():
	      char buffer[PATH_MAX];
	      wcstombs(buffer, hrvName, sizeof(buffer) );
	      
	      // FILE *fp = fopen((const char*)hrvName, "wt");  // no unicode
	      fp = fopen(buffer, "wt");  // no unicode
	      for (int i = 0; i < (int)rrs.size(); i++)
	    	{ fwprintf(fp, L"%lf\n", rrs[i]); }
	      fclose(fp);
	      
	      wprintf(L"\n mean heart rate: %.2lf\n", signal.Mean(&rrs[0], (int)rrs.size()));
	    }
	    */
	  }
	  else {
	    wprintf(L" could not get QRS complexes. make sure you have got \"filters\" directory in the ecg application dir.\n\n");
	    continue;
	  }
	}
    }
    else {
      wprintf(L" failed to read %s file\n", argv[1]);
      exit(1);
    }
  }

  return 0;
}

void help(char* bin_name)
{
  wprintf(L"usage: %s physionetfile.dat [LeadNumber] [params]\n", bin_name );
  wprintf(L"       do not forget about \\filters dir to be present.\n");
}

// static LARGE_INTEGER m_nFreq;
// static LARGE_INTEGER m_nBeginTime;

// void tic()
// {
//         QueryPerformanceFrequency(&m_nFreq);
//         QueryPerformanceCounter(&m_nBeginTime);
// }
// void toc()
// {
//         LARGE_INTEGER nEndTime;
//         __int64 nCalcTime;

//         QueryPerformanceCounter(&nEndTime);
//         nCalcTime = (nEndTime.QuadPart - m_nBeginTime.QuadPart) * 1000 / m_nFreq.QuadPart;

//         wprintf(L" processing time: %d ms\n", nCalcTime);
// }

void change_extension(wchar_t* path, const wchar_t* ext)
{
  for (int i = (int)wcslen(path) - 1; i > 0; i--) {
    if (path[i] == '.') {
      path[i] = 0;
      wcscat(path, ext);
      return;
    }
  }
  wcscat(path, ext);
}

void change_extension(char* path, const char* ext)
{
  for (int i = (int)strlen(path) - 1; i > 0; i--) {
    if (path[i] == '.') {
      path[i] = 0;
      strcat(path, ext);
      return;
    }
  }
  strcat(path, ext);
}

int parse_params(class EcgAnnotation &ann)
{
  // Convert name to char* for fopen():
  char buffer[PATH_MAX];
  wcstombs(buffer, params, sizeof(buffer) );

  // FILE* fp = fopen((const char*)params, "rt");  // no unicode
  FILE* fp = fopen(buffer, "rt");  // no unicode
        if (fp != 0) {
                ANNHDR hdr;
                int res = 0;
                res = fwscanf(fp, L"%*s %d %*s %d"
                                  L"%*s %lf %*s %lf %*s %lf %*s %d %*s %lf"
                                  L"%*s %lf %*s %lf %*s %lf %*s %lf"
                                  L"%*s %lf %*s %lf %*s %d",
                                   &hdr.minbpm, &hdr.maxbpm,
                                   &hdr.minQRS, &hdr.maxQRS, &hdr.qrsFreq, &hdr.ampQRS, &hdr.minUmV,
                                   &hdr.minPQ, &hdr.maxPQ, &hdr.minQT, &hdr.maxQT,
                                   &hdr.pFreq, &hdr.tFreq, &hdr.biTwave);
                if (res == 14) {
                        PANNHDR phdr = ann.GetAnnotationHeader();
			memcpy(phdr, &hdr, sizeof(ANNHDR));
                        wprintf(L" using annotation params from file %s\n", params);
                        wprintf(L"  minBpm  %d\n"
                                L"  maxBpm  %d\n"
                                L"  minQRS  %lg\n"
                                L"  maxQRS  %lg\n"
                                L" qrsFreq  %lg\n"
                                L"  ampQRS  %d\n"
                                L"  minUmV  %lg\n"
                                L"   minPQ  %lg\n"
                                L"   maxPQ  %lg\n"
                                L"   minQT  %1f\n"
                                L"   maxQT  %lg\n"
                                L"   pFreq  %lg\n"
                                L"   tFreq  %lg\n"
                                L" biTwave  %d\n\n", hdr.minbpm, hdr.maxbpm,
                                                   hdr.minQRS, hdr.maxQRS, hdr.qrsFreq, hdr.ampQRS, hdr.minUmV,
                                                   hdr.minPQ, hdr.maxPQ, hdr.minQT, hdr.maxQT,
                                                   hdr.pFreq, hdr.tFreq, hdr.biTwave);
                        fclose(fp);
                        return 0;
                }
                else {
                        fclose(fp);
                        wprintf(L" failed to read %s annotation params file, using default ones instead.\n", params);
                        return res;
                }
        }
        else {
                wprintf(L" failed to open %s annotation params file, using default ones instead.\n", params);
                return -1;
        }
}
