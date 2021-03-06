// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _StepRepr_ConfigurationEffectivity_HeaderFile
#define _StepRepr_ConfigurationEffectivity_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_StepRepr_ConfigurationEffectivity_HeaderFile
#include <Handle_StepRepr_ConfigurationEffectivity.hxx>
#endif

#ifndef _Handle_StepRepr_ConfigurationDesign_HeaderFile
#include <Handle_StepRepr_ConfigurationDesign.hxx>
#endif
#ifndef _StepBasic_ProductDefinitionEffectivity_HeaderFile
#include <StepBasic_ProductDefinitionEffectivity.hxx>
#endif
#ifndef _Handle_TCollection_HAsciiString_HeaderFile
#include <Handle_TCollection_HAsciiString.hxx>
#endif
#ifndef _Handle_StepBasic_ProductDefinitionRelationship_HeaderFile
#include <Handle_StepBasic_ProductDefinitionRelationship.hxx>
#endif
class StepRepr_ConfigurationDesign;
class TCollection_HAsciiString;
class StepBasic_ProductDefinitionRelationship;


//! Representation of STEP entity ConfigurationEffectivity <br>
class StepRepr_ConfigurationEffectivity : public StepBasic_ProductDefinitionEffectivity {

public:

  //! Empty constructor <br>
  Standard_EXPORT   StepRepr_ConfigurationEffectivity();
  //! Initialize all fields (own and inherited) <br>
  Standard_EXPORT     void Init(const Handle(TCollection_HAsciiString)& aEffectivity_Id,const Handle(StepBasic_ProductDefinitionRelationship)& aProductDefinitionEffectivity_Usage,const Handle(StepRepr_ConfigurationDesign)& aConfiguration) ;
  //! Returns field Configuration <br>
  Standard_EXPORT     Handle_StepRepr_ConfigurationDesign Configuration() const;
  //! Set field Configuration <br>
  Standard_EXPORT     void SetConfiguration(const Handle(StepRepr_ConfigurationDesign)& Configuration) ;




  DEFINE_STANDARD_RTTI(StepRepr_ConfigurationEffectivity)

protected:




private: 


Handle_StepRepr_ConfigurationDesign theConfiguration;


};





// other Inline functions and methods (like "C++: function call" methods)


#endif
