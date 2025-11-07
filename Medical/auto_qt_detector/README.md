# README #

This project is an extension of Yuriy Chesnokov's code from the 2006 PhysioNet Computers in Cardiology challenge.  It was designed to measure QT intervals in ECG recordings, but is also able to annotate and measure other intervals such as RR, PR, etc.

The code was downloaded and merged from the following two sources:

* https://www.physionet.org/challenge/2006/sources/yuriy-chesnokov/
* http://www.codeproject.com/Articles/20995/ECG-Annotation-C-Library

It was originally very Windows-specific, and I have been working to make it more portable.  It should currently compile and run natively in Linux and Mac OS.  In Windows, it can be compiled using MinGW or Cygwin.

ISHNE file support has also been added.

### How do I run it? ###

A simple Makefile is included which builds `ecg_ann`.  The `filters` directory must always accompany this binary.

There is an example PhysioNet recording in `data/`.  To annotate s0010_re.dat: `./ecg_ann s0010_re.dat`.  Note that PhysioNet .dat files must also include the .hea header file.

The output of the ecg.cpp program is a csv file with [lead, sample number, feature] in each row.

You may want to edit the parameters (such as `maxQT`) in `ecgannotation.cpp`.  You can also edit them case-by-case in a text file, and point to the file with a command-line argument; see `parse_params()` in `ecg.cpp`.

### Who do I talk to? ###

* Current maintainer: Alex Page, alex.page@rochester.edu
* Original author: Yuriy Chesnokov