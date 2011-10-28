// This file is generated by WOK (CPPExt).
// Please do not edit this file; modify original file instead.
// The copyright and license terms as defined for the original file apply to 
// this header file considered to be the "object code" form of the original source.

#ifndef _MDocStd_XLinkRetrievalDriver_HeaderFile
#define _MDocStd_XLinkRetrievalDriver_HeaderFile

#ifndef _Standard_HeaderFile
#include <Standard.hxx>
#endif
#ifndef _Standard_DefineHandle_HeaderFile
#include <Standard_DefineHandle.hxx>
#endif
#ifndef _Handle_MDocStd_XLinkRetrievalDriver_HeaderFile
#include <Handle_MDocStd_XLinkRetrievalDriver.hxx>
#endif

#ifndef _MDF_ARDriver_HeaderFile
#include <MDF_ARDriver.hxx>
#endif
#ifndef _Handle_CDM_MessageDriver_HeaderFile
#include <Handle_CDM_MessageDriver.hxx>
#endif
#ifndef _Standard_Integer_HeaderFile
#include <Standard_Integer.hxx>
#endif
#ifndef _Handle_Standard_Type_HeaderFile
#include <Handle_Standard_Type.hxx>
#endif
#ifndef _Handle_TDF_Attribute_HeaderFile
#include <Handle_TDF_Attribute.hxx>
#endif
#ifndef _Handle_PDF_Attribute_HeaderFile
#include <Handle_PDF_Attribute.hxx>
#endif
#ifndef _Handle_MDF_RRelocationTable_HeaderFile
#include <Handle_MDF_RRelocationTable.hxx>
#endif
class CDM_MessageDriver;
class Standard_Type;
class TDF_Attribute;
class PDF_Attribute;
class MDF_RRelocationTable;


//! Tool used to translate a persistent XLink into a <br>
//!          transient one. <br>
class MDocStd_XLinkRetrievalDriver : public MDF_ARDriver {

public:

  
  Standard_EXPORT   MDocStd_XLinkRetrievalDriver(const Handle(CDM_MessageDriver)& theMessageDriver);
  //! Returns the version number from which the driver <br>
//!          is available: 0. <br>
  Standard_EXPORT     Standard_Integer VersionNumber() const;
  //! Returns the type XLink from PXref. <br>
  Standard_EXPORT     Handle_Standard_Type SourceType() const;
  
  Standard_EXPORT     Handle_TDF_Attribute NewEmpty() const;
  
  Standard_EXPORT     void Paste(const Handle(PDF_Attribute)& aSource,const Handle(TDF_Attribute)& aTarget,const Handle(MDF_RRelocationTable)& aRelocTable) const;




  DEFINE_STANDARD_RTTI(MDocStd_XLinkRetrievalDriver)

protected:




private: 




};





// other Inline functions and methods (like "C++: function call" methods)


#endif