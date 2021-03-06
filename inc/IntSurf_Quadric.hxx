// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _IntSurf_Quadric_HeaderFile
#define _IntSurf_Quadric_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _gp_Ax3_HeaderFile
#include <gp_Ax3.hxx>
#endif
#ifndef _gp_Lin_HeaderFile
#include <gp_Lin.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _GeomAbs_SurfaceType_HeaderFile
#include <GeomAbs_SurfaceType.hxx>
#endif
#ifndef _gp_Pln_HeaderFile
#include <gp_Pln.hxx>
#endif
#ifndef _gp_Sphere_HeaderFile
#include <gp_Sphere.hxx>
#endif
#ifndef _gp_Cylinder_HeaderFile
#include <gp_Cylinder.hxx>
#endif
#ifndef _gp_Cone_HeaderFile
#include <gp_Cone.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
class gp_Pln;
class gp_Cylinder;
class gp_Sphere;
class gp_Cone;
class gp_Pnt;
class gp_Vec;



class IntSurf_Quadric  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   IntSurf_Quadric();
  
  Standard_EXPORT   IntSurf_Quadric(const gp_Pln& P);
  
  Standard_EXPORT   IntSurf_Quadric(const gp_Cylinder& C);
  
  Standard_EXPORT   IntSurf_Quadric(const gp_Sphere& S);
  
  Standard_EXPORT   IntSurf_Quadric(const gp_Cone& C);
  
  Standard_EXPORT     void SetValue(const gp_Pln& P) ;
  
  Standard_EXPORT     void SetValue(const gp_Cylinder& C) ;
  
  Standard_EXPORT     void SetValue(const gp_Sphere& S) ;
  
  Standard_EXPORT     void SetValue(const gp_Cone& C) ;
  
  Standard_EXPORT     Standard_Real Distance(const gp_Pnt& P) const;
  
  Standard_EXPORT     gp_Vec Gradient(const gp_Pnt& P) const;
  
  Standard_EXPORT     void ValAndGrad(const gp_Pnt& P,Standard_Real& Dist,gp_Vec& Grad) const;
  
        GeomAbs_SurfaceType TypeQuadric() const;
  
        gp_Pln Plane() const;
  
        gp_Sphere Sphere() const;
  
        gp_Cylinder Cylinder() const;
  
        gp_Cone Cone() const;
  
  Standard_EXPORT     gp_Pnt Value(const Standard_Real U,const Standard_Real V) const;
  
  Standard_EXPORT     void D1(const Standard_Real U,const Standard_Real V,gp_Pnt& P,gp_Vec& D1U,gp_Vec& D1V) const;
  
  Standard_EXPORT     gp_Vec DN(const Standard_Real U,const Standard_Real V,const Standard_Integer Nu,const Standard_Integer Nv) const;
  
  Standard_EXPORT     gp_Vec Normale(const Standard_Real U,const Standard_Real V) const;
  
  Standard_EXPORT     void Parameters(const gp_Pnt& P,Standard_Real& U,Standard_Real& V) const;
  
  Standard_EXPORT     gp_Vec Normale(const gp_Pnt& P) const;





protected:





private:



gp_Ax3 ax3;
gp_Lin lin;
Standard_Real prm1;
Standard_Real prm2;
Standard_Real prm3;
Standard_Real prm4;
Standard_Boolean ax3direc;
GeomAbs_SurfaceType typ;


};


#include <IntSurf_Quadric.lxx>



// other Inline functions and methods (like "C++: function call" methods)


#endif
