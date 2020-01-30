/*
 * jacobi.h
 *
 * author: a.vogel@rub.de
 *
 */

#ifndef JACOBI_H
#define JACOBI_H


#include "linear_iterator.h"

class Jacobi
: public LinearIterator
{
	public:
		/// constructor
		Jacobi();

		/// constructor with damping factor
		Jacobi(double damp);

		/// set damping factor
		void set_damping(double damp) {m_damp = damp;}

		/// set matrix
		virtual bool init(const ELLMatrix<double>& mat);

		/// @copydoc LinearIterator::apply
		virtual bool precond(Vector<double>& c, const Vector<double>& r) const;

		virtual LinearIterator* clone() const {return new Jacobi(*this);}

	protected:
		double m_damp;

		Vector<double> m_diag;
};

#endif // JACOBI_H
