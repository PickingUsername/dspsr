//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Signal/Pulsar/dsp/Fold.h,v $
   $Revision: 1.2 $
   $Date: 2002/09/24 07:55:45 $
   $Author: wvanstra $ */


#ifndef __Fold_h
#define __Fold_h

#include <vector>

#include "Operation.h"
#include "Observation.h"

class polyco;

namespace dsp {

  //! Fold Timeseries data into average profile(s)
  /*! 
    This Operation does not modify the Timeseries.  Rather, it accumulates
    the (folded) average pulse profile data within its data structures.
  */
  class Fold : public Operation, public Observation {

  public:
    
    //! Constructor
    Fold () : Operation ("Fold", inplace) { init(); }
    
    //! Destructor
    ~Fold ();

    //! Set the number of phase bins into which data will be folded
    void set_nbin (int nbin);

    //! Set the number of phase bins into which data will be folded
    int get_nbin () const;

    //! Set the period at which to fold data (in seconds)
    void set_folding_period (double folding_period);

    //! Get the average folding period
    double get_folding_period () const;

    //! Set the phase polynomial(s) with which to fold data
    void set_folding_polyco (polyco* folding_polyco);

    //! Get the mid-time of the integration
    MJD get_midtime () const;

    //! Get the number of seconds integrated into the profile(s)
    double get_integration_length () const;

    //! Reset all phase bin totals to zero
    void zero ();

  protected:

    //! The operation folds the data into the profile
    virtual void operation ();

    //! The number of seconds integrated into the profile(s)
    double integration_length;

    //! The MJD of the last-integrated time sample's tail edge
    MJD end_time;

    //! Period at which to fold data (CAL)
    double folding_period;

    //! Phase polynomial(s) with which to fold data (PSR)
    Reference::To<polyco> folding_polyco;

    //! Number of time samples integrated into each phase bin
    vector<unsigned> hits;

    //! Integrated total amplitudes
    vector<float> amps;


  private:
    void init();
    
  };

}

#endif // !defined(__Fold_h)
