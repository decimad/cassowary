// $Id: test-ClVariable.cc,v 1.13 1999/04/20 00:25:36 gjb Exp $
//
// Cassowary Incremental Constraint Solver
// Original Smalltalk Implementation by Alan Borning
// This C++ Implementation by Greg J. Badros, <gjb@cs.washington.edu>
// http://www.cs.washington.edu/homes/gjb
// (C) 1998, 1999 Greg J. Badros and Alan Borning
// See ../LICENSE for legal details regarding this software
//
// test-ClVariable.cc

#include "Cl.h"

int
main( char **, int )
{
  ClVariable clv1("clv1");
  ClVariable clv2("clv2",2.4);
  cout << clv1 << endl;
  cout << clv2 << endl;

  return 0;
}
