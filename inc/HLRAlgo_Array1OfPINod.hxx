// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _HLRAlgo_Array1OfPINod_HeaderFile
#define _HLRAlgo_Array1OfPINod_HeaderFile

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
#ifndef _Handle_HLRAlgo_PolyInternalNode_HeaderFile
#include <Handle_HLRAlgo_PolyInternalNode.hxx>
#endif
class Standard_RangeError;
class Standard_DimensionMismatch;
class Standard_OutOfRange;
class Standard_OutOfMemory;
class HLRAlgo_PolyInternalNode;



class HLRAlgo_Array1OfPINod  {
public:

  DEFINE_STANDARD_ALLOC

  
  Standard_EXPORT   HLRAlgo_Array1OfPINod(const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT   HLRAlgo_Array1OfPINod(const Handle(HLRAlgo_PolyInternalNode)& Item,const Standard_Integer Low,const Standard_Integer Up);
  
  Standard_EXPORT     void Init(const Handle(HLRAlgo_PolyInternalNode)& V) ;
  
  Standard_EXPORT     void Destroy() ;
~HLRAlgo_Array1OfPINod()
{
  Destroy();
}
  
        Standard_Boolean IsAllocated() const;
  
  Standard_EXPORT    const HLRAlgo_Array1OfPINod& Assign(const HLRAlgo_Array1OfPINod& Other) ;
   const HLRAlgo_Array1OfPINod& operator =(const HLRAlgo_Array1OfPINod& Other) 
{
  return Assign(Other);
}
  
        Standard_Integer Length() const;
  
        Standard_Integer Lower() const;
  
        Standard_Integer Upper() const;
  
        void SetValue(const Standard_Integer Index,const Handle(HLRAlgo_PolyInternalNode)& Value) ;
  
       const Handle_HLRAlgo_PolyInternalNode& Value(const Standard_Integer Index) const;
     const Handle_HLRAlgo_PolyInternalNode& operator ()(const Standard_Integer Index) const
{
  return Value(Index);
}
  
        Handle_HLRAlgo_PolyInternalNode& ChangeValue(const Standard_Integer Index) ;
      Handle_HLRAlgo_PolyInternalNode& operator ()(const Standard_Integer Index) 
{
  return ChangeValue(Index);
}





protected:





private:

  
  Standard_EXPORT   HLRAlgo_Array1OfPINod(const HLRAlgo_Array1OfPINod& AnArray);


Standard_Integer myLowerBound;
Standard_Integer myUpperBound;
Standard_Address myStart;
Standard_Boolean isAllocated;


};

#define Array1Item Handle_HLRAlgo_PolyInternalNode
#define Array1Item_hxx <HLRAlgo_PolyInternalNode.hxx>
#define TCollection_Array1 HLRAlgo_Array1OfPINod
#define TCollection_Array1_hxx <HLRAlgo_Array1OfPINod.hxx>

#include <TCollection_Array1.lxx>

#undef Array1Item
#undef Array1Item_hxx
#undef TCollection_Array1
#undef TCollection_Array1_hxx


// other Inline functions and methods (like "C++: function call" methods)


#endif
