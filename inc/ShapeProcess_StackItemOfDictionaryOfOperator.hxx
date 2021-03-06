// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _ShapeProcess_StackItemOfDictionaryOfOperator_HeaderFile
#define _ShapeProcess_StackItemOfDictionaryOfOperator_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_ShapeProcess_StackItemOfDictionaryOfOperator_HeaderFile
#include <Handle_ShapeProcess_StackItemOfDictionaryOfOperator.hxx>
#endif

#ifndef _Handle_ShapeProcess_DictionaryOfOperator_HeaderFile
#include <Handle_ShapeProcess_DictionaryOfOperator.hxx>
#endif
#ifndef _Handle_ShapeProcess_StackItemOfDictionaryOfOperator_HeaderFile
#include <Handle_ShapeProcess_StackItemOfDictionaryOfOperator.hxx>
#endif
#ifndef _MMgt_TShared_HeaderFile
#include <MMgt_TShared.hxx>
#endif
#ifndef _Handle_ShapeProcess_Operator_HeaderFile
#include <Handle_ShapeProcess_Operator.hxx>
#endif
class ShapeProcess_DictionaryOfOperator;
class ShapeProcess_Operator;
class ShapeProcess_IteratorOfDictionaryOfOperator;



class ShapeProcess_StackItemOfDictionaryOfOperator : public MMgt_TShared {

public:

  
  Standard_EXPORT   ShapeProcess_StackItemOfDictionaryOfOperator();
  
  Standard_EXPORT   ShapeProcess_StackItemOfDictionaryOfOperator(const Handle(ShapeProcess_StackItemOfDictionaryOfOperator)& previous);
  
  Standard_EXPORT     Handle_ShapeProcess_StackItemOfDictionaryOfOperator Previous() const;
  
  Standard_EXPORT     Handle_ShapeProcess_DictionaryOfOperator Value() const;
  
  Standard_EXPORT     void SetValue(const Handle(ShapeProcess_DictionaryOfOperator)& cval) ;




  DEFINE_STANDARD_RTTI(ShapeProcess_StackItemOfDictionaryOfOperator)

protected:




private: 


Handle_ShapeProcess_DictionaryOfOperator thevalue;
Handle_ShapeProcess_StackItemOfDictionaryOfOperator theprev;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
