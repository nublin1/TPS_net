// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "SteamWSRequestUGCDetailsCallbackProxy.h"
#include "AdvancedSteamWorkshopLibrary.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeSteamWSRequestUGCDetailsCallbackProxy() {}

// ********** Begin Cross Module References ********************************************************
ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy();
ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister();
ADVANCEDSTEAMSESSIONS_API UFunction* Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature();
ADVANCEDSTEAMSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopID();
ADVANCEDSTEAMSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UOnlineBlueprintCallProxyBase();
UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FBlueprintWorkshopDetailsDelegate *************************************
struct Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics
{
	struct _Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms
	{
		FBPSteamWorkshopItemDetails WorkShopDetails;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_WorkShopDetails_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorkShopDetails;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::NewProp_WorkShopDetails = { "WorkShopDetails", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms, WorkShopDetails), Z_Construct_UScriptStruct_FBPSteamWorkshopItemDetails, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_WorkShopDetails_MetaData), NewProp_WorkShopDetails_MetaData) }; // 1827740272
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::NewProp_WorkShopDetails,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_AdvancedSteamSessions, nullptr, "BlueprintWorkshopDetailsDelegate__DelegateSignature", Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::_Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::_Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FBlueprintWorkshopDetailsDelegate_DelegateWrapper(const FMulticastScriptDelegate& BlueprintWorkshopDetailsDelegate, FBPSteamWorkshopItemDetails const& WorkShopDetails)
{
	struct _Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms
	{
		FBPSteamWorkshopItemDetails WorkShopDetails;
	};
	_Script_AdvancedSteamSessions_eventBlueprintWorkshopDetailsDelegate_Parms Parms;
	Parms.WorkShopDetails=WorkShopDetails;
	BlueprintWorkshopDetailsDelegate.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FBlueprintWorkshopDetailsDelegate ***************************************

// ********** Begin Class USteamWSRequestUGCDetailsCallbackProxy Function GetWorkshopItemDetails ***
struct Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics
{
	struct SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms
	{
		UObject* WorldContextObject;
		FBPSteamWorkshopID WorkShopID;
		USteamWSRequestUGCDetailsCallbackProxy* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Online|AdvancedSteamWorkshop" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Ends the current session\n" },
#endif
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Ends the current session" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_WorkShopID;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorkShopID = { "WorkShopID", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms, WorkShopID), Z_Construct_UScriptStruct_FBPSteamWorkshopID, METADATA_PARAMS(0, nullptr) }; // 301282290
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms, ReturnValue), Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_WorkShopID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy, nullptr, "GetWorkshopItemDetails", Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::PropPointers), sizeof(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::Function_MetaDataParams), Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::SteamWSRequestUGCDetailsCallbackProxy_eventGetWorkshopItemDetails_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(USteamWSRequestUGCDetailsCallbackProxy::execGetWorkshopItemDetails)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_STRUCT(FBPSteamWorkshopID,Z_Param_WorkShopID);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(USteamWSRequestUGCDetailsCallbackProxy**)Z_Param__Result=USteamWSRequestUGCDetailsCallbackProxy::GetWorkshopItemDetails(Z_Param_WorldContextObject,Z_Param_WorkShopID);
	P_NATIVE_END;
}
// ********** End Class USteamWSRequestUGCDetailsCallbackProxy Function GetWorkshopItemDetails *****

// ********** Begin Class USteamWSRequestUGCDetailsCallbackProxy ***********************************
void USteamWSRequestUGCDetailsCallbackProxy::StaticRegisterNativesUSteamWSRequestUGCDetailsCallbackProxy()
{
	UClass* Class = USteamWSRequestUGCDetailsCallbackProxy::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetWorkshopItemDetails", &USteamWSRequestUGCDetailsCallbackProxy::execGetWorkshopItemDetails },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy;
UClass* USteamWSRequestUGCDetailsCallbackProxy::GetPrivateStaticClass()
{
	using TClass = USteamWSRequestUGCDetailsCallbackProxy;
	if (!Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("SteamWSRequestUGCDetailsCallbackProxy"),
			Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy.InnerSingleton,
			StaticRegisterNativesUSteamWSRequestUGCDetailsCallbackProxy,
			sizeof(TClass),
			alignof(TClass),
			TClass::StaticClassFlags,
			TClass::StaticClassCastFlags(),
			TClass::StaticConfigName(),
			(UClass::ClassConstructorType)InternalConstructor<TClass>,
			(UClass::ClassVTableHelperCtorCallerType)InternalVTableHelperCtorCaller<TClass>,
			UOBJECT_CPPCLASS_STATICFUNCTIONS_FORCLASS(TClass),
			&TClass::Super::StaticClass,
			&TClass::WithinClass::StaticClass
		);
	}
	return Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy.InnerSingleton;
}
UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_NoRegister()
{
	return USteamWSRequestUGCDetailsCallbackProxy::GetPrivateStaticClass();
}
struct Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "SteamWSRequestUGCDetailsCallbackProxy.h" },
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSuccess_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called when there is a successful results return\n" },
#endif
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when there is a successful results return" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnFailure_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called when there is an unsuccessful results return\n" },
#endif
		{ "ModuleRelativePath", "Classes/SteamWSRequestUGCDetailsCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when there is an unsuccessful results return" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSuccess;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnFailure;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_USteamWSRequestUGCDetailsCallbackProxy_GetWorkshopItemDetails, "GetWorkshopItemDetails" }, // 3526692281
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<USteamWSRequestUGCDetailsCallbackProxy>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnSuccess = { "OnSuccess", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USteamWSRequestUGCDetailsCallbackProxy, OnSuccess), Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSuccess_MetaData), NewProp_OnSuccess_MetaData) }; // 530699292
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnFailure = { "OnFailure", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(USteamWSRequestUGCDetailsCallbackProxy, OnFailure), Z_Construct_UDelegateFunction_AdvancedSteamSessions_BlueprintWorkshopDetailsDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnFailure_MetaData), NewProp_OnFailure_MetaData) }; // 530699292
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::NewProp_OnFailure,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UOnlineBlueprintCallProxyBase,
	(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::ClassParams = {
	&USteamWSRequestUGCDetailsCallbackProxy::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::PropPointers),
	0,
	0x008800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::Class_MetaDataParams), Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy()
{
	if (!Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy.OuterSingleton, Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(USteamWSRequestUGCDetailsCallbackProxy);
USteamWSRequestUGCDetailsCallbackProxy::~USteamWSRequestUGCDetailsCallbackProxy() {}
// ********** End Class USteamWSRequestUGCDetailsCallbackProxy *************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamWSRequestUGCDetailsCallbackProxy_h__Script_AdvancedSteamSessions_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_USteamWSRequestUGCDetailsCallbackProxy, USteamWSRequestUGCDetailsCallbackProxy::StaticClass, TEXT("USteamWSRequestUGCDetailsCallbackProxy"), &Z_Registration_Info_UClass_USteamWSRequestUGCDetailsCallbackProxy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(USteamWSRequestUGCDetailsCallbackProxy), 1320433637U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamWSRequestUGCDetailsCallbackProxy_h__Script_AdvancedSteamSessions_3611567158(TEXT("/Script/AdvancedSteamSessions"),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamWSRequestUGCDetailsCallbackProxy_h__Script_AdvancedSteamSessions_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_SteamWSRequestUGCDetailsCallbackProxy_h__Script_AdvancedSteamSessions_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
