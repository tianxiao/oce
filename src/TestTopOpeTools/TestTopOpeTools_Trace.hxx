// Created on: 1994-08-01
// Created by: Jean Yves LEBEY
// Copyright (c) 1994-1999 Matra Datavision
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



#ifndef _TestTopOpeTools_Trace_HeaderFile
#define _TestTopOpeTools_Trace_HeaderFile

#include <TCollection_AsciiString.hxx>
#include <TColStd_Array1OfAsciiString.hxx>
#include <TColStd_Array1OfInteger.hxx>
#include <TColStd_Array1OfBoolean.hxx>

typedef Standard_Boolean t_value;
typedef TCollection_AsciiString t_flag;

typedef void (*tf_value)(const t_value);
typedef void (*tf_intarg)(const t_value, Standard_Integer, const char**);
typedef Standard_Integer (*tf_int_intarg)(const t_value, Standard_Integer, const char**);

typedef enum te_ftyp { te_value, te_intarg, te_int_intarg } te_ftyp;

//---------------------------------------------------------------------------
//
// Une fonction de trace FT est une fonction qui value un ensemble
// de variables de controle dont la valeur conditionne l execution 
// d un ensemble d instructions.
//
// La classe TestTopOpeTools_Trace permet de coupler un nom, ou flag,
// a une fonction de trace, et de stocker une ensemble de tels couples.
// Un flag est une chaine de caracteres qui identifie la fonction.
//
// 1/ trace simple 
// Une fonction de trace simple consiste a valuer une valeur booleenne.
// le type t_value est defini comme Standard_Boolean
// le type tf_value decrit une fonction de trace a un argument de type t_value.
//
// Creation de l objet de trace T :
//       TestTopOpeTools_Trace T;
//
// Ajouter une fonction de trace FT1 de nom "toto" a l objet de trace T :
// Ajout de la fonction de trace FT2 de nom "titi" a l objet de trace T :
//
// Standard_IMPORT void FT1(const Standard_Boolean);
// Standard_IMPORT void FT2(const Standard_Boolean);
// T.Add("toto",(tf_value)FT1);
// T.Add("titi",(tf_value)FT2);
//
// Valuation a Standard_True de la variable de controle gouvernee par FT1 :
//       
// T.Set("toto",Standard_True);
//
// 2/ trace generale
// Une fonction de trace generale prend 3 arguments :
//   - Standard_Boolean b
//   - Standard_Integer n
//   - char **a
//
// le type tf_intarg represente une telle fonction de trace
//
// Ajouter une fonction de trace FT3 de nom "aaaaaa" a l objet de trace T :
//
// Standard_IMPORT void FT3(const Standard_Boolean,const Standard_Integer,const char**);
// T.Add((tf_intarg)FT3);
//
// Chargement de la fonction de trace FT3 par b,n,a :
// T.Set("aaaaaa",b,n,a);
//
//
// TestTopOpeTools.hxx definit l objet theTrace (classe TestTopOpeTools_Trace)
//
//----------------------------------------------------------------------------

class TestTopOpeTools_Trace {
  
public:
  
  TestTopOpeTools_Trace(const Standard_Integer nbmaxentry,
			const TCollection_AsciiString& genre);
  TestTopOpeTools_Trace(const Standard_Integer nbmaxentry);

  Standard_Integer Add(const t_flag flag, tf_value func);
  Standard_Integer SetVerbose(const Standard_Boolean b);
  Standard_Integer SetVerbose(const t_flag flag, const Standard_Boolean b);
  Standard_Integer Set(const Standard_Integer mute,
		       const t_flag flag, const t_value value);
  
  Standard_Integer Add(const t_flag flag, tf_intarg func);
  Standard_Integer Add(const t_flag flag, tf_int_intarg func);
  Standard_Integer Set(const Standard_Integer mute,
		       const t_flag flag, const t_value value, 
		       Standard_Integer narg, const char** args);
  
  void Dump();
  void Reset(const t_value);
  Standard_Boolean IsEmpty() { return (mynbentries == 0); }
  const TCollection_AsciiString& Genre() { return mygenre; }
  
  Standard_Boolean Exist(const t_flag flag, Standard_Integer& index);
  Standard_Boolean Exist(const tf_value func, Standard_Integer& index);

private:
  
  // ==== Methods
  
  const t_flag Getflag(const Standard_Integer index);
  const tf_value Getfunc(const Standard_Integer index);
  const te_ftyp Getftyp(const Standard_Integer index);
  Standard_Integer Add(const t_flag flag,const tf_value func,const te_ftyp ftyp);
  
  // ==== Fields
  
  TCollection_AsciiString     mygenre;
  Standard_Integer            myfirstentry,mynbmaxentry,mynbentries;
  TColStd_Array1OfAsciiString myflag;
  TColStd_Array1OfInteger     myfunc;
  TColStd_Array1OfInteger     myftyp;
  Standard_Boolean            myverbose;
  TColStd_Array1OfBoolean     myfverbose;
};

#endif
