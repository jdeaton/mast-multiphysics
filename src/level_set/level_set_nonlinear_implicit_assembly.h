/*
 * MAST: Multidisciplinary-design Adaptation and Sensitivity Toolkit
 * Copyright (C) 2013-2018  Manav Bhatia
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef __mast__level_set_nonlinear_implicit_assembly_h__
#define __mast__level_set_nonlinear_implicit_assembly_h__

// MAST includes
#include "base/nonlinear_implicit_assembly.h"


namespace MAST {
    
    // Forward declerations
    template <typename ValType> class FieldFunction;
    class LevelSetIntersection;
    class LevelSetInterfaceDofHandler;
    class LevelSetVoidSolution;
    
    
    class LevelSetNonlinearImplicitAssembly:
    public MAST::NonlinearImplicitAssembly {
    public:
        
        
        /*!
         *   constructor associates this assembly object with the system
         */
        LevelSetNonlinearImplicitAssembly();
        
        
        /*!
         *   destructor resets the association of this assembly object with
         *   the system
         */
        virtual ~LevelSetNonlinearImplicitAssembly();
        
        
        /*!
         *   attaches level set function to \p this
         */
        virtual void
        set_level_set_function(MAST::FieldFunction<Real>& level_set);

        
        /*!
         *   attaches indicator function to \p this.
         */
        virtual void
        set_indicator_function(MAST::FieldFunction<RealVectorX>& indicator);
        
        /*!
         *   clears association with level set function
         */
        virtual void
        clear_level_set_function();

        /*!
         *   the velocity function used to calculate topology sensitivity
         */
        virtual void
        set_level_set_velocity_function(MAST::FieldFunction<RealVectorX>& velocity);
        
        
        /*!
         *   clears the velocity function
         */
        virtual void
        clear_level_set_velocity_function();

        
        /*!
         *  @returns a reference to the level set function
         */
        MAST::LevelSetIntersection& get_intersection();

        
        /*!
         *  @returns a reference to the \p LevelSetInterfaceDofHandler object
         */
        MAST::LevelSetInterfaceDofHandler& get_dof_handler();

        
        /*!
         *    function that assembles the matrices and vectors quantities for
         *    nonlinear solution
         */
        virtual void
        residual_and_jacobian (const libMesh::NumericVector<Real>& X,
                               libMesh::NumericVector<Real>* R,
                               libMesh::SparseMatrix<Real>*  J,
                               libMesh::NonlinearImplicitSystem& S);

        
        virtual bool
        sensitivity_assemble (const MAST::FunctionBase& f,
                              libMesh::NumericVector<Real>& sensitivity_rhs);
        
        
        virtual void
        calculate_output_derivative(const libMesh::NumericVector<Real>& X,
                                    MAST::OutputAssemblyElemOperations& output,
                                    libMesh::NumericVector<Real>& dq_dX);
        
//#define MAST_ENABLE_PLPLOT 1
#if MAST_ENABLE_PLPLOT == 1
        void plot_sub_elems(bool plot_reference_elem,
                            bool plot_low_phi_elem,
                            bool plot_high_phi_elem);
#endif
        
        
        /*!
         *   calculates the value of quantity \f$ q(X,p) \f$.
         */
        virtual void
        calculate_output(const libMesh::NumericVector<Real>& X,
                         MAST::OutputAssemblyElemOperations& output);
        
        
        
        /*!
         *   evaluates the sensitivity of the outputs in the attached
         *   discipline with respect to the parametrs in \par params.
         *   The base solution should be provided in \par X. If total sensitivity
         *   is desired, then \par dXdp should contain the sensitivity of
         *   solution wrt the parameter \par p. If this \par dXdp is zero,
         *   the calculated sensitivity will be the partial derivarive of
         *   \par output wrt \par p.
         */
        virtual void
        calculate_output_direct_sensitivity(const libMesh::NumericVector<Real>& X,
                                            const libMesh::NumericVector<Real>& dXdp,
                                            const MAST::FunctionBase& p,
                                            MAST::OutputAssemblyElemOperations& output);
        
        
        /*!
         *   Evaluates the total sensitivity of \par output wrt \par p using
         *   the adjoint solution provided in \par dq_dX for a linearization
         *   about solution \par X.
         */
        /*virtual Real
        calculate_output_adjoint_sensitivity(const libMesh::NumericVector<Real>& X,
                                             const libMesh::NumericVector<Real>& dq_dX,
                                             const MAST::FunctionBase& p,
                                             MAST::AssemblyElemOperations&       elem_ops,
                                             MAST::OutputAssemblyElemOperations& output,
                                             const bool include_partial_sens = true);
         */
        
        /*!
         *   @returns a MAST::FEBase object for calculation of finite element
         *   quantities. For all standard applications this is a wrapper
         *   around the libMesh::FEBase class, which is specialized for
         *   cut-cell applications where a sub-finite element is created
         *   for element integration.
         */
        virtual std::unique_ptr<MAST::FEBase>
        build_fe();

    protected:

        /*Real
        _adjoint_sensitivity_dot_product (const MAST::FunctionBase& f,
                                          const libMesh::NumericVector<Real>& X,
                                          const libMesh::NumericVector<Real>& dq_dX);
        */
        
        MAST::FieldFunction<Real>            *_level_set;

        MAST::FieldFunction<RealVectorX>     *_indicator;

        MAST::LevelSetIntersection           *_intersection;

        MAST::LevelSetInterfaceDofHandler    *_dof_handler;
        
        MAST::LevelSetVoidSolution           *_void_solution_monitor;

        MAST::FieldFunction<RealVectorX>     *_velocity;

    };
}


#endif //__mast__level_set_nonlinear_implicit_assembly_h__

