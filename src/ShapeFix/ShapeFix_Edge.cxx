// Copyright (c) 1999-2012 OPEN CASCADE SAS
//
// The content of this file is subject to the Open CASCADE Technology Public
// License Version 6.5 (the "License"). You may not use the content of this file
// except in compliance with the License. Please obtain a copy of the License
// at http://www.opencascade.org and read it completely before using this file.
//
// The Initial Developer of the Original Code is Open CASCADE S.A.S., having its
// main offices at: 1, place des Freres Montgolfier, 78280 Guyancourt, France.
//
// The Original Code and all software distributed under the License is
// distributed on an "AS IS" basis, without warranty of any kind, and the
// Initial Developer hereby disclaims all such warranties, including without
// limitation, any warranties of merchantability, fitness for a particular
// purpose or non-infringement. Please see the License for the specific terms
// and conditions governing the rights and limitations under the License.

// abv 30 Dec 98: code optimizations
//:o1 abv 16.02.99: updating vertices tolerance when edge is updated
//    rln 03.03.99 S4135: removed unnecessary check for Geom_SphericalSurface (as not V-closed)
//:q8 abv 23.03.99: bm4_al_eye.stp #53710: avoid shifting pcurves for pseudo-seam
//#78 rln 12.03.99 S4135: checking spatial closure with prec
//#81 rln 15.03.99 S4135: for not SP edge chose the best result (either BRepLib or deviation only)
//#82 rln 16.03.99 S4135: avoiding setting input precision into the edge in FixAddPCurve
//:r4 abv 02.04.99 improving method FixSameParameter()
//:s5 abv 22.04.99 Adding debug printouts in catch {} blocks
//    abv 05.05.99 S4137: method CopyPCurves moved to ShapeBuild_Edge
#include <ShapeFix_Edge.ixx>

#include <Standard_ErrorHandler.hxx>
#include <Standard_Failure.hxx>

#include <BRep_Builder.hxx>
#include <BRep_GCurve.hxx>
#include <BRep_TEdge.hxx>
#include <BRep_Tool.hxx>
#include <BRep_ListIteratorOfListOfCurveRepresentation.hxx>
#include <BRep_ListOfCurveRepresentation.hxx>
#include <BRepLib.hxx>

#include <Geom2d_Curve.hxx>
#include <Geom2d_Line.hxx>
#include <Geom2d_BSplineCurve.hxx>
#include <Geom2d_TrimmedCurve.hxx>
#include <Geom2d_BezierCurve.hxx>

#include <Geom_Curve.hxx>
#include <GeomLib.hxx>

#include <Precision.hxx>
#include <TopExp.hxx>
#include <TopoDS_Vertex.hxx>
#include <TopoDS.hxx>

#include <ShapeAnalysis_Edge.hxx>
#include <ShapeExtend.hxx>
#include <ShapeBuild_Edge.hxx>
#include <ShapeFix_ShapeTolerance.hxx>
#include <Geom2d_OffsetCurve.hxx>
#include <ShapeAnalysis_Curve.hxx>


//=======================================================================
//function : ShapeFix_Edge
//purpose  : 
//=======================================================================

ShapeFix_Edge::ShapeFix_Edge()
{
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
  myProjector = new ShapeConstruct_ProjectCurveOnSurface;
}

//=======================================================================
//function : Projector
//purpose  : 
//=======================================================================

Handle(ShapeConstruct_ProjectCurveOnSurface) ShapeFix_Edge::Projector()
{
  return myProjector;
}


//=======================================================================
//function : FixRemovePCurve
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixRemovePCurve (const TopoDS_Edge& edge,
						 const TopoDS_Face& face) 
{
  TopLoc_Location L;
  const Handle(Geom_Surface)& S = BRep_Tool::Surface(face, L);
  return FixRemovePCurve (edge, S, L);
}

//=======================================================================
//function : FixRemovePCurve
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixRemovePCurve (const TopoDS_Edge& edge,
						 const Handle(Geom_Surface)& surface,
						 const TopLoc_Location& location) 
{
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
  ShapeAnalysis_Edge EA;
  Standard_Boolean result = EA.CheckVerticesWithPCurve (edge, surface, location);
  if (result) ShapeBuild_Edge().RemovePCurve (edge, surface, location);
  return result;
}

//=======================================================================
//function : FixRemoveCurve3d
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixRemoveCurve3d (const TopoDS_Edge& edge) 
{
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
  ShapeAnalysis_Edge EA;
  Standard_Boolean result = EA.CheckVerticesWithCurve3d (edge);
  if (result) ShapeBuild_Edge().RemoveCurve3d (edge);
  return result;
}

//=======================================================================
//function : FixAddPCurve
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixAddPCurve (const TopoDS_Edge& edge,
					      const TopoDS_Face& face,
					      const Standard_Boolean isSeam,
					      const Standard_Real prec) 
{
  TopLoc_Location L;
  const Handle(Geom_Surface)& S = BRep_Tool::Surface(face, L);
  return FixAddPCurve (edge, S, L, isSeam, prec);
}

//=======================================================================
//function : FixAddPCurve
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixAddPCurve (const TopoDS_Edge& edge,
					      const Handle(Geom_Surface)& surface,
					      const TopLoc_Location& location,
					      const Standard_Boolean isSeam,
					      const Standard_Real prec)
{
  Handle(ShapeAnalysis_Surface) sas = new ShapeAnalysis_Surface (surface);
  return FixAddPCurve (edge, surface, location, isSeam, sas, prec);
}

//=======================================================================
//function : FixAddPCurve
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixAddPCurve (const TopoDS_Edge& edge,
					      const TopoDS_Face& face,
					      const Standard_Boolean isSeam,
					      const Handle(ShapeAnalysis_Surface)& surfana,
					      const Standard_Real prec) 
{
  TopLoc_Location L;
  const Handle(Geom_Surface)& S = BRep_Tool::Surface(face, L);
  return FixAddPCurve (edge, S, L, isSeam, surfana, prec);
}

//=======================================================================
//function : FixAddPCurve
//purpose  : 
//=======================================================================

//#12 rln 17/03/98 making this method to be more general : if a curve is
//parallel to one iso let us translate it parallely in the direction to another
//iso (which is located farther from aC2d). Thus, the requirement for closeness
//to the surface bounds may be avoid.
//For example, instead of Abs(theLoc.X()-uf) <= Tol) ... elseif (...-ul..)...
//the comparison if (Abs(theLoc.X()-uf) <= Abs(theLoc.X()-ul)) .... can be used.

//The reason of this fix #12 is that seam is not sure to lie on the bound :
//if a surface is periodic the whole contour may be shifted (e.g. ProSTEP,
//file ug_exhaust-A.stp entity #284920)

static Handle(Geom2d_Curve) TranslatePCurve (const Handle(Geom_Surface)& aSurf,  
                                             Handle(Geom2d_Curve)& aC2d,
                                             const Standard_Real& aTol)
{
  Standard_Real uf,ul,vf,vl;
  aSurf->Bounds(uf,ul,vf,vl);
  
  // cas d une ligne
  Handle(Geom2d_Line) theL2d = Handle(Geom2d_Line)::DownCast(aC2d);
  if (!theL2d.IsNull()) {
    gp_Pnt2d theLoc = theL2d->Location();
    gp_Dir2d theDir = theL2d->Direction();

    gp_Pnt2d newLoc;
    Handle(Geom2d_Line) theNewL2d = theL2d;

    //case UClosed
    if (Abs(theDir.X()) <= aTol && Abs(theDir.Y()) >= aTol) {
      if (Abs(theLoc.X() - uf) < Abs(theLoc.X() - ul))
	newLoc.SetCoord (theLoc.X() + (ul - uf), theLoc.Y());
      else
	newLoc.SetCoord (theLoc.X() - (ul - uf), theLoc.Y());
      theNewL2d = new Geom2d_Line(newLoc, theDir);
    }
/*    // case UClosed and line in U = UFirst
    if ((Abs(theLoc.X() - uf) <= aTol) &&
	(Abs(theDir.X()) <= aTol)      &&
	(Abs(theDir.Y()) >= aTol)) {
      // on translate en ul
      gp_Pnt2d newLoc(ul, theLoc.Y());
      Handle(Geom2d_Line) theNewL2d = new Geom2d_Line(newLoc, theDir);
      return theNewL2d;
    }
    // cas UClosed and line in U = ULast
    if ((Abs(theLoc.X() - ul) <= aTol) &&
	(Abs(theDir.X()) <= aTol)      &&
	(Abs(theDir.Y()) >= aTol)) {
      // on translate en uf
      gp_Pnt2d newLoc(uf, theLoc.Y());
      Handle(Geom2d_Line) theNewL2d = new Geom2d_Line(newLoc, theDir);
      return theNewL2d;
    }
*/
    //case VClosed
    if (Abs(theDir.X()) >= aTol && Abs(theDir.Y()) <= aTol) {
      if (Abs(theLoc.Y() - vf) < Abs(theLoc.Y() - vl))
	newLoc.SetCoord (theLoc.X(), theLoc.Y() + (vl - vf));
      else
	newLoc.SetCoord (theLoc.X(), theLoc.Y() - (vl - vf));
      theNewL2d = new Geom2d_Line(newLoc, theDir);
    }
/*    // case VClosed and line in V = VFirst
    if ((Abs(theLoc.Y() - vf) <= aTol) &&
	(Abs(theDir.X()) >= aTol)      &&
	(Abs(theDir.Y()) <= aTol)) {
      // on translate en vl
      gp_Pnt2d newLoc(theLoc.X(), vl);
      Handle(Geom2d_Line) theNewL2d = new Geom2d_Line(newLoc, theDir);
      return theNewL2d;
    }
    // cas VClosed and line in V = VLast
    if ((Abs(theLoc.Y() - vl) <= aTol) &&
	(Abs(theDir.X()) >= aTol)      &&
	(Abs(theDir.Y()) <= aTol)) {
      // on translate en vf
      gp_Pnt2d newLoc(theLoc.X(), vf);
      Handle(Geom2d_Line) theNewL2d = new Geom2d_Line(newLoc, theDir);
      return theNewL2d;
    }
*/
    // Other case not yet implemented
#ifdef DEBUG
    cout << "TranslatePCurve not performed" << endl;
#endif
    return theNewL2d;//*theL2d;
  }
  else {
    // cas bspline curve
    Handle(Geom2d_BSplineCurve) 
      aBC = Handle(Geom2d_BSplineCurve)::DownCast(aC2d);
    if (aBC.IsNull()) {
#ifdef DEBUG
      cout << "Untreated curve type in TranslatePCurve" << endl;
#endif
      return aC2d;
    }
    Handle(Geom2d_BSplineCurve) newC = 
      Handle(Geom2d_BSplineCurve)::DownCast(aBC->Copy());
    gp_Pnt2d FirstPoint = aBC->StartPoint();
    gp_Pnt2d LastPoint  = aBC->EndPoint();
    gp_Vec2d theVector (FirstPoint, LastPoint);
    gp_Pnt2d p00(uf, vf), p01(uf,vl), p10(ul,vf);
    gp_Vec2d VectIsoUF(p00, p01);
    gp_Vec2d VectIsoVF(p00, p10);

    gp_Trsf2d T;
    if (theVector.IsParallel(VectIsoUF, aTol)) {
      if (Abs(FirstPoint.X() - uf) < Abs(FirstPoint.X() - ul))	T.SetTranslation(p00, p10);
      else                                                      T.SetTranslation(p10, p00);
      newC->Transform(T);
      return newC;
    }
/*      // case UClosed and line in U = UFirst
      if (Abs(FirstPoint.X() - uf) <= aTol) {
	gp_Trsf2d T;
	T.SetTranslation(p00, p10);
	newC->Transform(T);
	return newC;
      }
      // case UClosed and line in U = ULast
      else if (Abs(FirstPoint.X() - ul) <= aTol) {
	gp_Trsf2d T;
	T.SetTranslation(p10, p00);
	newC->Transform(T);
	return newC;	
      }
      else { // les courbes ne sont pas sur la couture
	return aC2d;
      }
*/
    else if (theVector.IsParallel(VectIsoVF, aTol)) {
//#ifdef DEBUG
//      cout << "other curve-VClosed Surface. TranslatePC not impl." << endl;
//#endif
      if (Abs(FirstPoint.Y() - vf) < Abs(FirstPoint.Y() - vl))	T.SetTranslation(p00, p01);
      else                                                      T.SetTranslation(p01, p00);
      newC->Transform(T);
      return newC;
    }
  }
  // les courbes ne sont pas sur la couture
  return aC2d;
}

//=======================================================================
//static : Range3d 
//purpose  : contournement du Range de BRep_Builder pour ne pas affecter
//           les ranges des pcurves.
//=======================================================================

static void Range3d (const TopoDS_Edge& E, 
		     const Standard_Real First, const Standard_Real Last,
		     const Standard_Real myPrecision) 
{
  //  set the range to all the representations
  const Handle(BRep_TEdge)& TE = *((Handle(BRep_TEdge)*) &E.TShape());
  
  BRep_ListOfCurveRepresentation& lcr = TE->ChangeCurves();
  BRep_ListIteratorOfListOfCurveRepresentation itcr(lcr);
  Handle(BRep_GCurve) GC;
  
  while (itcr.More()) {
    GC = Handle(BRep_GCurve)::DownCast(itcr.Value());
    if (!GC.IsNull()) {
      if (GC->IsCurve3D()) {
	GC->SetRange(First,Last);
	// Set the closedness flag to the correct value.
	Handle(Geom_Curve) C = GC->Curve3D();
	if ( !C.IsNull() ) {
	  Standard_Boolean closed = C->Value(First).IsEqual(C->Value(Last),myPrecision);
	  TE->Closed(closed);
	}
      }
    }
    itcr.Next();
  }

  TE->Modified(Standard_True);
}
//=======================================================================
//function : SameRange (Temp)
//purpose  : 
//=======================================================================
//:b0 abv 16 Feb 98: This is a copy of BRepLib::SameRange()
// modified in order to be able to fix seam edges
// NOTE: It is to be removed when is fixed either BRepLib::SameRange() 
// (concerning seam edges) or BRepLib::SameParameter() (concerning call
// to GeomLib::SameRange() with 3d tolerance)

 static void TempSameRange(const TopoDS_Edge& AnEdge,
			   const Standard_Real Tolerance) 
{
  BRep_ListIteratorOfListOfCurveRepresentation an_Iterator
    ((*((Handle(BRep_TEdge)*)&AnEdge.TShape()))->ChangeCurves());
  
  Handle(Geom2d_Curve) Curve2dPtr, NewCurve2dPtr;
  Handle(Geom2d_Curve) Curve2dPtr2, NewCurve2dPtr2;
  TopLoc_Location LocalLoc ;

  //Standard_Boolean  IsSameRange = Standard_True //skl
  Standard_Boolean first_time_in = Standard_True, has_curve, has_closed_curve;
  Handle(BRep_GCurve) geometric_representation_ptr;
  Standard_Real first, current_first, last, current_last;

  const Handle(Geom_Curve) C = BRep_Tool::Curve(AnEdge, LocalLoc, 
						current_first, current_last);
  if (!C.IsNull()) first_time_in = Standard_False;
  
  while (an_Iterator.More()) {
    geometric_representation_ptr =
      Handle(BRep_GCurve)::DownCast(an_Iterator.Value());
    if (! geometric_representation_ptr.IsNull()) {
      has_closed_curve = has_curve = Standard_False;
      first = geometric_representation_ptr->First();
      last =  geometric_representation_ptr->Last();
      if (geometric_representation_ptr->IsCurveOnSurface()) {
	Curve2dPtr = geometric_representation_ptr->PCurve() ; 
	has_curve = Standard_True ;
      }
      if (geometric_representation_ptr->IsCurveOnClosedSurface()) {
	Curve2dPtr2 = geometric_representation_ptr->PCurve2() ;
	has_closed_curve = Standard_True ;
      }
      if (has_curve || has_closed_curve) {
	if (first_time_in) {
	  current_first = first;
	  current_last = last;
	  first_time_in = Standard_False;
        }
	
        if (Abs(first - current_first) > Precision::PConfusion() || //:b8 abv 20 Feb 98: Confusion -> PConfusion
	    Abs(last - current_last) > Precision::PConfusion() ) {  //:b8
	  Standard_Real oldFirst=0., oldLast=0.; //skl
	  if (has_curve) {
	    //pdn 20.05.99 Work around 
            oldFirst = geometric_representation_ptr->First();
	    oldLast = geometric_representation_ptr->Last();
            // 15.11.2002 PTV OCC966
	    if(ShapeAnalysis_Curve::IsPeriodic(Curve2dPtr)) {
	      Handle(Geom2d_TrimmedCurve) tc = new Geom2d_TrimmedCurve(Curve2dPtr,oldFirst,oldLast);
	      Standard_Real shift = tc->FirstParameter()-oldFirst;
	      oldFirst += shift;
	      oldLast += shift;
	    }
	    //pdn 30.06.2000 work arounf on beziers
	    Standard_Real oldFirstCurve1 = oldFirst, oldLastCurve1 = oldLast;
	    if(Curve2dPtr->IsKind(STANDARD_TYPE(Geom2d_BezierCurve))) {
	      
	      Standard_Real preci = Precision::PConfusion();
	      if ( Abs(oldFirst) > preci || Abs(oldLast-1) > preci ) {
		Handle(Geom2d_BezierCurve) bezier = Handle(Geom2d_BezierCurve)::DownCast(Curve2dPtr->Copy());
		bezier->Segment(oldFirst,oldLast);
		Curve2dPtr = bezier;
	      }
	      oldFirstCurve1 = 0;
	      oldLastCurve1 = 1;
	    }
	       
	    GeomLib::SameRange(Tolerance, Curve2dPtr, 
			       oldFirstCurve1,
			       oldLastCurve1,
			       current_first, current_last, NewCurve2dPtr);
	    geometric_representation_ptr->PCurve(NewCurve2dPtr) ;
  	  }
	  if (has_closed_curve) {
	    
	    Standard_Real oldFirstCurve2 = oldFirst, oldLastCurve2 = oldLast;
	    
	    if(Curve2dPtr2->IsKind(STANDARD_TYPE(Geom2d_BezierCurve))) {
	      
	      Standard_Real preci = Precision::PConfusion();
	      if ( Abs(oldFirst) > preci || Abs(oldLast-1) > preci ) {
		Handle(Geom2d_BezierCurve) bezier = Handle(Geom2d_BezierCurve)::DownCast(Curve2dPtr2->Copy());
		bezier->Segment(oldFirst,oldLast);
		Curve2dPtr2 = bezier;
	      }
	      oldFirstCurve2 = 0;
	      oldLastCurve2 = 1;
	    }
	    	      
 	    GeomLib::SameRange(Tolerance, Curve2dPtr2, 
			       oldFirstCurve2,
			       oldLastCurve2,
		  	       current_first, current_last, NewCurve2dPtr2);
	    geometric_representation_ptr->PCurve2(NewCurve2dPtr2);
   	  }
	}
      }
    }
    an_Iterator.Next();
  }
  BRep_Builder B;
  B.Range(TopoDS::Edge(AnEdge), current_first, current_last);
  B.SameRange(AnEdge, Standard_True);
}

//=======================================================================
//function : FixAddPCurve
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixAddPCurve (const TopoDS_Edge& edge,
					      const Handle(Geom_Surface)& surf,
					      const TopLoc_Location& location,
					      const Standard_Boolean isSeam,
					      const Handle(ShapeAnalysis_Surface)& sas,
					      const Standard_Real prec)
{
  ShapeAnalysis_Edge sae;
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
  if ( (!isSeam && sae.HasPCurve (edge, surf, location))||
       ( isSeam && sae.IsSeam(edge, surf, location))) return Standard_False;

  // PCurve on Plane not computed
  if (surf->IsKind(STANDARD_TYPE(Geom_Plane))) return Standard_False;

//  Standard_Real step = 0;
  try {
    OCC_CATCH_SIGNALS
    Standard_Real First, Last;

    BRep_Builder B;

    Standard_Real preci = ( prec >0. ? prec : BRep_Tool::Tolerance(edge) );
    Handle(Geom_Curve) c3d = BRep_Tool::Curve(edge, /*Loc,*/ First, Last);
    //  Handle(Geom_Curve) c3d = BRep_Tool::Curve(E, First, Last);
    if (c3d.IsNull() || (Abs(Last-First) <Precision::PConfusion())) {
      myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL1);
      return Standard_False;
    }

    // Trim the curve to avoid problem  ??
//    c3d = Handle(Geom_Curve)::DownCast(c3d->Transformed(Loc.Transformation()));
//    Handle(Geom_TrimmedCurve) theTrimmed = new Geom_TrimmedCurve(c3d, First, Last);
//    c3d = theTrimmed;

//    step = 1;

    //  A present, on projette
    //  stat : 0 pas pu faire, 1 analytique, 2 approx
    Handle(Geom2d_Curve) c2d;
    Standard_Real a1, b1;
    if ( ! sae.HasPCurve (edge, surf, location)) {
      myProjector->Init ( sas, preci );
      myProjector->Perform (c3d,First,Last,c2d);
      //  stat = 2 : reinterpoler la c3d ?
      if ( myProjector->Status ( ShapeExtend_DONE4 ) )
	myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE2);
      a1 = First;
      b1 = Last;
    }
    else {
      sae.PCurve ( edge, surf, location, c2d, a1, b1, Standard_False );
    }

//    step = 2;

    // adding by skl 28.03.2003 for usung Line instead of BSpline
    Standard_Real fp=0.,lp=0.;
    Standard_Boolean isLine=Standard_False;
    if(c2d->IsKind(STANDARD_TYPE(Geom2d_TrimmedCurve))) {
      Handle(Geom2d_TrimmedCurve) tc = Handle(Geom2d_TrimmedCurve)::DownCast(c2d);
      if(tc->BasisCurve()->IsKind(STANDARD_TYPE(Geom2d_Line))) {
        fp = tc->FirstParameter();
        lp = tc->LastParameter();
        isLine = Standard_True;
      }
    }

    if (isSeam) {
      // On ne sait pas laquelle est Forward. Au PIF. La geometrie Forward
      // sera mise a jour dans ComputeWire
      Handle(Geom2d_Curve) c2d2 = Handle(Geom2d_Curve)::DownCast(c2d->Copy());
      //  ATTENTION : TranslatePCurve reconstruit une Line // bords, en
      //  intuitant U ou V ...
      //  Ici, on exploite les infos deja connues
      Standard_Real uf,ul,vf,vl;
      surf->Bounds (uf,ul,vf,vl);
      //#4 rln 19/02/98 ProSTEP ug_exhaust-A.stp entity #284920 (thoroidal surface)
      //#13 rln 17/03/98 (updating fix #4) call to TranslatePCurve in the case
      //when a surface is either u- and vclosed or neither u- nor vclosed
      //#78 rln 12.03.99 S4135: checking spatial closure with prec
      if (sas->IsUClosed(prec) && ! sas->IsVClosed(prec) //rln S4135 sphere is not considered as V-closed anymore ||
	  /* rln S4135 sas->Surface()->IsKind(STANDARD_TYPE(Geom_SphericalSurface)) */ )  {//:d9 abv 17 Mar 98: any sphere
	gp_Vec2d tranvec (ul-uf,0);
	c2d2->Translate (tranvec);
      }
      else if (sas->IsVClosed(prec) && ! sas->IsUClosed(prec) ) {
	gp_Vec2d tranvec (0,vl-vf);
	c2d2->Translate (tranvec);
      }
      else if ( sas->IsUClosed() && sas->IsVClosed() ) { //:q8 abv 23 Mar 99: bm4_al_eye.stp #53710: avoid shifting pcurves for pseudo-seam
	//      Doublement fermee (ex tore) : on lance la charge
	c2d2 = TranslatePCurve(sas->Surface(), c2d2, prec);
      }
      B.UpdateEdge (edge,c2d,c2d2,surf,location, 0.); //#82 rln 16.03.99: preci
//      if ( c2d->IsKind (STANDARD_TYPE(Geom2d_BoundedCurve)) )
//	B.Range    (edge,surf,location,c2d->FirstParameter(),c2d->LastParameter());
      B.Range    (edge,surf,location,a1,b1);
    }
    else {
      B.UpdateEdge (edge,c2d,surf,location, 0.); //#82 rln 16.03.99: preci
    }

    if ( isLine ) {
      B.Range(edge,surf,location,fp,lp);
      B.SameParameter(edge,Standard_False);
      B.SameRange(edge,Standard_False);
    }

    //  Conclusion
//    step = 3;
    if ( myProjector->Status ( ShapeExtend_DONE3 ) ) {
      Standard_Real G3dCFirst = c3d->FirstParameter();
      Standard_Real G3dCLast  = c3d->LastParameter();
      B.UpdateEdge(edge, c3d, 0.);
      Range3d(edge, G3dCFirst, G3dCLast, 0.);
    }
  }   // end try
  catch(Standard_Failure) {
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL2);
#ifdef DEB //:s5
    cout << "Warning: ShapeFix_Edge::FixAddPCurve(): Exception: ";
    Standard_Failure::Caught()->Print(cout); cout << endl;
#endif
  }
  myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
  return Standard_True;
}

//=======================================================================
//function : FixAddCurve3d
//purpose  : 
//=======================================================================

 Standard_Boolean ShapeFix_Edge::FixAddCurve3d(const TopoDS_Edge& edge) 
{
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
  ShapeAnalysis_Edge EA;
  if ( BRep_Tool::Degenerated ( edge ) || EA.HasCurve3d (edge) ) return Standard_False;
  if(!BRep_Tool::SameRange(edge))
    TempSameRange(edge,Precision::PConfusion());
    
  if (!ShapeBuild_Edge().BuildCurve3d(edge)) {
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL1);
    return Standard_False;
  }
  myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
  return Standard_True;
}

//=======================================================================
//function : FixVertexTolerance
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixVertexTolerance(const TopoDS_Edge& edge,
                                                   const TopoDS_Face& face)
{
  myStatus = ShapeExtend::EncodeStatus ( ShapeExtend_OK );
  ShapeAnalysis_Edge sae;
  Standard_Real toler1, toler2;
  if (!sae.CheckVertexTolerance (edge, face, toler1, toler2)) return Standard_False;
  if (sae.Status (ShapeExtend_DONE1))
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
  if (sae.Status (ShapeExtend_DONE2))
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE2);
  BRep_Builder B;
  TopoDS_Vertex V1 = sae.FirstVertex(edge);
  TopoDS_Vertex V2 = sae.LastVertex(edge);
  B.UpdateVertex (V1, toler1);
  B.UpdateVertex (V2, toler2);
  return Standard_True;
}

//=======================================================================
//function : FixVertexTolerance
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixVertexTolerance(const TopoDS_Edge& edge)
{
  myStatus = ShapeExtend::EncodeStatus ( ShapeExtend_OK );
  ShapeAnalysis_Edge sae;
  Standard_Real toler1, toler2;
  if (!sae.CheckVertexTolerance (edge, toler1, toler2)) return Standard_False;
  if (sae.Status (ShapeExtend_DONE1))
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
  if (sae.Status (ShapeExtend_DONE2))
    myStatus = ShapeExtend::EncodeStatus (ShapeExtend_DONE2);
  BRep_Builder B;
  TopoDS_Vertex V1 = sae.FirstVertex(edge);
  TopoDS_Vertex V2 = sae.LastVertex(edge);
  B.UpdateVertex (V1, toler1);
  B.UpdateVertex (V2, toler2);
  return Standard_True;
}

//=======================================================================
//function : FixReversed2d
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixReversed2d (const TopoDS_Edge& edge,
					       const TopoDS_Face& face) 
{
  TopLoc_Location L;
  const Handle(Geom_Surface)& S = BRep_Tool::Surface(face, L);
  return FixReversed2d (edge, S, L);
}

//=======================================================================
//function : FixReversed2d
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixReversed2d (const TopoDS_Edge& edge,
					       const Handle(Geom_Surface)& surface,
					       const TopLoc_Location& location) 
{
  myStatus = ShapeExtend::EncodeStatus (ShapeExtend_OK);
  
  ShapeAnalysis_Edge EA;
  EA.CheckCurve3dWithPCurve (edge, surface, location);
  if (EA.Status (ShapeExtend_FAIL1))
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL1);
  if (EA.Status (ShapeExtend_FAIL2))
    myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_FAIL2);
  if ( ! EA.Status (ShapeExtend_DONE) ) return Standard_False;
  
  Handle(Geom2d_Curve) c2d;
  Standard_Real f,l;
  EA.PCurve (edge, surface, location, c2d, f, l, Standard_False);
  //#46 rln 01.12.98 buc40130, entity 272 (4-th curve)
  Standard_Real newf = c2d->ReversedParameter (l), newl = c2d->ReversedParameter (f);
  c2d->Reverse();
  BRep_Builder B;
//will break seams!  B.UpdateEdge (edge, c2d, surface, location, Precision::Confusion());
  B.Range (edge, surface, location, newf, newl);
  //#51 rln 15.12.98 pro6562 entity 2788
  //Because of numerical accuracy the range on B-Splines (moreover, on any curve!)
  //the range is changed
  Standard_Real first, last;
  BRep_Tool::Range (edge, first, last);
  if (first != newf || last != newl) {
    B.SameRange     (edge, Standard_False);
    B.SameParameter (edge, Standard_False);
  }
  myStatus |= ShapeExtend::EncodeStatus (ShapeExtend_DONE1);
  return Standard_True;
}


//=======================================================================
//function : FixSameParameter
//purpose  : 
//=======================================================================

Standard_Boolean ShapeFix_Edge::FixSameParameter(const TopoDS_Edge& edge,
						 const Standard_Real tolerance) 
{
  myStatus = ShapeExtend::EncodeStatus ( ShapeExtend_OK );
  
  if ( BRep_Tool::Degenerated ( edge ) ) {
    BRep_Builder B;
    if ( ! BRep_Tool::SameRange (edge) )
      TempSameRange ( edge, Precision::PConfusion() );
    B.SameParameter ( edge, Standard_True );
    return Standard_False;
  }
  ShapeFix_ShapeTolerance SFST;
  ShapeAnalysis_Edge sae;
  BRep_Builder B;

  TopoDS_Edge copyedge;
  TopoDS_Vertex V1 = sae.FirstVertex (edge);
  TopoDS_Vertex V2 = sae.LastVertex  (edge);
  Standard_Real TolFV = ( V1.IsNull() ? 0. : BRep_Tool::Tolerance ( V1 ) );
  Standard_Real TolLV = ( V2.IsNull() ? 0. : BRep_Tool::Tolerance ( V2 ) );
  Standard_Real tol = BRep_Tool::Tolerance (edge);
  
  Standard_Boolean wasSP = BRep_Tool::SameParameter ( edge ), SP = Standard_False;
  {
    try {
      OCC_CATCH_SIGNALS
      if ( ! BRep_Tool::SameRange (edge) )
	TempSameRange ( edge, Precision::PConfusion() );
      //#81 rln 15.03.99 S4135: for not SP edge choose the best result (either BRepLib or deviation only)
      if ( ! wasSP ) {
	//create copyedge as copy of edge with the same vertices and copy of pcurves on the same surface(s)
	copyedge = ShapeBuild_Edge().Copy ( edge, Standard_False );
	B.SameParameter ( copyedge, Standard_False );
        // ShapeBuild_Edge::Copy() may change 3D curve range (if it's outside of its period).
        // In this case pcurves in BRepLib::SameParameter() will be changed as well
        // and later ShapeBuild_Edge::CopyPCurves() will copy pcurves keeping original range.
        // To prevent this discrepancy we enforce original 3D range.
        Standard_Real aF, aL;
        BRep_Tool::Range (edge, aF, aL);
        B.Range (copyedge, aF, aL, Standard_True); // only 3D
	BRepLib::SameParameter ( copyedge, ( tolerance >= Precision::Confusion() ? 
					    tolerance : tol ) );
	SP = BRep_Tool::SameParameter ( copyedge );
	if ( ! SP ) myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_FAIL2 );
      }
    }
    catch(Standard_Failure) {
#ifdef DEB
      cout << "\nWarning: ShapeFix_Edge: Exception in SameParameter: "; 
      Standard_Failure::Caught()->Print(cout); cout << endl;
#endif
      myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_FAIL2 );
    }
  }
  
  // compute deviation on the original pcurves
  Standard_Real maxdev;
  B.SameParameter ( edge, Standard_True );
  sae.CheckSameParameter ( edge, maxdev );
  if ( sae.Status ( ShapeExtend_FAIL2 ) )
    myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_FAIL1 );
  
  // if BRepLib was OK, compare and select the best variant
  if ( SP ) {
    Standard_Real BRLTol = BRep_Tool::Tolerance ( copyedge ), BRLDev;
    sae.CheckSameParameter ( copyedge, BRLDev );
    myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_DONE3 );
    if ( BRLTol < BRLDev ) BRLTol = BRLDev;
    
    //chose the best result
    if ( BRLTol < maxdev ) {
      if ( sae.Status ( ShapeExtend_FAIL2 ) )
	myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_FAIL1 );
      //copy pcurves and tolerances from copyedge
      ShapeBuild_Edge().CopyPCurves ( edge, copyedge );
      maxdev = BRLTol;
      SFST.SetTolerance (edge, BRLTol, TopAbs_EDGE);
      myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_DONE5 );
    }
  }
  //restore tolerances because they could be modified by BRepLib
  if ( ! V1.IsNull() ) SFST.SetTolerance ( V1, Max (maxdev, TolFV), TopAbs_VERTEX);
  if ( ! V2.IsNull() ) SFST.SetTolerance ( V2, Max (maxdev, TolLV), TopAbs_VERTEX);
  
  if ( maxdev > tol ) { 
    myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_DONE1 );
    B.UpdateEdge ( edge, maxdev );
    FixVertexTolerance(edge);
  }

  if ( ! wasSP && ! SP ) myStatus |= ShapeExtend::EncodeStatus ( ShapeExtend_DONE2 );
  return Status ( ShapeExtend_DONE );
}

//=======================================================================
//function : Status
//purpose  : 
//=======================================================================

 Standard_Boolean ShapeFix_Edge::Status(const ShapeExtend_Status status) const
{
  return ShapeExtend::DecodeStatus (myStatus, status);
}
