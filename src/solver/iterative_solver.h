/*
 * iterative_solver.h
 *
 * author: a.vogel@rub.de
 *
 */

#ifndef ITERATIVE_SOLVER_H
#define ITERATIVE_SOLVER_H


#include "algebra/vector.h"
#include "algebra/ell_matrix.h"
#include "precond/linear_iterator.h"
#include "solver/linear_solver.h"
#include <cstddef>

/** @brief An iterative linear solver
 * This solver iterates the following process for a given matrix A and rhs b:
 *     r_k     = b - A * x_k   (residuum)
 *     c_k     = B^{-1} * r_i  (correction)
 *     x_{i+1} = x_i + c_i     (solution update)
 * with an iteration matrix B that is an approximation of A and typically easy to invert.
 * The inversion (and implicit definition) of B is provided by a corrector method that
 * has to be assigned to any instance of this class. It has to implement the IPreconditioner
 * interface. Examples for such "correctors" are Jacobi and GaussSeidel.
 */
class IterativeSolver
 : public LinearSolver
{
	public:
		/// constructor
		IterativeSolver();

		/// constructor with matrix
		IterativeSolver(const ELLMatrix<double>& mat);

		/// set corrector method
		void set_linear_iterator(LinearIterator& linIter);

		/** @brief Set convergence control parameters
		 *
		 * @param maxIter maximal number of iterations
		 * @param minRes  absolute residuum norm value to be reached
		 * @param minRed  residuum norm reduction factor to be reached
		 */
		void set_convergence_params(std::size_t maxIter, double minRes, double minRed);

		/// Set output verbosity
		void set_verbose(bool verbose);

		/// set matrix
		virtual bool init(const ELLMatrix<double>& mat);

		/** @brief Perform iterative process
		 * Iteration solves Ax = b for x.
		 *
		 * @param x  solution
		 * @param b  right-hand side
		 * @return   false on failure; true otherwise
		 */
		virtual bool solve(Vector<double>& x, const Vector<double>& b) const;

		virtual LinearIterator* clone() const {return new IterativeSolver(*this);}

	private:
		LinearIterator* m_pLinearIterator;

		std::size_t m_maxIter;
		double m_minRes;
		double m_minRed;

		bool m_bVerbose;
};

#endif // ITERATIVE_SOLVER_H
