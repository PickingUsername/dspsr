//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Kernel/Formats/cpsr/dsp/rdisk.h,v $
   $Revision: 1.3 $
   $Date: 2001/07/31 20:25:56 $
   $Author: wvanstra $ */

#ifndef __RDISK_H
#define __RDISK_H

#include <iostream>
#include <string>
#include <vector>

#include "psr_cpp.h"

class rdisk {

 public:
  string machine;
  string path;

  rdisk () {};
  rdisk (const string& parse) { load (parse); }

  void load (const string& parse);

  // returns the available space in bytes
  double space () const;

  static void load (vector<rdisk>& disks, const char* filename);

};

inline ostream& operator << (ostream& ostr, const rdisk& rd)
{ return ostr << rd.machine << ":" << rd.path; }

#endif
