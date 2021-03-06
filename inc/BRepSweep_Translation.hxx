// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _BRepSweep_Translation_HeaderFile
#define _BRepSweep_Translation_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _gp_Vec_HeaderFile
#include <gp_Vec.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _BRepSweep_Trsf_HeaderFile
#include <BRepSweep_Trsf.hxx>
#endif
#ifndef _TopAbs_Orientation_HeaderFile
#include <TopAbs_Orientation.hxx>
#endif
class Standard_ConstructionError;
class TopoDS_Shape;
class Sweep_NumShape;
class TopLoc_Location;
class gp_Vec;


//! Provides   an  algorithm   to   build  object   by <br>
//!          translation sweep. <br>
class BRepSweep_Translation  : public BRepSweep_Trsf {
public:

  DEFINE_STANDARD_ALLOC

  //! Creates  a  topology by  translating <S>  with the <br>
//!          vector  <V>. If  C  is   true S Sucomponents   are <br>
//!          copied. If Canonize is true then generated surfaces <br>
//!          are attempted to be canonized in simple types <br>
  Standard_EXPORT   BRepSweep_Translation(const TopoDS_Shape& S,const Sweep_NumShape& N,const TopLoc_Location& L,const gp_Vec& V,const Standard_Boolean C,const Standard_Boolean Canonize = Standard_True);
  
  Standard_EXPORT   virtual  void Delete() ;
Standard_EXPORT virtual ~BRepSweep_Translation(){Delete() ; }
  //! Builds the vertex addressed by [aGenV,aDirV], with its <br>
//!          geometric part, but without subcomponents. <br>
  Standard_EXPORT     TopoDS_Shape MakeEmptyVertex(const TopoDS_Shape& aGenV,const Sweep_NumShape& aDirV) ;
  //! Builds the edge addressed by [aGenV,aDirE], with its <br>
//!          geometric part, but without subcomponents. <br>
  Standard_EXPORT     TopoDS_Shape MakeEmptyDirectingEdge(const TopoDS_Shape& aGenV,const Sweep_NumShape& aDirE) ;
  //! Builds the edge addressed by [aGenE,aDirV], with its <br>
//!          geometric part, but without subcomponents. <br>
  Standard_EXPORT     TopoDS_Shape MakeEmptyGeneratingEdge(const TopoDS_Shape& aGenE,const Sweep_NumShape& aDirV) ;
  //! Sets the  parameters of the new  vertex  on the new <br>
//!          face. The new face and  new vertex where generated <br>
//!          from aGenF, aGenV and aDirV . <br>
  Standard_EXPORT     void SetParameters(const TopoDS_Shape& aNewFace,TopoDS_Shape& aNewVertex,const TopoDS_Shape& aGenF,const TopoDS_Shape& aGenV,const Sweep_NumShape& aDirV) ;
  //! Sets the  parameter of the new  vertex  on the new <br>
//!          edge. The new edge and  new vertex where generated <br>
//!          from aGenV aDirE, and aDirV. <br>
  Standard_EXPORT     void SetDirectingParameter(const TopoDS_Shape& aNewEdge,TopoDS_Shape& aNewVertex,const TopoDS_Shape& aGenV,const Sweep_NumShape& aDirE,const Sweep_NumShape& aDirV) ;
  //! Sets the  parameter of the new  vertex  on the new <br>
//!          edge. The new edge and  new vertex where generated <br>
//!          from aGenE, aGenV and aDirV . <br>
  Standard_EXPORT     void SetGeneratingParameter(const TopoDS_Shape& aNewEdge,TopoDS_Shape& aNewVertex,const TopoDS_Shape& aGenE,const TopoDS_Shape& aGenV,const Sweep_NumShape& aDirV) ;
  //! Builds the  face addressed  by [aGenS,aDirS], with <br>
//!          its geometric part, but without subcomponents. The <br>
//!          couple aGenS, aDirS can  be a "generating face and <br>
//!          a  directing  vertex" or  "a generating edge and a <br>
//!          directing  edge". <br>
  Standard_EXPORT     TopoDS_Shape MakeEmptyFace(const TopoDS_Shape& aGenS,const Sweep_NumShape& aDirS) ;
  //! Sets the PCurve for a new edge on a new face. The <br>
//!          new edge and  the  new face were generated  using <br>
//!          aGenF, aGenE and aDirV. <br>
  Standard_EXPORT     void SetPCurve(const TopoDS_Shape& aNewFace,TopoDS_Shape& aNewEdge,const TopoDS_Shape& aGenF,const TopoDS_Shape& aGenE,const Sweep_NumShape& aDirV,const TopAbs_Orientation orien) ;
  //! Sets the PCurve for a new edge on a new face. The <br>
//!          new edge and  the  new face were generated  using <br>
//!          aGenE, aDirE and aDirV. <br>
  Standard_EXPORT     void SetGeneratingPCurve(const TopoDS_Shape& aNewFace,TopoDS_Shape& aNewEdge,const TopoDS_Shape& aGenE,const Sweep_NumShape& aDirE,const Sweep_NumShape& aDirV,const TopAbs_Orientation orien) ;
  //! Sets the PCurve for a new edge on a new face. The <br>
//!          new edge and  the  new face were generated  using <br>
//!          aGenE, aDirE and aGenV. <br>
  Standard_EXPORT     void SetDirectingPCurve(const TopoDS_Shape& aNewFace,TopoDS_Shape& aNewEdge,const TopoDS_Shape& aGenE,const TopoDS_Shape& aGenV,const Sweep_NumShape& aDirE,const TopAbs_Orientation orien) ;
  //! Returns the Orientation of the  shell in the solid <br>
//!          generated by the face aGenS  with  the edge aDirS. <br>
//!          It is  REVERSED  if the surface is  swept  in  the <br>
//!          direction of the normal. <br>
  Standard_EXPORT     TopAbs_Orientation DirectSolid(const TopoDS_Shape& aGenS,const Sweep_NumShape& aDirS) ;
  //! Returns   true   if  aNewSubShape    (addressed by <br>
//!          aSubGenS  and aDirS)  must  be added  in aNewShape <br>
//!          (addressed by aGenS and aDirS). <br>
  Standard_EXPORT     Standard_Boolean GGDShapeIsToAdd(const TopoDS_Shape& aNewShape,const TopoDS_Shape& aNewSubShape,const TopoDS_Shape& aGenS,const TopoDS_Shape& aSubGenS,const Sweep_NumShape& aDirS) const;
  //! Returns   true   if  aNewSubShape    (addressed by <br>
//!          aGenS  and aSubDirS)  must  be added  in aNewShape <br>
//!          (addressed by aGenS and aDirS). <br>
  Standard_EXPORT     Standard_Boolean GDDShapeIsToAdd(const TopoDS_Shape& aNewShape,const TopoDS_Shape& aNewSubShape,const TopoDS_Shape& aGenS,const Sweep_NumShape& aDirS,const Sweep_NumShape& aSubDirS) const;
  //! In  some  particular  cases  the   topology  of  a <br>
//!          generated  face must be  composed  of  independant <br>
//!          closed wires,  in this case  this function returns <br>
//!          true. <br>
//!          Here it always returns false. <br>
  Standard_EXPORT     Standard_Boolean SeparatedWires(const TopoDS_Shape& aNewShape,const TopoDS_Shape& aNewSubShape,const TopoDS_Shape& aGenS,const TopoDS_Shape& aSubGenS,const Sweep_NumShape& aDirS) const;
  //! Returns true   if aDirS   and aGenS  addresses   a <br>
//!          resulting Shape. In some  specific cases the shape <br>
//!          can  be    geometrically   inexsistant,  then this <br>
//!          function returns false. <br>
  Standard_EXPORT     Standard_Boolean HasShape(const TopoDS_Shape& aGenS,const Sweep_NumShape& aDirS) const;
  //! Returns  always     false   because    here    the <br>
//!          transformation is a translation. <br>
  Standard_EXPORT     Standard_Boolean IsInvariant(const TopoDS_Shape& aGenS) const;
  //! Returns the Vector of the Prism,  if it is an infinite <br>
//!          prism the Vec is unitar. <br>
  Standard_EXPORT     gp_Vec Vec() const;





protected:





private:



gp_Vec myVec;
Standard_Boolean myCanonize;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
