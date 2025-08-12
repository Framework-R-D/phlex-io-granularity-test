// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIsmshovandIproject2dIRNTuplemIImIOmIConfigdIbuilddIAOSDict
#define R__NO_DEPRECATION

/*******************************************************************/
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#define G__DICTIONARY
#include "ROOT/RConfig.hxx"
#include "TClass.h"
#include "TDictAttributeMap.h"
#include "TInterpreter.h"
#include "TROOT.h"
#include "TBuffer.h"
#include "TMemberInspector.h"
#include "TInterpreter.h"
#include "TVirtualMutex.h"
#include "TError.h"

#ifndef G__ROOT
#define G__ROOT
#endif

#include "RtypesImp.h"
#include "TIsAProxy.h"
#include "TFileMergeInfo.h"
#include <algorithm>
#include "TCollectionProxyInfo.h"
/*******************************************************************/

#include "TDataMember.h"

// Header files passed as explicit arguments
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp"
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp"
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/HitWireWriterHelpers.hpp"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_FlatROI(void *p = nullptr);
   static void *newArray_FlatROI(Long_t size, void *p);
   static void delete_FlatROI(void *p);
   static void deleteArray_FlatROI(void *p);
   static void destruct_FlatROI(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FlatROI*)
   {
      ::FlatROI *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FlatROI >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("FlatROI", ::FlatROI::Class_Version(), "", 15,
                  typeid(::FlatROI), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FlatROI::Dictionary, isa_proxy, 4,
                  sizeof(::FlatROI) );
      instance.SetNew(&new_FlatROI);
      instance.SetNewArray(&newArray_FlatROI);
      instance.SetDelete(&delete_FlatROI);
      instance.SetDeleteArray(&deleteArray_FlatROI);
      instance.SetDestructor(&destruct_FlatROI);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FlatROI*)
   {
      return GenerateInitInstanceLocal(static_cast<::FlatROI*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::FlatROI*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventAOS(void *p = nullptr);
   static void *newArray_EventAOS(Long_t size, void *p);
   static void delete_EventAOS(void *p);
   static void deleteArray_EventAOS(void *p);
   static void destruct_EventAOS(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventAOS*)
   {
      ::EventAOS *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventAOS >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("EventAOS", ::EventAOS::Class_Version(), "", 27,
                  typeid(::EventAOS), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventAOS::Dictionary, isa_proxy, 4,
                  sizeof(::EventAOS) );
      instance.SetNew(&new_EventAOS);
      instance.SetNewArray(&newArray_EventAOS);
      instance.SetDelete(&delete_EventAOS);
      instance.SetDeleteArray(&deleteArray_EventAOS);
      instance.SetDestructor(&destruct_EventAOS);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventAOS*)
   {
      return GenerateInitInstanceLocal(static_cast<::EventAOS*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::EventAOS*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WireBase(void *p = nullptr);
   static void *newArray_WireBase(Long_t size, void *p);
   static void delete_WireBase(void *p);
   static void deleteArray_WireBase(void *p);
   static void destruct_WireBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WireBase*)
   {
      ::WireBase *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WireBase >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("WireBase", ::WireBase::Class_Version(), "", 52,
                  typeid(::WireBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WireBase::Dictionary, isa_proxy, 4,
                  sizeof(::WireBase) );
      instance.SetNew(&new_WireBase);
      instance.SetNewArray(&newArray_WireBase);
      instance.SetDelete(&delete_WireBase);
      instance.SetDeleteArray(&deleteArray_WireBase);
      instance.SetDestructor(&destruct_WireBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WireBase*)
   {
      return GenerateInitInstanceLocal(static_cast<::WireBase*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::WireBase*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WireROI(void *p = nullptr);
   static void *newArray_WireROI(Long_t size, void *p);
   static void delete_WireROI(void *p);
   static void deleteArray_WireROI(void *p);
   static void destruct_WireROI(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WireROI*)
   {
      ::WireROI *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WireROI >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("WireROI", ::WireROI::Class_Version(), "", 61,
                  typeid(::WireROI), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WireROI::Dictionary, isa_proxy, 4,
                  sizeof(::WireROI) );
      instance.SetNew(&new_WireROI);
      instance.SetNewArray(&newArray_WireROI);
      instance.SetDelete(&delete_WireROI);
      instance.SetDeleteArray(&deleteArray_WireROI);
      instance.SetDestructor(&destruct_WireROI);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WireROI*)
   {
      return GenerateInitInstanceLocal(static_cast<::WireROI*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::WireROI*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr FlatROI::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *FlatROI::Class_Name()
{
   return "FlatROI";
}

//______________________________________________________________________________
const char *FlatROI::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FlatROI*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int FlatROI::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FlatROI*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FlatROI::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FlatROI*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FlatROI::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FlatROI*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventAOS::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *EventAOS::Class_Name()
{
   return "EventAOS";
}

//______________________________________________________________________________
const char *EventAOS::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventAOS*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int EventAOS::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventAOS*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventAOS::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventAOS*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventAOS::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventAOS*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WireBase::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *WireBase::Class_Name()
{
   return "WireBase";
}

//______________________________________________________________________________
const char *WireBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireBase*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int WireBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireBase*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WireBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireBase*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WireBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireBase*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WireROI::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *WireROI::Class_Name()
{
   return "WireROI";
}

//______________________________________________________________________________
const char *WireROI::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireROI*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int WireROI::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireROI*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WireROI::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireROI*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WireROI::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireROI*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void FlatROI::Streamer(TBuffer &R__b)
{
   // Stream an object of class FlatROI.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FlatROI::Class(),this);
   } else {
      R__b.WriteClassBuffer(FlatROI::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FlatROI(void *p) {
      return  p ? new(p) ::FlatROI : new ::FlatROI;
   }
   static void *newArray_FlatROI(Long_t nElements, void *p) {
      return p ? new(p) ::FlatROI[nElements] : new ::FlatROI[nElements];
   }
   // Wrapper around operator delete
   static void delete_FlatROI(void *p) {
      delete (static_cast<::FlatROI*>(p));
   }
   static void deleteArray_FlatROI(void *p) {
      delete [] (static_cast<::FlatROI*>(p));
   }
   static void destruct_FlatROI(void *p) {
      typedef ::FlatROI current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::FlatROI

//______________________________________________________________________________
void EventAOS::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventAOS.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventAOS::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventAOS::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventAOS(void *p) {
      return  p ? new(p) ::EventAOS : new ::EventAOS;
   }
   static void *newArray_EventAOS(Long_t nElements, void *p) {
      return p ? new(p) ::EventAOS[nElements] : new ::EventAOS[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventAOS(void *p) {
      delete (static_cast<::EventAOS*>(p));
   }
   static void deleteArray_EventAOS(void *p) {
      delete [] (static_cast<::EventAOS*>(p));
   }
   static void destruct_EventAOS(void *p) {
      typedef ::EventAOS current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::EventAOS

//______________________________________________________________________________
void WireBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class WireBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WireBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(WireBase::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WireBase(void *p) {
      return  p ? new(p) ::WireBase : new ::WireBase;
   }
   static void *newArray_WireBase(Long_t nElements, void *p) {
      return p ? new(p) ::WireBase[nElements] : new ::WireBase[nElements];
   }
   // Wrapper around operator delete
   static void delete_WireBase(void *p) {
      delete (static_cast<::WireBase*>(p));
   }
   static void deleteArray_WireBase(void *p) {
      delete [] (static_cast<::WireBase*>(p));
   }
   static void destruct_WireBase(void *p) {
      typedef ::WireBase current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::WireBase

//______________________________________________________________________________
void WireROI::Streamer(TBuffer &R__b)
{
   // Stream an object of class WireROI.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WireROI::Class(),this);
   } else {
      R__b.WriteClassBuffer(WireROI::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WireROI(void *p) {
      return  p ? new(p) ::WireROI : new ::WireROI;
   }
   static void *newArray_WireROI(Long_t nElements, void *p) {
      return p ? new(p) ::WireROI[nElements] : new ::WireROI[nElements];
   }
   // Wrapper around operator delete
   static void delete_WireROI(void *p) {
      delete (static_cast<::WireROI*>(p));
   }
   static void deleteArray_WireROI(void *p) {
      delete [] (static_cast<::WireROI*>(p));
   }
   static void destruct_WireROI(void *p) {
      typedef ::WireROI current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::WireROI

namespace ROOT {
   static TClass *vectorlEfloatgR_Dictionary();
   static void vectorlEfloatgR_TClassManip(TClass*);
   static void *new_vectorlEfloatgR(void *p = nullptr);
   static void *newArray_vectorlEfloatgR(Long_t size, void *p);
   static void delete_vectorlEfloatgR(void *p);
   static void deleteArray_vectorlEfloatgR(void *p);
   static void destruct_vectorlEfloatgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<float>*)
   {
      vector<float> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<float>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<float>", -2, "vector", 389,
                  typeid(vector<float>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEfloatgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<float>) );
      instance.SetNew(&new_vectorlEfloatgR);
      instance.SetNewArray(&newArray_vectorlEfloatgR);
      instance.SetDelete(&delete_vectorlEfloatgR);
      instance.SetDeleteArray(&deleteArray_vectorlEfloatgR);
      instance.SetDestructor(&destruct_vectorlEfloatgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<float> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<float>","std::vector<float, std::allocator<float> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<float>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEfloatgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<float>*>(nullptr))->GetClass();
      vectorlEfloatgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEfloatgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEfloatgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float> : new vector<float>;
   }
   static void *newArray_vectorlEfloatgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<float>[nElements] : new vector<float>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEfloatgR(void *p) {
      delete (static_cast<vector<float>*>(p));
   }
   static void deleteArray_vectorlEfloatgR(void *p) {
      delete [] (static_cast<vector<float>*>(p));
   }
   static void destruct_vectorlEfloatgR(void *p) {
      typedef vector<float> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<float>

namespace ROOT {
   static TClass *vectorlEWireIndividualgR_Dictionary();
   static void vectorlEWireIndividualgR_TClassManip(TClass*);
   static void *new_vectorlEWireIndividualgR(void *p = nullptr);
   static void *newArray_vectorlEWireIndividualgR(Long_t size, void *p);
   static void delete_vectorlEWireIndividualgR(void *p);
   static void deleteArray_vectorlEWireIndividualgR(void *p);
   static void destruct_vectorlEWireIndividualgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<WireIndividual>*)
   {
      vector<WireIndividual> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<WireIndividual>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<WireIndividual>", -2, "vector", 389,
                  typeid(vector<WireIndividual>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEWireIndividualgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<WireIndividual>) );
      instance.SetNew(&new_vectorlEWireIndividualgR);
      instance.SetNewArray(&newArray_vectorlEWireIndividualgR);
      instance.SetDelete(&delete_vectorlEWireIndividualgR);
      instance.SetDeleteArray(&deleteArray_vectorlEWireIndividualgR);
      instance.SetDestructor(&destruct_vectorlEWireIndividualgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<WireIndividual> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<WireIndividual>","std::vector<WireIndividual, std::allocator<WireIndividual> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<WireIndividual>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEWireIndividualgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<WireIndividual>*>(nullptr))->GetClass();
      vectorlEWireIndividualgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEWireIndividualgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEWireIndividualgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<WireIndividual> : new vector<WireIndividual>;
   }
   static void *newArray_vectorlEWireIndividualgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<WireIndividual>[nElements] : new vector<WireIndividual>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEWireIndividualgR(void *p) {
      delete (static_cast<vector<WireIndividual>*>(p));
   }
   static void deleteArray_vectorlEWireIndividualgR(void *p) {
      delete [] (static_cast<vector<WireIndividual>*>(p));
   }
   static void destruct_vectorlEWireIndividualgR(void *p) {
      typedef vector<WireIndividual> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<WireIndividual>

namespace ROOT {
   static TClass *vectorlEHitIndividualgR_Dictionary();
   static void vectorlEHitIndividualgR_TClassManip(TClass*);
   static void *new_vectorlEHitIndividualgR(void *p = nullptr);
   static void *newArray_vectorlEHitIndividualgR(Long_t size, void *p);
   static void delete_vectorlEHitIndividualgR(void *p);
   static void deleteArray_vectorlEHitIndividualgR(void *p);
   static void destruct_vectorlEHitIndividualgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<HitIndividual>*)
   {
      vector<HitIndividual> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<HitIndividual>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<HitIndividual>", -2, "vector", 389,
                  typeid(vector<HitIndividual>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEHitIndividualgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<HitIndividual>) );
      instance.SetNew(&new_vectorlEHitIndividualgR);
      instance.SetNewArray(&newArray_vectorlEHitIndividualgR);
      instance.SetDelete(&delete_vectorlEHitIndividualgR);
      instance.SetDeleteArray(&deleteArray_vectorlEHitIndividualgR);
      instance.SetDestructor(&destruct_vectorlEHitIndividualgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<HitIndividual> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<HitIndividual>","std::vector<HitIndividual, std::allocator<HitIndividual> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<HitIndividual>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEHitIndividualgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<HitIndividual>*>(nullptr))->GetClass();
      vectorlEHitIndividualgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEHitIndividualgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEHitIndividualgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<HitIndividual> : new vector<HitIndividual>;
   }
   static void *newArray_vectorlEHitIndividualgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<HitIndividual>[nElements] : new vector<HitIndividual>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEHitIndividualgR(void *p) {
      delete (static_cast<vector<HitIndividual>*>(p));
   }
   static void deleteArray_vectorlEHitIndividualgR(void *p) {
      delete [] (static_cast<vector<HitIndividual>*>(p));
   }
   static void destruct_vectorlEHitIndividualgR(void *p) {
      typedef vector<HitIndividual> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<HitIndividual>

namespace ROOT {
   // Registration Schema evolution read functions
   int RecordReadRules_AOSDict() {
      return 0;
   }
   static int _R__UNIQUE_DICT_(ReadRules_AOSDict) = RecordReadRules_AOSDict();R__UseDummy(_R__UNIQUE_DICT_(ReadRules_AOSDict));
} // namespace ROOT
namespace {
  void TriggerDictionaryInitialization_AOSDict_Impl() {
    static const char* headers[] = {
"/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp",
"/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp",
"/home/smshovan/project2/RNTuple-I-O-Config/include/HitWireWriterHelpers.hpp",
nullptr
    };
    static const char* includePaths[] = {
"/home/smshovan/spack/opt/spack/linux-cascadelake/root-6.36.02-ujt3ksktiwa6az4bc3ekvmzfmi4ydm6d/include/root",
"/home/smshovan/project2/RNTuple-I-O-Config/build/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "AOSDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/HitWireWriterHelpers.hpp")))  FlatROI;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/HitWireWriterHelpers.hpp")))  EventAOS;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/HitWireWriterHelpers.hpp")))  WireBase;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/HitWireWriterHelpers.hpp")))  WireROI;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "AOSDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp"
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp"
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/HitWireWriterHelpers.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"EventAOS", payloadCode, "@",
"FlatROI", payloadCode, "@",
"WireBase", payloadCode, "@",
"WireROI", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("AOSDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_AOSDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_AOSDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_AOSDict() {
  TriggerDictionaryInitialization_AOSDict_Impl();
}
