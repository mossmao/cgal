// TODO: Add licence
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL:$
// $Id: $
// 
//
// Author(s)     : Eric Berberich <eric@mpi-inf.mpg.de>
//                 Pavel Emeliyanenko <asm@mpi-sb.mpg.de>
//
// ============================================================================

#ifndef CGAL_CURVED_KERNEL_VIA_ANALYSIS_2_H
#define CGAL_CURVED_KERNEL_VIA_ANALYSIS_2_H

/*! \file Curved_kernel_via_analysis_2.h
 *  \brief defines class \c Curved_kernel_via_analysis_2
 *  
 *  Defines points and arcs supported by curves that can be analyzed
 */

#include <CGAL/basic.h>
#include <CGAL/Arr_enums.h>
#include <CGAL/Arr_tags.h>
#include <CGAL/Curved_kernel_via_analysis_2/Point_2.h>
#include <CGAL/Curved_kernel_via_analysis_2/Arc_2.h>

#include <CGAL/Curved_kernel_via_analysis_2/Curve_interval_arcno_cache.h>
#include <CGAL/Curved_kernel_via_analysis_2/Make_x_monotone_2.h>
#include <CGAL/Curved_kernel_via_analysis_2/Curved_kernel_via_analysis_2_functors.h>

CGAL_BEGIN_NAMESPACE

namespace CGALi {

// todo mode to another file
template < class CurveKernel_2 >
class Curved_kernel_via_analysis_2_base {
public:

    //! this instance's template parameter
    typedef CurveKernel_2 Curve_kernel_2;
    
    //! self
    typedef Curved_kernel_via_analysis_2_base< Curve_kernel_2 > Self;
    
    //!\name Global types
    //!@{

    //! type of general planar curve
    typedef typename Curve_kernel_2::Curve_2 Curve_2;
    
    //! type of point's x-coordinate
    typedef typename Curve_kernel_2::X_coordinate_1 X_coordinate_1;
    
    //! type of a finite point on curve
    typedef typename Curve_kernel_2::Xy_coordinate_2 Xy_coordinate_2;
    
    //! type of boundary of coordinates
    typedef typename Curve_kernel_2::Boundary Boundary;

    //! provides analysis of a single curve
    typedef typename Curve_kernel_2::Curve_analysis_2 Curve_analysis_2;
    
    //! provides analysis of a pair of curves
    typedef typename Curve_kernel_2::Curve_pair_analysis_2
            Curve_pair_analysis_2;
    
    //! tag specifies that "to the left of" comparisons supported
    typedef CGAL::Tag_true Has_left_category;

    //! tag specifies that merge and split functors supported
    typedef CGAL::Tag_true Has_merge_category; 

    //! tag specifies that unbounded arcs supported
    typedef CGAL::Tag_true Has_boundary_category;

    //! tag specifies which boundary functors are implemented
    typedef CGAL::Arr_unbounded_boundary_tag Boundary_category;

    //!@}

    //!\name Internal types
    //!@{
    
    //! type of inverval arcno cache
    typedef CGALi::Curve_interval_arcno_cache< Self > 
    Curve_interval_arcno_cache;

    //!@}


    //! \name Constructors
    //!@{

    //! default constructor
    Curved_kernel_via_analysis_2_base() :
        _m_kernel(Curve_kernel_2()), _m_interval_arcno_cache(this) {

        // clear all caches before computing
        //Curve_kernel_2::get_curve_cache().clear();
        //Curve_kernel_2::get_curve_pair_cache().clear();
    }

    //! construct using specific \c Curve_kernel_2 instance (for controlling)
    Curved_kernel_via_analysis_2_base(const Curve_kernel_2& kernel) :
        _m_kernel(kernel), _m_interval_arcno_cache(this) {
        
        //Curve_kernel_2::get_curve_cache().clear();
        //Curve_kernel_2::get_curve_pair_cache().clear();
    }
    
    //!@}


    //!\name underlying curve kernel
    //!@{
    
    //! access to \c Curve_interval_arcno_cache
    const Curve_interval_arcno_cache& interval_arcno_cache() const {
        return _m_interval_arcno_cache;
    }
            
    //! returns internal \c Curve_kernel_2 instance
    Curve_kernel_2 kernel() const {
        return _m_kernel;
    }
    
    //!@}

protected:
    //!@{
    //!\name private members
    
    //! an instance of \c Curve_kernel_2
    Curve_kernel_2 _m_kernel;
    
    //! an instance of \c Curve_interval_arcno_cache
    mutable Curve_interval_arcno_cache _m_interval_arcno_cache;
    
    //!@}

};    
    
} // namespace CGALi


// TODO documentation
template < class CurveKernel_2 >
class Curved_kernel_via_analysis_2 :
     public CGALi::Curved_kernel_via_analysis_2_base < CurveKernel_2 >,
     public CGALi::Curved_kernel_via_analysis_2_functors < 
            Curved_kernel_via_analysis_2< CurveKernel_2 >,
            typename CurveKernel_2::Curve_2,
            CGALi::Point_2 < Curved_kernel_via_analysis_2< CurveKernel_2 > >,
            CGALi::Arc_2 < Curved_kernel_via_analysis_2< CurveKernel_2 > >
        > 
{
public:
    //! \name public typedefs
    //!@{
    
    //! this instance's template argument
    typedef CurveKernel_2 Curve_kernel_2;

    //! myself
    typedef Curved_kernel_via_analysis_2< Curve_kernel_2 > Self;
    
    //!@}
    
    //!\name embedded types  for \c Arrangement_2 package
    //!@{

    //! type of curve_2
    typedef typename Curve_kernel_2::Curve_2 Curve_2;
        
    //! type of a point on generic curve
    typedef CGALi::Point_2< Self > Point_2; 

    //! type of an arc on generic curve
    typedef CGALi::Arc_2< Self > Arc_2; 

    //! type of weakly x-monotone arc for \c ArrangementTraits_2
    typedef Arc_2 X_monotone_curve_2;

    //!@}
    
protected:
    //!\name Protected internal types

    //!@{
    //! class collecting basic types
    typedef CGALi::Curved_kernel_via_analysis_2_base < CurveKernel_2 >
    Base_kernel;

    //! class collecting basic types
    typedef CGALi::Curved_kernel_via_analysis_2_functors < 
            Self, Curve_2, Point_2, Arc_2
    >  
    Base_functors;
    
    //!@}

public:
    //! \name Constructors
    //!@{

    //! default constructor
    Curved_kernel_via_analysis_2() :
        Base_kernel() {
    }
    
    //! construct using specific \c Curve_kernel_2 instance (for controlling)
    Curved_kernel_via_analysis_2(const Curve_kernel_2& kernel) :
        Base_kernel(kernel) {
    }
    
    //!@}

    //!\name Additinonal functors
    //!{

// declares curved kernel functors, for each functor defines a member function
// returning an instance of this functor
#define CGAL_CKvA_2_functor_pred(Y, Z) \
    typedef CGALi::Curved_kernel_via_analysis_2_Functors::Y<Self> Y; \
    Y Z() const { return Y((Curved_kernel_via_analysis_2 *)this); }

#define CGAL_CKvA_2_functor_cons(Y, Z) CGAL_CKvA_2_functor_pred(Y, Z)
    
public:

    CGAL_CKvA_2_functor_cons(Construct_point_2, 
                             construct_point_2_object);

    CGAL_CKvA_2_functor_cons(Construct_point_on_arc_2, 
                             construct_point_on_arc_2_object);

#undef CGAL_CKvA_2_functor_pred
#undef CGAL_CKvA_2_functor_cons


    //!@}
 
}; // class Curved_kernel_via_analysis_2

CGAL_END_NAMESPACE

#endif // CGAL_CURVED_KERNEL_VIA_ANALYSIS_2_H
