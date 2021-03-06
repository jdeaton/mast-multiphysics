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

#ifndef __mast__orthotropic_element_property_card_3D__
#define __mast__orthotropic_element_property_card_3D__

// MAST includes
#include "property_cards/element_property_card_base.h"



namespace MAST
{
    // Forward declerations
    class CoordinateBase;
    
    
    class OrthotropicElementPropertyCard3D:
    public MAST::ElementPropertyCardBase {
        
    public:
        OrthotropicElementPropertyCard3D():
        MAST::ElementPropertyCardBase(),
        _material(nullptr),
        _orient(nullptr)
        { }
        
        /*!
         *   virtual destructor
         */
        virtual ~OrthotropicElementPropertyCard3D();
        
        
        /*!
         *   dimension of the element for which this property is defined
         */
        virtual unsigned int dim() const {
            return 3;
        }
        
        /*!
         *   return true if the property is orthotropic
         */
        virtual bool if_isotropic() const {
            
            return false;
        }
        
        
        /*!
         *    sets the material card
         */
        virtual void set_material(MAST::MaterialPropertyCardBase& mat) {
            
            _material = &mat;
        }
        
        
        /*!
         *    returns a reference to the material
         */
        const MAST::MaterialPropertyCardBase& get_material() const {
            
            libmesh_assert(_material); // make sure it has already been set
            return *_material;
        }
        
        
        /*!
         *   sets the orientation coordinate system for this section.
         */
        virtual void set_orientation(const MAST::CoordinateBase& orient);
        
        
        /*!
         *   returns the bending model to be used for the element. Should be
         *   reimplemented in the derived classes
         */
        virtual MAST::BendingOperatorType
        bending_model(const libMesh::Elem& elem,
                      const libMesh::FEType& fe) const {
            libmesh_assert(false);
        }
        
        /*!
         *    returns the extra quadrature order (on top of the system) that
         *    this element should use. By default this is zero, and can be
         *    changed by the derived classes
         */
        virtual int extra_quadrature_order(const libMesh::Elem& elem,
                                           const libMesh::FEType& fe) const {
            libmesh_assert(false);
        }
        
        /*!
         *  returns true if the property card depends on the function \p f
         */
        virtual bool depends_on(const MAST::FunctionBase& f) const;
        
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        stiffness_A_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        stiffness_B_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        stiffness_D_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        damping_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        inertia_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        thermal_expansion_A_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        thermal_expansion_B_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        transverse_shear_stiffness_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        prestress_A_matrix( MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        prestress_B_matrix( MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        thermal_conductance_matrix(const MAST::ElementBase& e) const;
        
        virtual std::unique_ptr<MAST::FieldFunction<RealMatrixX> >
        thermal_capacitance_matrix(const MAST::ElementBase& e) const;
        
    protected:

        /*!
         *    pointer to the material property card
         */
        MAST::MaterialPropertyCardBase* _material;
        
        /*!
         *    coordinate system to define orientation
         */
        const MAST::CoordinateBase *_orient;
    };
}


#endif // __mast__orthotropic_element_property_card_3D__
