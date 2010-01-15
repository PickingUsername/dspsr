//-*-C++-*-
/***************************************************************************
 *
 *   Copyright (C) 2007 by Willem van Straten
 *   Licensed under the Academic Free License version 2.1
 *
 ***************************************************************************/

/* $Source: /cvsroot/dspsr/dspsr/Signal/Pulsar/dsp/LoadToFoldN.h,v $
   $Revision: 1.11 $
   $Date: 2010/01/15 11:55:26 $
   $Author: straten $ */

#ifndef __baseband_dsp_LoadToFoldN_h
#define __baseband_dsp_LoadToFoldN_h

#include "dsp/LoadToFold1.h"

class ThreadContext;

namespace dsp {

  class UnloaderShare;

  //! Multiple LoadToFold threads
  class LoadToFoldN : public LoadToFold {

  public:

    //! Constructor
    LoadToFoldN (unsigned nthread = 0);
    
    //! Destructor
    ~LoadToFoldN ();

    //! Set the number of thread to be used
    void set_nthread (unsigned);

    //! Set the configuration to be used in prepare and run
    void set_configuration (Config*);

    //! Set the Input from which data are read
    void set_input (Input*);

    //! Get the Input from which data are read
    Input* get_input ();

    //! Prepare to fold the input TimeSeries
    void prepare ();

    //! Run through the data
    void run ();

    //! Finish everything
    void finish ();

    //! Get the minimum number of samples required to process
    uint64_t get_minimum_samples () const;

  protected:

    //! Configuration parameters
    /*! call to set_configuration may precede set_nthread */
    Reference::To<Config> configuration;

    //! Input
    /*! call to set_input may precede set_nthread */
    Reference::To<Input> input;

    //! PhaseSeriesUnloader sharing
    std::vector< Reference::To<UnloaderShare> > unloader;

    //! Thread lock for Input::load
    ThreadContext* input_context;

    //! Condition for processing thread state changes
    ThreadContext* state_changes;

    //! The creator of new LoadToFold1 threads
    virtual LoadToFold1* new_thread ();

    //! The LoadToFold1 threads
    std::vector< Reference::To<LoadToFold1> > threads;

    //! The thread ids
    std::vector<pthread_t> ids;

    static void* thread (void*);

    void prepare_subint_archival ();
    void launch_threads ();

    static void share (LoadToFold1* fold, LoadToFold1* share);
    static void prepare (LoadToFold1* fold);
    static void wait (LoadToFold1* fold, LoadToFold1::State st);
    static void signal (LoadToFold1* fold, LoadToFold1::State st);

  };

}

#endif // !defined(__LoadToFoldN_h)





