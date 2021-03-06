// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _Expr_Array1OfNamedUnknown_HeaderFile
#define _Expr_Array1OfNamedUnknown_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineAlloc_HeaderFile
#include <Standard_DefineAlloc.hxx>
#endif
#ifndef _Standard_Macro_HeaderFile
#include <Standard_Macro.hxx>
#endif

#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Standard_Address_HeaderFile
#include <Standard_Address.hxx>
#endif
#ifndef _Standard_Boolean_HeaderFile
#include <Standard_Boolean.hxx>
#endif
#ifndef _Handle_Expr_NamedUnknown_HeaderFile
#include <Handle_Expr_NamedUnknown.hxx>
#endif
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class Expr_NamedUnknown;



class Expr_Array1OfNamedUnknown  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   Expr_Array1OfNamedUnknown(const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT   Expr_Array1OfNamedUnknown(const Handle(Expr_NamedUnknown)& Item,const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT     void Init(const Handle(Expr_NamedUnknown)& V) ;
  
  Standard_EXPORT     void Destroy() ;
~Expr_Array1OfNamedUnknown()
{
  Destroy();
}
  
        Standard_Boolean IsAllocated() const;
  
  Standard_EXPORT    const Expr_Array1OfNamedUnknown& Assign(const Expr_Array1OfNamedUnknown& Other) ;
   const Expr_Array1OfNamedUnknown& operator =(const Expr_Array1OfNamedUnknown& Other) 
{
  return Assign(Other);
}
  
        Standard_Integer Length() const;
  
        Standard_Integer Lower() const;
  
        Standard_Integer Upper() const;
  
        void SetValue(const Standard_Integer Index,const Handle(Expr_NamedUnknown)& Value) ;
  
       const Handle_Expr_NamedUnknown& Value(const Standard_Integer Index) const;
     const Handle_Expr_NamedUnknown& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
        Handle_Expr_NamedUnknown& ChangeValue(const Standard_Integer Index) ;
      Handle_Expr_NamedUnknown& operator ()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}





protected:





private:

  
  Standard_EXPORT   Expr_Array1OfNamedUnknown(const Expr_Array1OfNamedUnknown& AnArray);


Standard_Integer myLowerBound;
Standard_Integer myUpperBound;
Standard_Address myStart;
Standard_Boolean isAllocated;


};

#define Array1Item Handle_Expr_NamedUnknown
#define Array1Item_hxx <Expr_NamedUnknown.hxx>
#define TCollection_Array1 Expr_Array1OfNamedUnknown
#define TCollection_Array1_hxx <Expr_Array1OfNamedUnknown.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
