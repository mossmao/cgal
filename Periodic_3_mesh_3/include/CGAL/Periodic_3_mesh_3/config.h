// Copyright (c) 2014 INRIA (France).
//               2017 GeometryFactory Sarl (France)
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org).
// You can redistribute it and/or modify it under the terms of the GNU
// General Public License as published by the Free Software Foundation,
// either version 3 of the License, or (at your option) any later version.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// Author(s)     : Aymeric Pellé
//                 Mael Rouxel-Labbé

#ifndef CGAL_PERIODIC_3_MESH_3_CONFIG_H
#define CGAL_PERIODIC_3_MESH_3_CONFIG_H

// Avoid optimisations of Mesh_3
#define CGAL_NO_STRUCTURAL_FILTERING
#ifdef CGAL_MESH_3_SIZING_FIELD_INEXACT_LOCATE
  #undef CGAL_MESH_3_SIZING_FIELD_INEXACT_LOCATE
#endif

// to be sure that we include it before Mesh_3's version
#include <CGAL/Periodic_3_mesh_3/Protect_edges_sizing_field.h>

//#warning "Structural filtering is disabled because this feature isn't compatible with some periodic traits!"
/*
 * It's a temporary solution.
 * We avoid the structural filtering optimization, because it isn't
 * available with some periodic triangulation traits. (cf. Periodic_3_triangulation_remove_traits_3.h)
 * Indeed, this feature needs the Triangulation_3::inexact_orientation() method.
 *
 * A better solution would be to make Triangulation_3 compatible 'any' traits.
 * By this way, Triangulation_3 would require the Bare_point concept which would use in
 * inexact_orientation(). So, we'd work with a Bare_point instead of a Point in this method.
 * In the 'default' Triangulation_3 traits, Bare_point would be equal to Point_3
 * (or const Point_3&  <- for avoiding useless copies).
*/

#endif // CGAL_PERIODIC_3_MESH_3_CONFIG_H
