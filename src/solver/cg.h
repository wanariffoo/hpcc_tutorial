/*
 * cg.h
 *
 * author: a.vogel@rub.de
 *
 */

#ifndef CG_H
#define CG_H


#include "algebra/vector.h"
#include "algebra/ell_matrix.h"
#include "precond/linear_iterator.h"
#include "solver/linear_solver.h"
#include <cstddef>


/** @brief The conjugate gradient solver
 * This class implements the conjugate gradient method.
 *
 * It can be preconditioned with an iterator B that is an approximation of A 
 * and typically easy to invert. The Preconditioner (if any) is specified via the 
 * LinearIterator interface. Examples for LinearIteratora are Jacobi and GaussSeidel.
 */
class CG
 : public LinearSolver
{
	public:
		/// constructor
		CG();

		/// constructor with matrix
		CG(const ELLMatrix<double>& mat);

		/// set corrector method
		void set_linear_iterator(LinearIterator& linIter);

		/** @brief Set convergence control parameters
		 *
		 * @param maxIter maximal number of iterations
		 * @param minRes  absolute residuum norm value to be reached
		 * @param minRed  residuum norm reduction factor to be reached
		 */
		void set_convergence_params(std::size_t nIter, double minDef, double minRed);

		/// Set output verbosity
		void set_verbose(bool verbose);

		/// set matrix
		virtual bool init(const ELLMatrix<double>& mat);

		/** @brief Solves the linear system using the conjugate gradient method
		 * Solve Ax = b for x.
		 *
		 * @param x  solution
		 * @param b  right-hand side
		 * @return   false on failure; true otherwise
		 */
		virtual bool solve(Vector<double>& x, const Vector<double>& b) const;

		virtual LinearIterator* clone() const {return new CG(*this);}

	private:
		LinearIterator* m_pLinearIterator;

		std::size_t m_maxIter;
		double m_minRes;
		double m_minRed;

		bool m_bVerbose;
};

#endif // CG_H
