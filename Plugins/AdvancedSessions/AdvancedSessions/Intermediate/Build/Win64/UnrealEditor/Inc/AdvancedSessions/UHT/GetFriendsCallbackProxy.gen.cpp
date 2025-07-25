// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "GetFriendsCallbackProxy.h"
#include "BlueprintDataDefinitions.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeGetFriendsCallbackProxy() {}

// ********** Begin Cross Module References ********************************************************
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_UGetFriendsCallbackProxy();
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_UGetFriendsCallbackProxy_NoRegister();
ADVANCEDSESSIONS_API UFunction* Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature();
ADVANCEDSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPFriendInfo();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerController_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UOnlineBlueprintCallProxyBase();
UPackage* Z_Construct_UPackage__Script_AdvancedSessions();
// ********** End Cross Module References **********************************************************

// ********** Begin Delegate FBlueprintGetFriendsListDelegate **************************************
struct Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics
{
	struct _Script_AdvancedSessions_eventBlueprintGetFriendsListDelegate_Parms
	{
		TArray<FBPFriendInfo> Results;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "ModuleRelativePath", "Classes/GetFriendsCallbackProxy.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_Results_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_Results_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_Results;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FDelegateFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::NewProp_Results_Inner = { "Results", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBPFriendInfo, METADATA_PARAMS(0, nullptr) }; // 1295210154
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::NewProp_Results = { "Results", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(_Script_AdvancedSessions_eventBlueprintGetFriendsListDelegate_Parms, Results), EArrayPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_Results_MetaData), NewProp_Results_MetaData) }; // 1295210154
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::NewProp_Results_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::NewProp_Results,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::PropPointers) < 2048);
const UECodeGen_Private::FDelegateFunctionParams Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UPackage__Script_AdvancedSessions, nullptr, "BlueprintGetFriendsListDelegate__DelegateSignature", Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::PropPointers), sizeof(Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::_Script_AdvancedSessions_eventBlueprintGetFriendsListDelegate_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x00530000, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::Function_MetaDataParams), Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::_Script_AdvancedSessions_eventBlueprintGetFriendsListDelegate_Parms) < MAX_uint16);
UFunction* Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUDelegateFunction(&ReturnFunction, Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature_Statics::FuncParams);
	}
	return ReturnFunction;
}
void FBlueprintGetFriendsListDelegate_DelegateWrapper(const FMulticastScriptDelegate& BlueprintGetFriendsListDelegate, TArray<FBPFriendInfo> const& Results)
{
	struct _Script_AdvancedSessions_eventBlueprintGetFriendsListDelegate_Parms
	{
		TArray<FBPFriendInfo> Results;
	};
	_Script_AdvancedSessions_eventBlueprintGetFriendsListDelegate_Parms Parms;
	Parms.Results=Results;
	BlueprintGetFriendsListDelegate.ProcessMulticastDelegate<UObject>(&Parms);
}
// ********** End Delegate FBlueprintGetFriendsListDelegate ****************************************

// ********** Begin Class UGetFriendsCallbackProxy Function GetAndStoreFriendsList *****************
struct Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics
{
	struct GetFriendsCallbackProxy_eventGetAndStoreFriendsList_Parms
	{
		UObject* WorldContextObject;
		APlayerController* PlayerController;
		UGetFriendsCallbackProxy* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Online|AdvancedFriends" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Gets the players list of friends from the OnlineSubsystem and returns it, can be retrieved later with GetStoredFriendsList\n" },
#endif
		{ "ModuleRelativePath", "Classes/GetFriendsCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gets the players list of friends from the OnlineSubsystem and returns it, can be retrieved later with GetStoredFriendsList" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_PlayerController;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GetFriendsCallbackProxy_eventGetAndStoreFriendsList_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::NewProp_PlayerController = { "PlayerController", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GetFriendsCallbackProxy_eventGetAndStoreFriendsList_Parms, PlayerController), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(GetFriendsCallbackProxy_eventGetAndStoreFriendsList_Parms, ReturnValue), Z_Construct_UClass_UGetFriendsCallbackProxy_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::NewProp_PlayerController,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UGetFriendsCallbackProxy, nullptr, "GetAndStoreFriendsList", Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::PropPointers), sizeof(Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::GetFriendsCallbackProxy_eventGetAndStoreFriendsList_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::Function_MetaDataParams), Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::GetFriendsCallbackProxy_eventGetAndStoreFriendsList_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UGetFriendsCallbackProxy::execGetAndStoreFriendsList)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_OBJECT(APlayerController,Z_Param_PlayerController);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UGetFriendsCallbackProxy**)Z_Param__Result=UGetFriendsCallbackProxy::GetAndStoreFriendsList(Z_Param_WorldContextObject,Z_Param_PlayerController);
	P_NATIVE_END;
}
// ********** End Class UGetFriendsCallbackProxy Function GetAndStoreFriendsList *******************

// ********** Begin Class UGetFriendsCallbackProxy *************************************************
void UGetFriendsCallbackProxy::StaticRegisterNativesUGetFriendsCallbackProxy()
{
	UClass* Class = UGetFriendsCallbackProxy::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetAndStoreFriendsList", &UGetFriendsCallbackProxy::execGetAndStoreFriendsList },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UGetFriendsCallbackProxy;
UClass* UGetFriendsCallbackProxy::GetPrivateStaticClass()
{
	using TClass = UGetFriendsCallbackProxy;
	if (!Z_Registration_Info_UClass_UGetFriendsCallbackProxy.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("GetFriendsCallbackProxy"),
			Z_Registration_Info_UClass_UGetFriendsCallbackProxy.InnerSingleton,
			StaticRegisterNativesUGetFriendsCallbackProxy,
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
	return Z_Registration_Info_UClass_UGetFriendsCallbackProxy.InnerSingleton;
}
UClass* Z_Construct_UClass_UGetFriendsCallbackProxy_NoRegister()
{
	return UGetFriendsCallbackProxy::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UGetFriendsCallbackProxy_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "GetFriendsCallbackProxy.h" },
		{ "ModuleRelativePath", "Classes/GetFriendsCallbackProxy.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSuccess_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called when the friends list successfully was retrieved\n" },
#endif
		{ "ModuleRelativePath", "Classes/GetFriendsCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when the friends list successfully was retrieved" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnFailure_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called when there was an error retrieving the friends list\n" },
#endif
		{ "ModuleRelativePath", "Classes/GetFriendsCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when there was an error retrieving the friends list" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSuccess;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnFailure;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UGetFriendsCallbackProxy_GetAndStoreFriendsList, "GetAndStoreFriendsList" }, // 3726919758
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UGetFriendsCallbackProxy>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::NewProp_OnSuccess = { "OnSuccess", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGetFriendsCallbackProxy, OnSuccess), Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSuccess_MetaData), NewProp_OnSuccess_MetaData) }; // 3078213012
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::NewProp_OnFailure = { "OnFailure", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(UGetFriendsCallbackProxy, OnFailure), Z_Construct_UDelegateFunction_AdvancedSessions_BlueprintGetFriendsListDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnFailure_MetaData), NewProp_OnFailure_MetaData) }; // 3078213012
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::NewProp_OnSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::NewProp_OnFailure,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UOnlineBlueprintCallProxyBase,
	(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSessions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::ClassParams = {
	&UGetFriendsCallbackProxy::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::PropPointers),
	0,
	0x008800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::Class_MetaDataParams), Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UGetFriendsCallbackProxy()
{
	if (!Z_Registration_Info_UClass_UGetFriendsCallbackProxy.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UGetFriendsCallbackProxy.OuterSingleton, Z_Construct_UClass_UGetFriendsCallbackProxy_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UGetFriendsCallbackProxy.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(UGetFriendsCallbackProxy);
UGetFriendsCallbackProxy::~UGetFriendsCallbackProxy() {}
// ********** End Class UGetFriendsCallbackProxy ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_GetFriendsCallbackProxy_h__Script_AdvancedSessions_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UGetFriendsCallbackProxy, UGetFriendsCallbackProxy::StaticClass, TEXT("UGetFriendsCallbackProxy"), &Z_Registration_Info_UClass_UGetFriendsCallbackProxy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UGetFriendsCallbackProxy), 2275713614U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_GetFriendsCallbackProxy_h__Script_AdvancedSessions_882649665(TEXT("/Script/AdvancedSessions"),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_GetFriendsCallbackProxy_h__Script_AdvancedSessions_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_GetFriendsCallbackProxy_h__Script_AdvancedSessions_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
