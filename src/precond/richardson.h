/*
 * richardson.h
 *
 * author: a.vogel@rub.de
 *
 */

#ifndef RICHARDSON_H
#define RICHARDSON_H


#include "linear_iterator.h"


class Richardson
: public LinearIterator
{
	public:
		/// constructor
		Richardson() : m_eta(1.0) {};

		/// constructor
		Richardson(const double eta) : m_eta(eta) {};

		/// @copydoc LinearIterator::apply
		virtual bool precond(Vector<double>& c, const Vector<double>& r) const;
    
        /// set scale factor
        void set_factor(double eta) {m_eta = eta;}

 		virtual LinearIterator* clone() const {return new Richardson(*this);}
   
    protected:
        /// scale factor (should be: 2./(largest eigenvalue))
        double m_eta;
};

#endif // RICHARDSON_H
