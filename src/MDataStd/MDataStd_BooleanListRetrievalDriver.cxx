// Created on: 2007-05-29
// Created by: Vlad Romashko
// Copyright (c) 2007-2012 OPEN CASCADE SAS
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


#include <MDataStd_BooleanListRetrievalDriver.ixx>
#include <PDataStd_BooleanList.hxx>
#include <TDataStd_BooleanList.hxx>
#include <MDataStd.hxx>
#include <CDM_MessageDriver.hxx>

//=======================================================================
//function : MDataStd_BooleanListRetrievalDriver
//purpose  : 
//=======================================================================
MDataStd_BooleanListRetrievalDriver::MDataStd_BooleanListRetrievalDriver(const Handle(CDM_MessageDriver)& theMsgDriver):MDF_ARDriver(theMsgDriver)
{

}

//=======================================================================
//function : VersionNumber
//purpose  : 
//=======================================================================
Standard_Integer MDataStd_BooleanListRetrievalDriver::VersionNumber() const
{ 
  return 0; 
}

//=======================================================================
//function : SourceType
//purpose  : 
//=======================================================================
Handle(Standard_Type) MDataStd_BooleanListRetrievalDriver::SourceType() const
{
  static Handle(Standard_Type) sourceType = STANDARD_TYPE(PDataStd_BooleanList);
  return sourceType;
}

//=======================================================================
//function : NewEmpty
//purpose  : 
//=======================================================================
Handle(TDF_Attribute) MDataStd_BooleanListRetrievalDriver::NewEmpty () const 
{
  return new TDataStd_BooleanList();
}

//=======================================================================
//function : Paste
//purpose  : 
//=======================================================================
void MDataStd_BooleanListRetrievalDriver::Paste(const Handle(PDF_Attribute)& Source,
						const Handle(TDF_Attribute)& Target,
						const Handle(MDF_RRelocationTable)& ) const
{
  Handle(PDataStd_BooleanList) S = Handle(PDataStd_BooleanList)::DownCast (Source);
  Handle(TDataStd_BooleanList) T = Handle(TDataStd_BooleanList)::DownCast (Target);

  Standard_Integer i, lower = S->Lower(), upper = S->Upper();
  for (i = lower; i <= upper; i++)
  {
    T->Append(0 != S->Value(i));
  }
}
