/*
 * gs.h
 *
 * author: a.vogel@rub.de
 *
 */

#ifndef GAUSS_SEIDEL_H
#define GAUSS_SEIDEL_H


#include "linear_iterator.h"

class GaussSeidel
: public LinearIterator
{
	public:
		/// constructor
		GaussSeidel() {};

		/// @copydoc LinearIterator::apply
		virtual bool precond(Vector<double>& c, const Vector<double>& r) const;

		virtual LinearIterator* clone() const {return new GaussSeidel(*this);}
};

class BackwardGaussSeidel
: public LinearIterator
{
	public:
		/// constructor
		BackwardGaussSeidel() {};

		/// @copydoc LinearIterator::apply
		virtual bool precond(Vector<double>& c, const Vector<double>& r) const;

		virtual LinearIterator* clone() const {return new BackwardGaussSeidel(*this);}
};

class SymmetricGaussSeidel
: public LinearIterator
{
	public:
		/// constructor
		SymmetricGaussSeidel() {};

		/// @copydoc LinearIterator::apply
		virtual bool precond(Vector<double>& c, const Vector<double>& r) const;

		virtual LinearIterator* clone() const {return new SymmetricGaussSeidel(*this);}
};


#endif // GAUSS_SEIDEL_H
