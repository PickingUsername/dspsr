//-*-C++-*-

/* $Source: /cvsroot/dspsr/dspsr/Kernel/Classes/dsp/Transformation.h,v $
   $Revision: 1.8 $
   $Date: 2003/07/01 05:14:07 $
   $Author: hknight $ */

#ifndef __Transformation_h
#define __Transformation_h

#include <string>
#include <iostream>

#include <stdlib.h>

#include "environ.h"

#include "Error.h"

#include "dsp/Operation.h"

namespace dsp {

  //! Defines the interface by which Transformations are performed on data
  /*! This pure virtual template base class defines the manner in
    which various digital signal processing routines are performed. */
  template <class In, class Out>
  class Transformation : public Operation {

  public:

    //! All operations must define their behaviour
    enum Behaviour { inplace, outofplace, anyplace };

    //! All sub-classes must specify name and capacity for inplace operation
    Transformation (const char* _name, Behaviour _type) : Operation (_name)
    { type = _type; }

    //! Virtual destructor
    virtual ~Transformation () { }

    //! Set the container from which input data will be read
    //! Over-ride this to check input is of right type (use dynamic_cast)
    virtual void set_input (In* input);

    //! Set the container into which output data will be written
    //! Over-ride this to check output is of right type (use dynamic_cast)
    virtual void set_output (Out* output);

    //! Return pointer to the container from which input data will be read
    virtual In* get_input () const { return input; }
 
    //! Return pointer to the container into which output data will be written
    virtual Out* get_output () const { return output; }

    //! Return the Transformation type
    Behaviour get_type() { return type; }

  protected:

    //! Define the Operation pure virtual method
    virtual void operation ();

    //! Declare that sub-classes must define a transformation method
    virtual void transformation () = 0;

    //! Container from which input data will be read
    Reference::To <In> input;

    //! Container into which output data will be written
    Reference::To <Out> output;

  private:

    //! Behaviour of Transformation
    Behaviour type;

  };
  
}

template <class In, class Out>
void dsp::Transformation<In, Out>::operation ()
{
  if (verbose)
    cerr << "Transformation["+name+"]::operate" << endl;

  // If inplace is true, then the input and output should be of the same type....
  if( type==inplace && !input.ptr() && output.ptr() )
    input = (In*)output.get();
  if( type==inplace && !output.ptr() && input.ptr() )
    output = (Out*)input.get();

  if (!input)
    throw Error (InvalidState, string("Transformation["+name+"]::operate").c_str(),
		 "no input");

  if (input->get_ndat() < 1)
    throw Error (InvalidState, string("Transformation["+name+"]::operate").c_str(),
		 "empty input- input=%p input->ndat="UI64,
		 input.get(),input->get_ndat());

  string reason;
  if (!input->state_is_valid (reason))
    throw Error (InvalidState, string("Transformation["+name+"]::operate").c_str(),
		 "invalid input state: " + reason);

  if ( type!=inplace && !output)
    throw Error (InvalidState, string("Transformation["+name+"]::operate").c_str(),
		 "no output");

  //! call the pure virtual method defined by sub-classes
  transformation ();

  if ( type!=inplace && !output->state_is_valid (reason))
    throw Error (InvalidState, string("Transformation["+name+"]::operate").c_str(),
		 "invalid output state: " + reason);
}

template <class In, class Out>
void dsp::Transformation<In, Out>::set_input (In* _input)
{
  if (verbose)
    cerr << "dsp::Transformation["+name+"]::set_input ("<<_input<<")"<<endl;

  input = _input;

  if ( type == outofplace && input && output
       && (const void*)input == (const void*)output )
    throw Error (InvalidState, string("Transformation["+name+"]::set_input").c_str(),
		 "input must != output");
}

template <class In, class Out>
void dsp::Transformation<In, Out>::set_output (Out* _output)
{
  if (verbose)
    cerr << "dsp::Transformation["+name+"]::set_output ("<<_output<<")"<<endl;

  if (type == inplace && input.get() && (const void*)input.get()!=(const void*)_output ){
    Error er(InvalidState, string("Transformation["+name+"]::set_output").c_str(),
		 "inplace transformation input must equal output");
    cerr << er << endl;
    exit(-1);
  }

  output = _output;

  if ( type == outofplace && input && output 
       && (const void*)input.get() == (const void*)output.get() ){
    Error er(InvalidState, string("Transformation["+name+"]::set_output").c_str(),
		 "output must != input");
    cerr << er << endl;
    exit(-1);
  }

}


#endif
