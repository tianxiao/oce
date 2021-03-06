// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _TopOpeBRep_EdgesFiller_HeaderFile
#define _TopOpeBRep_EdgesFiller_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _TopoDS_Edge_HeaderFile
#include <TopoDS_Edge.hxx>
#endif
#ifndef _TopoDS_Face_HeaderFile
#include <TopoDS_Face.hxx>
#endif
#ifndef _Handle_TopOpeBRepDS_HDataStructure_HeaderFile
#include <Handle_TopOpeBRepDS_HDataStructure.hxx>
#endif
#ifndef _TopOpeBRepDS_PDataStructure_HeaderFile
#include <TopOpeBRepDS_PDataStructure.hxx>
#endif
#ifndef _TopOpeBRep_PEdgesIntersector_HeaderFile
#include <TopOpeBRep_PEdgesIntersector.hxx>
#endif
#ifndef _TopOpeBRepDS_ListOfInterference_HeaderFile
#include <TopOpeBRepDS_ListOfInterference.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _TopOpeBRepDS_Kind_HeaderFile
#include <TopOpeBRepDS_Kind.hxx>
#endif
#ifndef _Handle_TopOpeBRepDS_Interference_HeaderFile
#include <Handle_TopOpeBRepDS_Interference.hxx>
#endif
#ifndef _Standard_Real_HeaderFile
#include <Standard_Real.hxx>
#endif
#ifndef _TopOpeBRepDS_Config_HeaderFile
#include <TopOpeBRepDS_Config.hxx>
#endif
class TopOpeBRepDS_HDataStructure;
class TopoDS_Shape;
class TopOpeBRep_EdgesIntersector;
class TopOpeBRepDS_ListIteratorOfListOfInterference;
class TopOpeBRep_Point2d;
class TopOpeBRepDS_Transition;
class TopOpeBRepDS_Interference;
class TopoDS_Edge;
class TopOpeBRepDS_ListOfInterference;


//! Fills a TopOpeBRepDS_DataStructure with Edge/Edge <br>
//!          instersection data described by TopOpeBRep_EdgesIntersector. <br>
class TopOpeBRep_EdgesFiller  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   TopOpeBRep_EdgesFiller();
  
  Standard_EXPORT     void Insert(const TopoDS_Shape& E1,const TopoDS_Shape& E2,TopOpeBRep_EdgesIntersector& EI,const Handle(TopOpeBRepDS_HDataStructure)& HDS) ;
  
  Standard_EXPORT     void Face(const Standard_Integer I,const TopoDS_Shape& F) ;
  
  Standard_EXPORT    const TopoDS_Shape& Face(const Standard_Integer I) const;





protected:





private:

  
  Standard_EXPORT     Standard_Boolean GetGeometry(TopOpeBRepDS_ListIteratorOfListOfInterference& IT,const TopOpeBRep_Point2d& P,Standard_Integer& G,TopOpeBRepDS_Kind& K) const;
  
  Standard_EXPORT     Standard_Boolean MakeGeometry(const TopOpeBRep_Point2d& P,Standard_Integer& G,TopOpeBRepDS_Kind& K) const;
  
  Standard_EXPORT     void SetShapeTransition(const TopOpeBRep_Point2d& P,TopOpeBRepDS_Transition& T1,TopOpeBRepDS_Transition& T2) const;
  
  Standard_EXPORT     Handle_TopOpeBRepDS_Interference StorePI(const TopOpeBRep_Point2d& P,const TopOpeBRepDS_Transition& T,const Standard_Integer EI,const Standard_Integer PI,const Standard_Real p,const Standard_Integer IE) ;
  
  Standard_EXPORT     Handle_TopOpeBRepDS_Interference StoreVI(const TopOpeBRep_Point2d& P,const TopOpeBRepDS_Transition& T,const Standard_Integer EI,const Standard_Integer VI,const Standard_Boolean VB,const TopOpeBRepDS_Config C,const Standard_Real p,const Standard_Integer IE) ;
  
  Standard_EXPORT     Standard_Boolean ToRecompute(const TopOpeBRep_Point2d& P,const Handle(TopOpeBRepDS_Interference)& I,const Standard_Integer IEmother) ;
  
  Standard_EXPORT     void StoreRecompute(const Handle(TopOpeBRepDS_Interference)& I,const Standard_Integer IEmother) ;
  
  Standard_EXPORT     void RecomputeInterferences(const TopoDS_Edge& E,TopOpeBRepDS_ListOfInterference& LOI) ;


TopoDS_Edge myE1;
TopoDS_Edge myE2;
TopoDS_Face myF1;
TopoDS_Face myF2;
Handle_TopOpeBRepDS_HDataStructure myHDS;
TopOpeBRepDS_PDataStructure myPDS;
TopOpeBRep_PEdgesIntersector myPEI;
TopOpeBRepDS_ListOfInterference myLI1;
TopOpeBRepDS_ListOfInterference myLI2;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
