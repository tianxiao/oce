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

#include <IGESAppli_Protocol.ixx>

#include <IGESAppli_Node.hxx>
#include <IGESAppli_FiniteElement.hxx>
#include <IGESAppli_NodalDisplAndRot.hxx>
#include <IGESAppli_NodalResults.hxx>
#include <IGESAppli_ElementResults.hxx>
#include <IGESAppli_Flow.hxx>
#include <IGESAppli_PipingFlow.hxx>
#include <IGESAppli_RegionRestriction.hxx>
#include <IGESAppli_LevelFunction.hxx>
#include <IGESAppli_LineWidening.hxx>
#include <IGESAppli_DrilledHole.hxx>
#include <IGESAppli_ReferenceDesignator.hxx>
#include <IGESAppli_PinNumber.hxx>
#include <IGESAppli_PartNumber.hxx>
#include <IGESAppli_FlowLineSpec.hxx>
#include <IGESAppli_LevelToPWBLayerMap.hxx>
#include <IGESAppli_PWBArtworkStackup.hxx>
#include <IGESAppli_PWBDrilledHole.hxx>
#include <IGESAppli_NodalConstraint.hxx>

#include <IGESDefs.hxx>
#include <IGESDraw.hxx>
#include <IGESDefs_Protocol.hxx>
#include <IGESDraw_Protocol.hxx>


static int deja = 0;
static Handle(Standard_Type) atype01,atype02,atype03,atype04,atype05,atype06,
  atype07,atype08,atype09,atype10,atype11,atype12,atype13,atype14,atype15,
  atype16,atype17,atype18,atype19;

    IGESAppli_Protocol::IGESAppli_Protocol ()
{
  if (deja) return;  deja = 1;
  atype01 = STANDARD_TYPE(IGESAppli_DrilledHole);
  atype02 = STANDARD_TYPE(IGESAppli_ElementResults);
  atype03 = STANDARD_TYPE(IGESAppli_FiniteElement);
  atype04 = STANDARD_TYPE(IGESAppli_Flow);
  atype05 = STANDARD_TYPE(IGESAppli_FlowLineSpec);
  atype06 = STANDARD_TYPE(IGESAppli_LevelFunction);
  atype07 = STANDARD_TYPE(IGESAppli_LevelToPWBLayerMap);
  atype08 = STANDARD_TYPE(IGESAppli_LineWidening);
  atype09 = STANDARD_TYPE(IGESAppli_NodalConstraint);
  atype10 = STANDARD_TYPE(IGESAppli_NodalDisplAndRot);
  atype11 = STANDARD_TYPE(IGESAppli_NodalResults);
  atype12 = STANDARD_TYPE(IGESAppli_Node);
  atype13 = STANDARD_TYPE(IGESAppli_PWBArtworkStackup);
  atype14 = STANDARD_TYPE(IGESAppli_PWBDrilledHole);
  atype15 = STANDARD_TYPE(IGESAppli_PartNumber);
  atype16 = STANDARD_TYPE(IGESAppli_PinNumber);
  atype17 = STANDARD_TYPE(IGESAppli_PipingFlow);
  atype18 = STANDARD_TYPE(IGESAppli_ReferenceDesignator);
  atype19 = STANDARD_TYPE(IGESAppli_RegionRestriction);
}

    Standard_Integer IGESAppli_Protocol::NbResources () const
      {  return 2;  }

    Handle(Interface_Protocol) IGESAppli_Protocol::Resource
  (const Standard_Integer num) const
{
  Handle(Interface_Protocol) res;
  if (num == 1) res = IGESDefs::Protocol();
  if (num == 2) res = IGESDraw::Protocol();
  return res;
}

    Standard_Integer IGESAppli_Protocol::TypeNumber
  (const Handle(Standard_Type)& atype) const
{
  if      (atype == atype01) return  1;
  else if (atype == atype02) return  2;
  else if (atype == atype03) return  3;
  else if (atype == atype04) return  4;
  else if (atype == atype05) return  5;
  else if (atype == atype06) return  6;
  else if (atype == atype07) return  7;
  else if (atype == atype08) return  8;
  else if (atype == atype09) return  9;
  else if (atype == atype10) return 10;
  else if (atype == atype11) return 11;
  else if (atype == atype12) return 12;
  else if (atype == atype13) return 13;
  else if (atype == atype14) return 14;
  else if (atype == atype15) return 15;
  else if (atype == atype16) return 16;
  else if (atype == atype17) return 17;
  else if (atype == atype18) return 18;
  else if (atype == atype19) return 19;
  return 0;
}
