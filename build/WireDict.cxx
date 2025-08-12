// Do NOT change. Changes will be lost next time file is generated

#define R__DICTIONARY_FILENAME dIhomedIsmshovandIproject2dIRNTuplemIImIOmIConfigdIbuilddIWireDict
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
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp"
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp"

// Header files passed via #pragma extra_include

// The generated code does not explicitly qualify STL entities
namespace std {} using namespace std;

namespace ROOT {
   static void *new_HitVector(void *p = nullptr);
   static void *newArray_HitVector(Long_t size, void *p);
   static void delete_HitVector(void *p);
   static void deleteArray_HitVector(void *p);
   static void destruct_HitVector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HitVector*)
   {
      ::HitVector *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HitVector >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("HitVector", ::HitVector::Class_Version(), "", 12,
                  typeid(::HitVector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HitVector::Dictionary, isa_proxy, 4,
                  sizeof(::HitVector) );
      instance.SetNew(&new_HitVector);
      instance.SetNewArray(&newArray_HitVector);
      instance.SetDelete(&delete_HitVector);
      instance.SetDeleteArray(&deleteArray_HitVector);
      instance.SetDestructor(&destruct_HitVector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HitVector*)
   {
      return GenerateInitInstanceLocal(static_cast<::HitVector*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::HitVector*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_HitIndividual(void *p = nullptr);
   static void *newArray_HitIndividual(Long_t size, void *p);
   static void delete_HitIndividual(void *p);
   static void deleteArray_HitIndividual(void *p);
   static void destruct_HitIndividual(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::HitIndividual*)
   {
      ::HitIndividual *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::HitIndividual >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("HitIndividual", ::HitIndividual::Class_Version(), "", 94,
                  typeid(::HitIndividual), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::HitIndividual::Dictionary, isa_proxy, 4,
                  sizeof(::HitIndividual) );
      instance.SetNew(&new_HitIndividual);
      instance.SetNewArray(&newArray_HitIndividual);
      instance.SetDelete(&delete_HitIndividual);
      instance.SetDeleteArray(&deleteArray_HitIndividual);
      instance.SetDestructor(&destruct_HitIndividual);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::HitIndividual*)
   {
      return GenerateInitInstanceLocal(static_cast<::HitIndividual*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::HitIndividual*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WireVector(void *p = nullptr);
   static void *newArray_WireVector(Long_t size, void *p);
   static void delete_WireVector(void *p);
   static void deleteArray_WireVector(void *p);
   static void destruct_WireVector(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WireVector*)
   {
      ::WireVector *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WireVector >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("WireVector", ::WireVector::Class_Version(), "", 16,
                  typeid(::WireVector), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WireVector::Dictionary, isa_proxy, 4,
                  sizeof(::WireVector) );
      instance.SetNew(&new_WireVector);
      instance.SetNewArray(&newArray_WireVector);
      instance.SetDelete(&delete_WireVector);
      instance.SetDeleteArray(&deleteArray_WireVector);
      instance.SetDestructor(&destruct_WireVector);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WireVector*)
   {
      return GenerateInitInstanceLocal(static_cast<::WireVector*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::WireVector*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_RegionOfInterest(void *p = nullptr);
   static void *newArray_RegionOfInterest(Long_t size, void *p);
   static void delete_RegionOfInterest(void *p);
   static void deleteArray_RegionOfInterest(void *p);
   static void destruct_RegionOfInterest(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::RegionOfInterest*)
   {
      ::RegionOfInterest *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::RegionOfInterest >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("RegionOfInterest", ::RegionOfInterest::Class_Version(), "", 51,
                  typeid(::RegionOfInterest), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::RegionOfInterest::Dictionary, isa_proxy, 4,
                  sizeof(::RegionOfInterest) );
      instance.SetNew(&new_RegionOfInterest);
      instance.SetNewArray(&newArray_RegionOfInterest);
      instance.SetDelete(&delete_RegionOfInterest);
      instance.SetDeleteArray(&deleteArray_RegionOfInterest);
      instance.SetDestructor(&destruct_RegionOfInterest);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::RegionOfInterest*)
   {
      return GenerateInitInstanceLocal(static_cast<::RegionOfInterest*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::RegionOfInterest*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

namespace ROOT {
   static void *new_WireIndividual(void *p = nullptr);
   static void *newArray_WireIndividual(Long_t size, void *p);
   static void delete_WireIndividual(void *p);
   static void deleteArray_WireIndividual(void *p);
   static void destruct_WireIndividual(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const ::WireIndividual*)
   {
      ::WireIndividual *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TInstrumentedIsAProxy< ::WireIndividual >(nullptr);
      static ::ROOT::TGenericClassInfo 
         instance("WireIndividual", ::WireIndividual::Class_Version(), "", 67,
                  typeid(::WireIndividual), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &::WireIndividual::Dictionary, isa_proxy, 4,
                  sizeof(::WireIndividual) );
      instance.SetNew(&new_WireIndividual);
      instance.SetNewArray(&newArray_WireIndividual);
      instance.SetDelete(&delete_WireIndividual);
      instance.SetDeleteArray(&deleteArray_WireIndividual);
      instance.SetDestructor(&destruct_WireIndividual);
      return &instance;
   }
   TGenericClassInfo *GenerateInitInstance(const ::WireIndividual*)
   {
      return GenerateInitInstanceLocal(static_cast<::WireIndividual*>(nullptr));
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const ::WireIndividual*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));
} // end of namespace ROOT

//______________________________________________________________________________
atomic_TClass_ptr HitVector::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *HitVector::Class_Name()
{
   return "HitVector";
}

//______________________________________________________________________________
const char *HitVector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HitVector*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int HitVector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HitVector*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HitVector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HitVector*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HitVector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HitVector*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr HitIndividual::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *HitIndividual::Class_Name()
{
   return "HitIndividual";
}

//______________________________________________________________________________
const char *HitIndividual::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HitIndividual*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int HitIndividual::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::HitIndividual*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *HitIndividual::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HitIndividual*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *HitIndividual::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::HitIndividual*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WireVector::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *WireVector::Class_Name()
{
   return "WireVector";
}

//______________________________________________________________________________
const char *WireVector::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireVector*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int WireVector::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireVector*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WireVector::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireVector*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WireVector::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireVector*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr RegionOfInterest::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *RegionOfInterest::Class_Name()
{
   return "RegionOfInterest";
}

//______________________________________________________________________________
const char *RegionOfInterest::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RegionOfInterest*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int RegionOfInterest::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::RegionOfInterest*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *RegionOfInterest::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RegionOfInterest*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *RegionOfInterest::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::RegionOfInterest*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
atomic_TClass_ptr WireIndividual::fgIsA(nullptr);  // static to hold class pointer

//______________________________________________________________________________
const char *WireIndividual::Class_Name()
{
   return "WireIndividual";
}

//______________________________________________________________________________
const char *WireIndividual::ImplFileName()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireIndividual*)nullptr)->GetImplFileName();
}

//______________________________________________________________________________
int WireIndividual::ImplFileLine()
{
   return ::ROOT::GenerateInitInstanceLocal((const ::WireIndividual*)nullptr)->GetImplFileLine();
}

//______________________________________________________________________________
TClass *WireIndividual::Dictionary()
{
   fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireIndividual*)nullptr)->GetClass();
   return fgIsA;
}

//______________________________________________________________________________
TClass *WireIndividual::Class()
{
   if (!fgIsA.load()) { R__LOCKGUARD(gInterpreterMutex); fgIsA = ::ROOT::GenerateInitInstanceLocal((const ::WireIndividual*)nullptr)->GetClass(); }
   return fgIsA;
}

//______________________________________________________________________________
void HitVector::Streamer(TBuffer &R__b)
{
   // Stream an object of class HitVector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HitVector::Class(),this);
   } else {
      R__b.WriteClassBuffer(HitVector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HitVector(void *p) {
      return  p ? new(p) ::HitVector : new ::HitVector;
   }
   static void *newArray_HitVector(Long_t nElements, void *p) {
      return p ? new(p) ::HitVector[nElements] : new ::HitVector[nElements];
   }
   // Wrapper around operator delete
   static void delete_HitVector(void *p) {
      delete (static_cast<::HitVector*>(p));
   }
   static void deleteArray_HitVector(void *p) {
      delete [] (static_cast<::HitVector*>(p));
   }
   static void destruct_HitVector(void *p) {
      typedef ::HitVector current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::HitVector

//______________________________________________________________________________
void HitIndividual::Streamer(TBuffer &R__b)
{
   // Stream an object of class HitIndividual.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(HitIndividual::Class(),this);
   } else {
      R__b.WriteClassBuffer(HitIndividual::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_HitIndividual(void *p) {
      return  p ? new(p) ::HitIndividual : new ::HitIndividual;
   }
   static void *newArray_HitIndividual(Long_t nElements, void *p) {
      return p ? new(p) ::HitIndividual[nElements] : new ::HitIndividual[nElements];
   }
   // Wrapper around operator delete
   static void delete_HitIndividual(void *p) {
      delete (static_cast<::HitIndividual*>(p));
   }
   static void deleteArray_HitIndividual(void *p) {
      delete [] (static_cast<::HitIndividual*>(p));
   }
   static void destruct_HitIndividual(void *p) {
      typedef ::HitIndividual current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::HitIndividual

//______________________________________________________________________________
void WireVector::Streamer(TBuffer &R__b)
{
   // Stream an object of class WireVector.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WireVector::Class(),this);
   } else {
      R__b.WriteClassBuffer(WireVector::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WireVector(void *p) {
      return  p ? new(p) ::WireVector : new ::WireVector;
   }
   static void *newArray_WireVector(Long_t nElements, void *p) {
      return p ? new(p) ::WireVector[nElements] : new ::WireVector[nElements];
   }
   // Wrapper around operator delete
   static void delete_WireVector(void *p) {
      delete (static_cast<::WireVector*>(p));
   }
   static void deleteArray_WireVector(void *p) {
      delete [] (static_cast<::WireVector*>(p));
   }
   static void destruct_WireVector(void *p) {
      typedef ::WireVector current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::WireVector

//______________________________________________________________________________
void RegionOfInterest::Streamer(TBuffer &R__b)
{
   // Stream an object of class RegionOfInterest.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(RegionOfInterest::Class(),this);
   } else {
      R__b.WriteClassBuffer(RegionOfInterest::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_RegionOfInterest(void *p) {
      return  p ? new(p) ::RegionOfInterest : new ::RegionOfInterest;
   }
   static void *newArray_RegionOfInterest(Long_t nElements, void *p) {
      return p ? new(p) ::RegionOfInterest[nElements] : new ::RegionOfInterest[nElements];
   }
   // Wrapper around operator delete
   static void delete_RegionOfInterest(void *p) {
      delete (static_cast<::RegionOfInterest*>(p));
   }
   static void deleteArray_RegionOfInterest(void *p) {
      delete [] (static_cast<::RegionOfInterest*>(p));
   }
   static void destruct_RegionOfInterest(void *p) {
      typedef ::RegionOfInterest current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::RegionOfInterest

//______________________________________________________________________________
void WireIndividual::Streamer(TBuffer &R__b)
{
   // Stream an object of class WireIndividual.

   if (R__b.IsReading()) {
      R__b.ReadClassBuffer(WireIndividual::Class(),this);
   } else {
      R__b.WriteClassBuffer(WireIndividual::Class(),this);
   }
}

namespace ROOT {
   // Wrappers around operator new
   static void *new_WireIndividual(void *p) {
      return  p ? new(p) ::WireIndividual : new ::WireIndividual;
   }
   static void *newArray_WireIndividual(Long_t nElements, void *p) {
      return p ? new(p) ::WireIndividual[nElements] : new ::WireIndividual[nElements];
   }
   // Wrapper around operator delete
   static void delete_WireIndividual(void *p) {
      delete (static_cast<::WireIndividual*>(p));
   }
   static void deleteArray_WireIndividual(void *p) {
      delete [] (static_cast<::WireIndividual*>(p));
   }
   static void destruct_WireIndividual(void *p) {
      typedef ::WireIndividual current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class ::WireIndividual

namespace ROOT {
   static TClass *vectorlEunsignedsPlonggR_Dictionary();
   static void vectorlEunsignedsPlonggR_TClassManip(TClass*);
   static void *new_vectorlEunsignedsPlonggR(void *p = nullptr);
   static void *newArray_vectorlEunsignedsPlonggR(Long_t size, void *p);
   static void delete_vectorlEunsignedsPlonggR(void *p);
   static void deleteArray_vectorlEunsignedsPlonggR(void *p);
   static void destruct_vectorlEunsignedsPlonggR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<unsigned long>*)
   {
      vector<unsigned long> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<unsigned long>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<unsigned long>", -2, "vector", 389,
                  typeid(vector<unsigned long>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlEunsignedsPlonggR_Dictionary, isa_proxy, 0,
                  sizeof(vector<unsigned long>) );
      instance.SetNew(&new_vectorlEunsignedsPlonggR);
      instance.SetNewArray(&newArray_vectorlEunsignedsPlonggR);
      instance.SetDelete(&delete_vectorlEunsignedsPlonggR);
      instance.SetDeleteArray(&deleteArray_vectorlEunsignedsPlonggR);
      instance.SetDestructor(&destruct_vectorlEunsignedsPlonggR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<unsigned long> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<unsigned long>","std::vector<unsigned long, std::allocator<unsigned long> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<unsigned long>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlEunsignedsPlonggR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<unsigned long>*>(nullptr))->GetClass();
      vectorlEunsignedsPlonggR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlEunsignedsPlonggR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlEunsignedsPlonggR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned long> : new vector<unsigned long>;
   }
   static void *newArray_vectorlEunsignedsPlonggR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<unsigned long>[nElements] : new vector<unsigned long>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlEunsignedsPlonggR(void *p) {
      delete (static_cast<vector<unsigned long>*>(p));
   }
   static void deleteArray_vectorlEunsignedsPlonggR(void *p) {
      delete [] (static_cast<vector<unsigned long>*>(p));
   }
   static void destruct_vectorlEunsignedsPlonggR(void *p) {
      typedef vector<unsigned long> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<unsigned long>

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
                  &vectorlEWireIndividualgR_Dictionary, isa_proxy, 4,
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
   static TClass *vectorlERegionOfInterestgR_Dictionary();
   static void vectorlERegionOfInterestgR_TClassManip(TClass*);
   static void *new_vectorlERegionOfInterestgR(void *p = nullptr);
   static void *newArray_vectorlERegionOfInterestgR(Long_t size, void *p);
   static void delete_vectorlERegionOfInterestgR(void *p);
   static void deleteArray_vectorlERegionOfInterestgR(void *p);
   static void destruct_vectorlERegionOfInterestgR(void *p);

   // Function generating the singleton type initializer
   static TGenericClassInfo *GenerateInitInstanceLocal(const vector<RegionOfInterest>*)
   {
      vector<RegionOfInterest> *ptr = nullptr;
      static ::TVirtualIsAProxy* isa_proxy = new ::TIsAProxy(typeid(vector<RegionOfInterest>));
      static ::ROOT::TGenericClassInfo 
         instance("vector<RegionOfInterest>", -2, "vector", 389,
                  typeid(vector<RegionOfInterest>), ::ROOT::Internal::DefineBehavior(ptr, ptr),
                  &vectorlERegionOfInterestgR_Dictionary, isa_proxy, 0,
                  sizeof(vector<RegionOfInterest>) );
      instance.SetNew(&new_vectorlERegionOfInterestgR);
      instance.SetNewArray(&newArray_vectorlERegionOfInterestgR);
      instance.SetDelete(&delete_vectorlERegionOfInterestgR);
      instance.SetDeleteArray(&deleteArray_vectorlERegionOfInterestgR);
      instance.SetDestructor(&destruct_vectorlERegionOfInterestgR);
      instance.AdoptCollectionProxyInfo(TCollectionProxyInfo::Generate(TCollectionProxyInfo::Pushback< vector<RegionOfInterest> >()));

      instance.AdoptAlternate(::ROOT::AddClassAlternate("vector<RegionOfInterest>","std::vector<RegionOfInterest, std::allocator<RegionOfInterest> >"));
      return &instance;
   }
   // Static variable to force the class initialization
   static ::ROOT::TGenericClassInfo *_R__UNIQUE_DICT_(Init) = GenerateInitInstanceLocal(static_cast<const vector<RegionOfInterest>*>(nullptr)); R__UseDummy(_R__UNIQUE_DICT_(Init));

   // Dictionary for non-ClassDef classes
   static TClass *vectorlERegionOfInterestgR_Dictionary() {
      TClass* theClass =::ROOT::GenerateInitInstanceLocal(static_cast<const vector<RegionOfInterest>*>(nullptr))->GetClass();
      vectorlERegionOfInterestgR_TClassManip(theClass);
   return theClass;
   }

   static void vectorlERegionOfInterestgR_TClassManip(TClass* ){
   }

} // end of namespace ROOT

namespace ROOT {
   // Wrappers around operator new
   static void *new_vectorlERegionOfInterestgR(void *p) {
      return  p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RegionOfInterest> : new vector<RegionOfInterest>;
   }
   static void *newArray_vectorlERegionOfInterestgR(Long_t nElements, void *p) {
      return p ? ::new(static_cast<::ROOT::Internal::TOperatorNewHelper*>(p)) vector<RegionOfInterest>[nElements] : new vector<RegionOfInterest>[nElements];
   }
   // Wrapper around operator delete
   static void delete_vectorlERegionOfInterestgR(void *p) {
      delete (static_cast<vector<RegionOfInterest>*>(p));
   }
   static void deleteArray_vectorlERegionOfInterestgR(void *p) {
      delete [] (static_cast<vector<RegionOfInterest>*>(p));
   }
   static void destruct_vectorlERegionOfInterestgR(void *p) {
      typedef vector<RegionOfInterest> current_t;
      (static_cast<current_t*>(p))->~current_t();
   }
} // end of namespace ROOT for class vector<RegionOfInterest>

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
                  &vectorlEHitIndividualgR_Dictionary, isa_proxy, 4,
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
   int RecordReadRules_WireDict() {
      return 0;
   }
   static int _R__UNIQUE_DICT_(ReadRules_WireDict) = RecordReadRules_WireDict();R__UseDummy(_R__UNIQUE_DICT_(ReadRules_WireDict));
} // namespace ROOT
namespace {
  void TriggerDictionaryInitialization_WireDict_Impl() {
    static const char* headers[] = {
"/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp",
"/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp",
nullptr
    };
    static const char* includePaths[] = {
"/home/smshovan/spack/opt/spack/linux-cascadelake/root-6.36.02-ujt3ksktiwa6az4bc3ekvmzfmi4ydm6d/include/root",
"/home/smshovan/project2/RNTuple-I-O-Config/build/",
nullptr
    };
    static const char* fwdDeclCode = R"DICTFWDDCLS(
#line 1 "WireDict dictionary forward declarations' payload"
#pragma clang diagnostic ignored "-Wkeyword-compat"
#pragma clang diagnostic ignored "-Wignored-attributes"
#pragma clang diagnostic ignored "-Wreturn-type-c-linkage"
extern int __Cling_AutoLoading_Map;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  WireIndividual;
namespace std{template <typename _Tp> class __attribute__((annotate("$clingAutoload$bits/allocator.h")))  __attribute__((annotate("$clingAutoload$string")))  allocator;
}
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  HitIndividual;
class __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  HitVector;
class __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  WireVector;
struct __attribute__((annotate("$clingAutoload$/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp")))  RegionOfInterest;
)DICTFWDDCLS";
    static const char* payloadCode = R"DICTPAYLOAD(
#line 1 "WireDict dictionary payload"


#define _BACKWARD_BACKWARD_WARNING_H
// Inline headers
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Wire.hpp"
#include "/home/smshovan/project2/RNTuple-I-O-Config/include/Hit.hpp"

#undef  _BACKWARD_BACKWARD_WARNING_H
)DICTPAYLOAD";
    static const char* classesHeaders[] = {
"HitIndividual", payloadCode, "@",
"HitVector", payloadCode, "@",
"RegionOfInterest", payloadCode, "@",
"WireIndividual", payloadCode, "@",
"WireVector", payloadCode, "@",
nullptr
};
    static bool isInitialized = false;
    if (!isInitialized) {
      TROOT::RegisterModule("WireDict",
        headers, includePaths, payloadCode, fwdDeclCode,
        TriggerDictionaryInitialization_WireDict_Impl, {}, classesHeaders, /*hasCxxModule*/false);
      isInitialized = true;
    }
  }
  static struct DictInit {
    DictInit() {
      TriggerDictionaryInitialization_WireDict_Impl();
    }
  } __TheDictionaryInitializer;
}
void TriggerDictionaryInitialization_WireDict() {
  TriggerDictionaryInitialization_WireDict_Impl();
}
