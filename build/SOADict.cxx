// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIsmshovandIproject2dIRNTuplemIImIOmIConfigdIbuilddISOADict
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

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_SOAHitVector(void *p = nullptr);
   static void *newArray_SOAHitVector(Long_t size, void *p);
   static void delete_SOAHitVector(void *p);
   static void deleteArray_SOAHitVector(void *p);
   static void destruct_SOAHitVector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SOAHitVector*)
   {
      ::SOAHitVector *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SOAHitVector >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SOAHitVector", ::SOAHitVector::Class_Version(), "", 126,
                  typeid(::SOAHitVector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SOAHitVector::Dictionary, isa_proxy, 4,
                  sizeof(::SOAHitVector) );
      instance.SetNew(&new_SOAHitVector);
      instance.SetNewArray(&newArray_SOAHitVector);
      instance.SetDelete(&delete_SOAHitVector);
      instance.SetDeleteArray(&deleteArray_SOAHitVector);
      instance.SetDestructor(&destruct_SOAHitVector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SOAHitVector*)
   {
      return GenerateInitInstanceLocal(static_cast<::SOAHitVector*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SOAHitVector*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SOAHit(void *p = nullptr);
   static void *newArray_SOAHit(Long_t size, void *p);
   static void delete_SOAHit(void *p);
   static void deleteArray_SOAHit(void *p);
   static void destruct_SOAHit(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SOAHit*)
   {
      ::SOAHit *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SOAHit >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SOAHit", ::SOAHit::Class_Version(), "", 154,
                  typeid(::SOAHit), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SOAHit::Dictionary, isa_proxy, 4,
                  sizeof(::SOAHit) );
      instance.SetNew(&new_SOAHit);
      instance.SetNewArray(&newArray_SOAHit);
      instance.SetDelete(&delete_SOAHit);
      instance.SetDeleteArray(&deleteArray_SOAHit);
      instance.SetDestructor(&destruct_SOAHit);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SOAHit*)
   {
      return GenerateInitInstanceLocal(static_cast<::SOAHit*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SOAHit*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SOAROI(void *p = nullptr);
   static void *newArray_SOAROI(Long_t size, void *p);
   static void delete_SOAROI(void *p);
   static void deleteArray_SOAROI(void *p);
   static void destruct_SOAROI(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SOAROI*)
   {
      ::SOAROI *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SOAROI >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SOAROI", ::SOAROI::Class_Version(), "", 84,
                  typeid(::SOAROI), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SOAROI::Dictionary, isa_proxy, 4,
                  sizeof(::SOAROI) );
      instance.SetNew(&new_SOAROI);
      instance.SetNewArray(&newArray_SOAROI);
      instance.SetDelete(&delete_SOAROI);
      instance.SetDeleteArray(&deleteArray_SOAROI);
      instance.SetDestructor(&destruct_SOAROI);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SOAROI*)
   {
      return GenerateInitInstanceLocal(static_cast<::SOAROI*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SOAROI*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SOAWire(void *p = nullptr);
   static void *newArray_SOAWire(Long_t size, void *p);
   static void delete_SOAWire(void *p);
   static void deleteArray_SOAWire(void *p);
   static void destruct_SOAWire(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SOAWire*)
   {
      ::SOAWire *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SOAWire >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SOAWire", ::SOAWire::Class_Version(), "", 89,
                  typeid(::SOAWire), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SOAWire::Dictionary, isa_proxy, 4,
                  sizeof(::SOAWire) );
      instance.SetNew(&new_SOAWire);
      instance.SetNewArray(&newArray_SOAWire);
      instance.SetDelete(&delete_SOAWire);
      instance.SetDeleteArray(&deleteArray_SOAWire);
      instance.SetDestructor(&destruct_SOAWire);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SOAWire*)
   {
      return GenerateInitInstanceLocal(static_cast<::SOAWire*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SOAWire*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SOAWireBase(void *p = nullptr);
   static void *newArray_SOAWireBase(Long_t size, void *p);
   static void delete_SOAWireBase(void *p);
   static void deleteArray_SOAWireBase(void *p);
   static void destruct_SOAWireBase(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SOAWireBase*)
   {
      ::SOAWireBase *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SOAWireBase >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SOAWireBase", ::SOAWireBase::Class_Version(), "", 98,
                  typeid(::SOAWireBase), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SOAWireBase::Dictionary, isa_proxy, 4,
                  sizeof(::SOAWireBase) );
      instance.SetNew(&new_SOAWireBase);
      instance.SetNewArray(&newArray_SOAWireBase);
      instance.SetDelete(&delete_SOAWireBase);
      instance.SetDeleteArray(&deleteArray_SOAWireBase);
      instance.SetDestructor(&destruct_SOAWireBase);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SOAWireBase*)
   {
      return GenerateInitInstanceLocal(static_cast<::SOAWireBase*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SOAWireBase*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_FlatSOAROI(void *p = nullptr);
   static void *newArray_FlatSOAROI(Long_t size, void *p);
   static void delete_FlatSOAROI(void *p);
   static void deleteArray_FlatSOAROI(void *p);
   static void destruct_FlatSOAROI(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::FlatSOAROI*)
   {
      ::FlatSOAROI *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::FlatSOAROI >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("FlatSOAROI", ::FlatSOAROI::Class_Version(), "", 106,
                  typeid(::FlatSOAROI), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::FlatSOAROI::Dictionary, isa_proxy, 4,
                  sizeof(::FlatSOAROI) );
      instance.SetNew(&new_FlatSOAROI);
      instance.SetNewArray(&newArray_FlatSOAROI);
      instance.SetDelete(&delete_FlatSOAROI);
      instance.SetDeleteArray(&deleteArray_FlatSOAROI);
      instance.SetDestructor(&destruct_FlatSOAROI);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::FlatSOAROI*)
   {
      return GenerateInitInstanceLocal(static_cast<::FlatSOAROI*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::FlatSOAROI*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_SOAWireVector(void *p = nullptr);
   static void *newArray_SOAWireVector(Long_t size, void *p);
   static void delete_SOAWireVector(void *p);
   static void deleteArray_SOAWireVector(void *p);
   static void destruct_SOAWireVector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::SOAWireVector*)
   {
      ::SOAWireVector *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::SOAWireVector >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("SOAWireVector", ::SOAWireVector::Class_Version(), "", 113,
                  typeid(::SOAWireVector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::SOAWireVector::Dictionary, isa_proxy, 4,
                  sizeof(::SOAWireVector) );
      instance.SetNew(&new_SOAWireVector);
      instance.SetNewArray(&newArray_SOAWireVector);
      instance.SetDelete(&delete_SOAWireVector);
      instance.SetDeleteArray(&deleteArray_SOAWireVector);
      instance.SetDestructor(&destruct_SOAWireVector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::SOAWireVector*)
   {
      return GenerateInitInstanceLocal(static_cast<::SOAWireVector*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::SOAWireVector*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_EventSOA(void *p = nullptr);
   static void *newArray_EventSOA(Long_t size, void *p);
   static void delete_EventSOA(void *p);
   static void deleteArray_EventSOA(void *p);
   static void destruct_EventSOA(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::EventSOA*)
   {
      ::EventSOA *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::EventSOA >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("EventSOA", ::EventSOA::Class_Version(), "", 121,
                  typeid(::EventSOA), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::EventSOA::Dictionary, isa_proxy, 4,
                  sizeof(::EventSOA) );
      instance.SetNew(&new_EventSOA);
      instance.SetNewArray(&newArray_EventSOA);
      instance.SetDelete(&delete_EventSOA);
      instance.SetDeleteArray(&deleteArray_EventSOA);
      instance.SetDestructor(&destruct_EventSOA);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::EventSOA*)
   {
      return GenerateInitInstanceLocal(static_cast<::EventSOA*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::EventSOA*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr SOAHitVector::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SOAHitVector::Class_Name()
{
   return "SOAHitVector";
}

//______________________________________________________________________________
const char *SOAHitVector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAHitVector*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SOAHitVector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAHitVector*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SOAHitVector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAHitVector*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SOAHitVector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAHitVector*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SOAHit::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SOAHit::Class_Name()
{
   return "SOAHit";
}

//______________________________________________________________________________
const char *SOAHit::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAHit*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SOAHit::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAHit*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SOAHit::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAHit*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SOAHit::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAHit*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SOAROI::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SOAROI::Class_Name()
{
   return "SOAROI";
}

//______________________________________________________________________________
const char *SOAROI::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAROI*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SOAROI::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAROI*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SOAROI::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAROI*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SOAROI::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAROI*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SOAWire::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SOAWire::Class_Name()
{
   return "SOAWire";
}

//______________________________________________________________________________
const char *SOAWire::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAWire*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SOAWire::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAWire*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SOAWire::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAWire*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SOAWire::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAWire*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SOAWireBase::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SOAWireBase::Class_Name()
{
   return "SOAWireBase";
}

//______________________________________________________________________________
const char *SOAWireBase::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAWireBase*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SOAWireBase::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAWireBase*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SOAWireBase::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAWireBase*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SOAWireBase::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAWireBase*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr FlatSOAROI::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *FlatSOAROI::Class_Name()
{
   return "FlatSOAROI";
}

//______________________________________________________________________________
const char *FlatSOAROI::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FlatSOAROI*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int FlatSOAROI::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::FlatSOAROI*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *FlatSOAROI::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FlatSOAROI*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *FlatSOAROI::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::FlatSOAROI*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr SOAWireVector::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *SOAWireVector::Class_Name()
{
   return "SOAWireVector";
}

//______________________________________________________________________________
const char *SOAWireVector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAWireVector*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int SOAWireVector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::SOAWireVector*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *SOAWireVector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAWireVector*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *SOAWireVector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::SOAWireVector*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr EventSOA::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *EventSOA::Class_Name()
{
   return "EventSOA";
}

//______________________________________________________________________________
const char *EventSOA::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventSOA*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int EventSOA::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::EventSOA*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *EventSOA::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventSOA*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *EventSOA::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::EventSOA*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void SOAHitVector::Streamer(TBuffer &R__b)
{
   // Stream an object of class SOAHitVector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SOAHitVector::Class(),this);
   } else {
      R__b.WriteClassBuffer(SOAHitVector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SOAHitVector(void *p) {
      return  p ? new(p) ::SOAHitVector : new ::SOAHitVector;
   }
   static void *newArray_SOAHitVector(Long_t nElements, void *p) {
      return p ? new(p) ::SOAHitVector[nElements] : new ::SOAHitVector[nElements];
   }
   // Wrapper around operator delete
   static void delete_SOAHitVector(void *p) {
      delete (static_cast<::SOAHitVector*>(p));
   }
   static void deleteArray_SOAHitVector(void *p) {
      delete [] (static_cast<::SOAHitVector*>(p));
   }
   static void destruct_SOAHitVector(void *p) {
      typedef ::SOAHitVector current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SOAHitVector

//______________________________________________________________________________
void SOAHit::Streamer(TBuffer &R__b)
{
   // Stream an object of class SOAHit.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SOAHit::Class(),this);
   } else {
      R__b.WriteClassBuffer(SOAHit::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SOAHit(void *p) {
      return  p ? new(p) ::SOAHit : new ::SOAHit;
   }
   static void *newArray_SOAHit(Long_t nElements, void *p) {
      return p ? new(p) ::SOAHit[nElements] : new ::SOAHit[nElements];
   }
   // Wrapper around operator delete
   static void delete_SOAHit(void *p) {
      delete (static_cast<::SOAHit*>(p));
   }
   static void deleteArray_SOAHit(void *p) {
      delete [] (static_cast<::SOAHit*>(p));
   }
   static void destruct_SOAHit(void *p) {
      typedef ::SOAHit current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SOAHit

//______________________________________________________________________________
void SOAROI::Streamer(TBuffer &R__b)
{
   // Stream an object of class SOAROI.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SOAROI::Class(),this);
   } else {
      R__b.WriteClassBuffer(SOAROI::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SOAROI(void *p) {
      return  p ? new(p) ::SOAROI : new ::SOAROI;
   }
   static void *newArray_SOAROI(Long_t nElements, void *p) {
      return p ? new(p) ::SOAROI[nElements] : new ::SOAROI[nElements];
   }
   // Wrapper around operator delete
   static void delete_SOAROI(void *p) {
      delete (static_cast<::SOAROI*>(p));
   }
   static void deleteArray_SOAROI(void *p) {
      delete [] (static_cast<::SOAROI*>(p));
   }
   static void destruct_SOAROI(void *p) {
      typedef ::SOAROI current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SOAROI

//______________________________________________________________________________
void SOAWire::Streamer(TBuffer &R__b)
{
   // Stream an object of class SOAWire.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SOAWire::Class(),this);
   } else {
      R__b.WriteClassBuffer(SOAWire::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SOAWire(void *p) {
      return  p ? new(p) ::SOAWire : new ::SOAWire;
   }
   static void *newArray_SOAWire(Long_t nElements, void *p) {
      return p ? new(p) ::SOAWire[nElements] : new ::SOAWire[nElements];
   }
   // Wrapper around operator delete
   static void delete_SOAWire(void *p) {
      delete (static_cast<::SOAWire*>(p));
   }
   static void deleteArray_SOAWire(void *p) {
      delete [] (static_cast<::SOAWire*>(p));
   }
   static void destruct_SOAWire(void *p) {
      typedef ::SOAWire current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SOAWire

//______________________________________________________________________________
void SOAWireBase::Streamer(TBuffer &R__b)
{
   // Stream an object of class SOAWireBase.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SOAWireBase::Class(),this);
   } else {
      R__b.WriteClassBuffer(SOAWireBase::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SOAWireBase(void *p) {
      return  p ? new(p) ::SOAWireBase : new ::SOAWireBase;
   }
   static void *newArray_SOAWireBase(Long_t nElements, void *p) {
      return p ? new(p) ::SOAWireBase[nElements] : new ::SOAWireBase[nElements];
   }
   // Wrapper around operator delete
   static void delete_SOAWireBase(void *p) {
      delete (static_cast<::SOAWireBase*>(p));
   }
   static void deleteArray_SOAWireBase(void *p) {
      delete [] (static_cast<::SOAWireBase*>(p));
   }
   static void destruct_SOAWireBase(void *p) {
      typedef ::SOAWireBase current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SOAWireBase

//______________________________________________________________________________
void FlatSOAROI::Streamer(TBuffer &R__b)
{
   // Stream an object of class FlatSOAROI.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(FlatSOAROI::Class(),this);
   } else {
      R__b.WriteClassBuffer(FlatSOAROI::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_FlatSOAROI(void *p) {
      return  p ? new(p) ::FlatSOAROI : new ::FlatSOAROI;
   }
   static void *newArray_FlatSOAROI(Long_t nElements, void *p) {
      return p ? new(p) ::FlatSOAROI[nElements] : new ::FlatSOAROI[nElements];
   }
   // Wrapper around operator delete
   static void delete_FlatSOAROI(void *p) {
      delete (static_cast<::FlatSOAROI*>(p));
   }
   static void deleteArray_FlatSOAROI(void *p) {
      delete [] (static_cast<::FlatSOAROI*>(p));
   }
   static void destruct_FlatSOAROI(void *p) {
      typedef ::FlatSOAROI current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::FlatSOAROI

//______________________________________________________________________________
void SOAWireVector::Streamer(TBuffer &R__b)
{
   // Stream an object of class SOAWireVector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(SOAWireVector::Class(),this);
   } else {
      R__b.WriteClassBuffer(SOAWireVector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_SOAWireVector(void *p) {
      return  p ? new(p) ::SOAWireVector : new ::SOAWireVector;
   }
   static void *newArray_SOAWireVector(Long_t nElements, void *p) {
      return p ? new(p) ::SOAWireVector[nElements] : new ::SOAWireVector[nElements];
   }
   // Wrapper around operator delete
   static void delete_SOAWireVector(void *p) {
      delete (static_cast<::SOAWireVector*>(p));
   }
   static void deleteArray_SOAWireVector(void *p) {
      delete [] (static_cast<::SOAWireVector*>(p));
   }
   static void destruct_SOAWireVector(void *p) {
      typedef ::SOAWireVector current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::SOAWireVector

//______________________________________________________________________________
void EventSOA::Streamer(TBuffer &R__b)
{
   // Stream an object of class EventSOA.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(EventSOA::Class(),this);
   } else {
      R__b.WriteClassBuffer(EventSOA::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_EventSOA(void *p) {
      return  p ? new(p) ::EventSOA : new ::EventSOA;
   }
   static void *newArray_EventSOA(Long_t nElements, void *p) {
      return p ? new(p) ::EventSOA[nElements] : new ::EventSOA[nElements];
   }
   // Wrapper around operator delete
   static void delete_EventSOA(void *p) {
      delete (static_cast<::EventSOA*>(p));
   }
   static void deleteArray_EventSOA(void *p) {
      delete [] (static_cast<::EventSOA*>(p));
   }
   static void destruct_EventSOA(void *p) {
      typedef ::EventSOA current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::EventSOA

namespace ROOT {
   static TClass *vectorlEvectorlESOAROIgRsPgR_Dictionary();
   static void vectorlEvectorlESOAROIgRsPgR_TClassManip(TClass*);
   static void *new_vectorlEvectorlESOAROIgRsPgR(void *p = nullptr);
   static void *newArray_vectorlEvectorlESOAROIgRsPgR(Long_t size, void *p);
   static void delete_vectorlEvectorlESOAROIgRsPgR(void *p);
   static void deleteArray_vectorlEvectorlESOAROIgRsPgR(void *p);
   static void destruct_vectorlEvectorlESOAROIgRsPgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<vector<SOAROI> >*)
   {
      vector<vector<SOAROI> > *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<vector<SOAROI> >));
      static ::ROOT::TGenericClassInfo 
         instance("vector<vector<SOAROI> >", -2, "vector", 389,
                  typeid(vector<vector<SOAROI> >), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEvectorlESOAROIgRsPgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<vector<SOAROI> >) );
      instance.SetNew(&new_vectorlEvectorlESOAROIgRsPgR);
      instance.SetNewArray(&newArray_vectorlEvectorlESOAROIgRsPgR);
      instance.SetDelete(&delete_vectorlEvectorlESOAROIgRsPgR);
      instance.SetDeleteArray(&deleteArray_vectorlEvectorlESOAROIgRsPgR);
      instance.SetDestructor(&destruct_vectorlEvectorlESOAROIgRsPgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<vector<SOAROI> > >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<vector<SOAROI> >","std::vector<std::vector<SOAROI, std::allocator<SOAROI> >, std::allocator<std::vector<SOAROI, std::allocator<SOAROI> > > >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<vector<SOAROI> >*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEvectorlESOAROIgRsPgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<vector<SOAROI> >*>(nullptr))->GetClass();
      vectorlEvectorlESOAROIgRsPgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEvectorlESOAROIgRsPgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEvectorlESOAROIgRsPgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<SOAROI> > : new vector<vector<SOAROI> >;
   }
   static void *newArray_vectorlEvectorlESOAROIgRsPgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<vector<SOAROI> >[nElements] : new vector<vector<SOAROI> >[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEvectorlESOAROIgRsPgR(void *p) {
      delete (static_cast<vector<vector<SOAROI> >*>(p));
   }
   static void deleteArray_vectorlEvectorlESOAROIgRsPgR(void *p) {
      delete [] (static_cast<vector<vector<SOAROI> >*>(p));
   }
   static void destruct_vectorlEvectorlESOAROIgRsPgR(void *p) {
      typedef vector<vector<SOAROI> > current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<vector<SOAROI> >

namespace ROOT {
   static TClass *vectorlEunsignedsPintgR_Dictionary();
   static void vectorlEunsignedsPintgR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPintgR(void *p = nullptr);
   static void *newArray_vectorlEunsignedsPintgR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPintgR(void *p);
   static void deleteArray_vectorlEunsignedsPintgR(void *p);
   static void destruct_vectorlEunsignedsPintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned int>*)
   {
      vector<unsigned int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned int>", -2, "vector", 389,
                  typeid(vector<unsigned int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned int>) );
      instance.SetNew(&new_vectorlEunsignedsPintgR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPintgR);
      instance.SetDelete(&delete_vectorlEunsignedsPintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPintgR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<unsigned int>","std::vector<unsigned int, std::allocator<unsigned int> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<unsigned int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<unsigned int>*>(nullptr))->GetClass();
      vectorlEunsignedsPintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPintgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned int> : new vector<unsigned int>;
   }
   static void *newArray_vectorlEunsignedsPintgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned int>[nElements] : new vector<unsigned int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPintgR(void *p) {
      delete (static_cast<vector<unsigned int>*>(p));
   }
   static void deleteArray_vectorlEunsignedsPintgR(void *p) {
      delete [] (static_cast<vector<unsigned int>*>(p));
   }
   static void destruct_vectorlEunsignedsPintgR(void *p) {
      typedef vector<unsigned int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned int>

namespace ROOT {
   static TClass *vectorlEshortgR_Dictionary();
   static void vectorlEshortgR_TClassManip(TClass*);
   static void *new_vectorlEshortgR(void *p = nullptr);
   static void *newArray_vectorlEshortgR(Long_t size, void *p);
   static void delete_vectorlEshortgR(void *p);
   static void deleteArray_vectorlEshortgR(void *p);
   static void destruct_vectorlEshortgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<short>*)
   {
      vector<short> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<short>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<short>", -2, "vector", 389,
                  typeid(vector<short>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEshortgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<short>) );
      instance.SetNew(&new_vectorlEshortgR);
      instance.SetNewArray(&newArray_vectorlEshortgR);
      instance.SetDelete(&delete_vectorlEshortgR);
      instance.SetDeleteArray(&deleteArray_vectorlEshortgR);
      instance.SetDestructor(&destruct_vectorlEshortgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<short> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<short>","std::vector<short, std::allocator<short> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<short>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEshortgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<short>*>(nullptr))->GetClass();
      vectorlEshortgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEshortgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEshortgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<short> : new vector<short>;
   }
   static void *newArray_vectorlEshortgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<short>[nElements] : new vector<short>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEshortgR(void *p) {
      delete (static_cast<vector<short>*>(p));
   }
   static void deleteArray_vectorlEshortgR(void *p) {
      delete [] (static_cast<vector<short>*>(p));
   }
   static void destruct_vectorlEshortgR(void *p) {
      typedef vector<short> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<short>

namespace ROOT {
   static TClass *vectorlEintgR_Dictionary();
   static void vectorlEintgR_TClassManip(TClass*);
   static void *new_vectorlEintgR(void *p = nullptr);
   static void *newArray_vectorlEintgR(Long_t size, void *p);
   static void delete_vectorlEintgR(void *p);
   static void deleteArray_vectorlEintgR(void *p);
   static void destruct_vectorlEintgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<int>*)
   {
      vector<int> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<int>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<int>", -2, "vector", 389,
                  typeid(vector<int>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEintgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<int>) );
      instance.SetNew(&new_vectorlEintgR);
      instance.SetNewArray(&newArray_vectorlEintgR);
      instance.SetDelete(&delete_vectorlEintgR);
      instance.SetDeleteArray(&deleteArray_vectorlEintgR);
      instance.SetDestructor(&destruct_vectorlEintgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<int> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<int>","std::vector<int, std::allocator<int> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEintgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<int>*>(nullptr))->GetClass();
      vectorlEintgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEintgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEintgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int> : new vector<int>;
   }
   static void *newArray_vectorlEintgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<int>[nElements] : new vector<int>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEintgR(void *p) {
      delete (static_cast<vector<int>*>(p));
   }
   static void deleteArray_vectorlEintgR(void *p) {
      delete [] (static_cast<vector<int>*>(p));
   }
   static void destruct_vectorlEintgR(void *p) {
      typedef vector<int> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<int>

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
   static TClass *vectorlESOAROIgR_Dictionary();
   static void vectorlESOAROIgR_TClassManip(TClass*);
   static void *new_vectorlESOAROIgR(void *p = nullptr);
   static void *newArray_vectorlESOAROIgR(Long_t size, void *p);
   static void delete_vectorlESOAROIgR(void *p);
   static void deleteArray_vectorlESOAROIgR(void *p);
   static void destruct_vectorlESOAROIgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<SOAROI>*)
   {
      vector<SOAROI> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<SOAROI>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<SOAROI>", -2, "vector", 389,
                  typeid(vector<SOAROI>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlESOAROIgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<SOAROI>) );
      instance.SetNew(&new_vectorlESOAROIgR);
      instance.SetNewArray(&newArray_vectorlESOAROIgR);
      instance.SetDelete(&delete_vectorlESOAROIgR);
      instance.SetDeleteArray(&deleteArray_vectorlESOAROIgR);
      instance.SetDestructor(&destruct_vectorlESOAROIgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<SOAROI> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<SOAROI>","std::vector<SOAROI, std::allocator<SOAROI> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<SOAROI>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlESOAROIgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<SOAROI>*>(nullptr))->GetClass();
      vectorlESOAROIgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlESOAROIgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlESOAROIgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<SOAROI> : new vector<SOAROI>;
   }
   static void *newArray_vectorlESOAROIgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<SOAROI>[nElements] : new vector<SOAROI>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlESOAROIgR(void *p) {
      delete (static_cast<vector<SOAROI>*>(p));
   }
   static void deleteArray_vectorlESOAROIgR(void *p) {
      delete [] (static_cast<vector<SOAROI>*>(p));
   }
   static void destruct_vectorlESOAROIgR(void *p) {
      typedef vector<SOAROI> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<SOAROI>

namespace ROOT {
   static TClass *vectorlELong64_tgR_Dictionary();
   static void vectorlELong64_tgR_TClassManip(TClass*);
   static void *new_vectorlELong64_tgR(void *p = nullptr);
   static void *newArray_vectorlELong64_tgR(Long_t size, void *p);
   static void delete_vectorlELong64_tgR(void *p);
   static void deleteArray_vectorlELong64_tgR(void *p);
   static void destruct_vectorlELong64_tgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<Long64_t>*)
   {
      vector<Long64_t> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<Long64_t>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<Long64_t>", -2, "vector", 389,
                  typeid(vector<Long64_t>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlELong64_tgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<Long64_t>) );
      instance.SetNew(&new_vectorlELong64_tgR);
      instance.SetNewArray(&newArray_vectorlELong64_tgR);
      instance.SetDelete(&delete_vectorlELong64_tgR);
      instance.SetDeleteArray(&deleteArray_vectorlELong64_tgR);
      instance.SetDestructor(&destruct_vectorlELong64_tgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<Long64_t> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<Long64_t>","std::vector<long long, std::allocator<long long> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<Long64_t>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlELong64_tgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<Long64_t>*>(nullptr))->GetClass();
      vectorlELong64_tgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlELong64_tgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlELong64_tgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<Long64_t> : new vector<Long64_t>;
   }
   static void *newArray_vectorlELong64_tgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<Long64_t>[nElements] : new vector<Long64_t>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlELong64_tgR(void *p) {
      delete (static_cast<vector<Long64_t>*>(p));
   }
   static void deleteArray_vectorlELong64_tgR(void *p) {
      delete [] (static_cast<vector<Long64_t>*>(p));
   }
   static void destruct_vectorlELong64_tgR(void *p) {
      typedef vector<Long64_t> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<Long64_t>

namespace ROOT {
   // Registration Schema evolution read functions
   int RecordReadRules_SOADict() {
      return 0;
   }
   static int _R__UNIQUE_DICT_(ReadRules_SOADict) = RecordReadRules_SOADict();R__UseDummy(_R__UNIQUE_DICT_(ReadRules_SOADict));
} // namespace ROOT
namespace {
  void TriggerDictionaryInitialization_SOADict_Impl() {
    static const char* headers[] = {
"/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp",
"/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp",
nullptr
    };
    static const char* includePaths[] = {
"/home/smshovan/spack/opt/spack/linux-cascadelake/root-6.36.02-ujt3ksktiwa6az4bc3ekvmzfmi4ydm6d/include/root",
"/home/smshovan/project2/RNTuple-I-O-Config/build/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "SOADict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp")))  SOAHitVector;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp")))  SOAHit;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  SOAROI;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  SOAWire;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  SOAWireBase;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  FlatSOAROI;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  SOAWireVector;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  EventSOA;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "SOADict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp"
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"EventSOA", payloadCode, "@",
"FlatSOAROI", payloadCode, "@",
"SOAHit", payloadCode, "@",
"SOAHitVector", payloadCode, "@",
"SOAROI", payloadCode, "@",
"SOAWire", payloadCode, "@",
"SOAWireBase", payloadCode, "@",
"SOAWireVector", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("SOADict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_SOADict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_SOADict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_SOADict() {
  TriggerDictionaryInitialization_SOADict_Impl();
}
