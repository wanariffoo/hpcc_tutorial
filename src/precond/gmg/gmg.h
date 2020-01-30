/*
 * gmg.h
 *
 * author: a.vogel@rub.de
 *
 */

#ifndef GMG_H
#define GMG_H


#include "precond/linear_iterator.h"
#include "solver/linear_solver.h"
#include "prolongation.h"
#include "grid/structured_multi_grid.h"
#include "disc/assemble_interface.h"
#include "algebra/ell_matrix.h"
#include "algebra/vector.h"

#include <memory>

template<std::size_t dim>
class GMG
: public LinearIterator
{
	public:
		/// constructor
		GMG(	StructuredMultiGrid<dim>& multiGrid,
				IAssemble<dim>& disc,
				IProlongation<dim>& prol,
				LinearIterator& smoother,
				LinearSolver& baseSolver);

        /// set num pre- and post-smoothing steps
        void set_num_smooth(std::size_t nu) {m_numPreSmooth = m_numPostSmooth = nu;}
    
        /// set num pre-smoothing steps
        void set_num_presmooth(std::size_t nu) {m_numPreSmooth = nu;}

        /// set num post-smoothing steps
        void set_num_postsmooth(std::size_t nu) {m_numPostSmooth = nu;}

        /// set base level
        void set_base_level(std::size_t lvl);
    
        /// set cycle type
        void set_cycle(int gamma);
        void set_cycle(const char type);

        /// set using rap product
        void set_rap(bool bRAP);

		/// @copydoc LinearIterator::init
		bool init(const ELLMatrix<double>& mat);

		/// @copydoc LinearIterator::apply
		virtual bool precond(Vector<double>& c, const Vector<double>& r) const;

		virtual LinearIterator* clone() const {return new GMG(*this);}

	protected:
        static const int _F_ = -1;
        static const int _V_ = 1;
        static const int _W_ = 2;
    
		bool precond_add_update(Vector<double>& c, Vector<double>& d, std::size_t lev, int cycle) const;

	protected:
		StructuredMultiGrid<dim>& m_multiGrid;
		IAssemble<dim>* m_pDisc;
		IProlongation<dim>* m_pProl;
		LinearIterator* m_pSmoother;
		LinearSolver* m_pBaseSolver;

		std::size_t m_numPreSmooth, m_numPostSmooth, m_baseLvl;
        int m_gamma;
        bool m_bRAP;

		std::vector<std::shared_ptr<LinearIterator>> m_vSmoother;
    
		std::vector<ELLMatrix<double>> m_vStiffMat;
		std::vector<ELLMatrix<double>> m_vProlongMat;

		std::vector<Vector<double>> m_vCtmp;
		std::vector<Vector<double>> m_vR;
};

#endif // GMG_H
