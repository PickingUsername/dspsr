//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Signal/Pulsar/dsp/PhaseSeries.h,v $
   $Revision: 1.9 $
   $Date: 2003/08/22 15:49:16 $
   $Author: wvanstra $ */

#ifndef __PhaseSeries_h
#define __PhaseSeries_h

#include <vector>

#include "dsp/TimeSeries.h"

class polyco;

namespace dsp {
  
  class PhaseSeries : public TimeSeries {

    friend class Fold;

  public:

    //! Null constructor
    PhaseSeries ();

    //! Destructor
    ~PhaseSeries ();

    //! Allocate the space required to store nsamples time samples.
    virtual void resize (int64 nsamples);

    //! Set this equal to prof
    PhaseSeries& operator = (const PhaseSeries& prof);

    //! Add prof to this
    PhaseSeries& operator += (const PhaseSeries& prof);

    //! Set the reference phase (phase of bin zero)
    void set_reference_phase (double phase) { reference_phase = phase; }
    //! Get the reference phase (phase of bin zero)
    double get_reference_phase () const { return reference_phase; }

    //! Set the period at which to fold data (in seconds)
    void set_folding_period (double folding_period);
    //! Get the period at which to fold data (in seconds)
    double get_folding_period () const;

    //! Set the phase polynomial(s) with which to fold data
    void set_folding_polyco (const polyco* folding_polyco);
    //! Get the phase polynomial(s) with which to fold data
    const polyco* get_folding_polyco () const;

    //! Get the number of seconds integrated
    double get_integration_length () const { return integration_length; }

    virtual MJD get_end_time () const { return end_time; }

    //! Get the number of phase bins
    unsigned get_nbin () const { return ndat; }

    //! Get the hit for the given bin
    unsigned get_hit (unsigned ibin) const { return hits[ibin]; }

    //! Get the mid-time of the integration
    MJD get_mid_time () const;

    //! Reset all phase bin totals to zero
    void zero ();

    //! Over-ride Observation::combinable_rate
    bool combinable_rate (double test_rate) const { return true; }

  protected:

    //! Period at which CAL data is folded
    double folding_period;

    //! Phase polynomial(s) with which PSR is folded
    Reference::To<const polyco> folding_polyco;

    //! Reference phase (phase of bin zero)
    double reference_phase;

    //! Number of time samples integrated into each phase bin
    vector<unsigned> hits;

    //! The number of seconds integrated into the profile(s)
    double integration_length;

    //! The MJD of the last-integrated time sample's tail edge
    MJD end_time;

    //! Return true when Observation can be integrated (and prepare for it)
    bool mixable (const Observation& obs, unsigned nbin,
		  int64 istart=0, int64 fold_ndat=0);

  };

}

#endif
