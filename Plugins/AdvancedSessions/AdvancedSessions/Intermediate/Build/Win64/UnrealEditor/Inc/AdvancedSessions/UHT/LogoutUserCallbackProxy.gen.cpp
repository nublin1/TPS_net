// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "LogoutUserCallbackProxy.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeLogoutUserCallbackProxy() {}

// ********** Begin Cross Module References ********************************************************
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_ULogoutUserCallbackProxy();
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_ULogoutUserCallbackProxy_NoRegister();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_APlayerController_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UOnlineBlueprintCallProxyBase();
ENGINE_API UFunction* Z_Construct_UDelegateFunction_Engine_EmptyOnlineDelegate__DelegateSignature();
UPackage* Z_Construct_UPackage__Script_AdvancedSessions();
// ********** End Cross Module References **********************************************************

// ********** Begin Class ULogoutUserCallbackProxy Function LogoutUser *****************************
struct Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics
{
	struct LogoutUserCallbackProxy_eventLogoutUser_Parms
	{
		UObject* WorldContextObject;
		APlayerController* PlayerController;
		ULogoutUserCallbackProxy* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "BlueprintInternalUseOnly", "true" },
		{ "Category", "Online|AdvancedIdentity" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Logs out of the identity interface\n" },
#endif
		{ "ModuleRelativePath", "Classes/LogoutUserCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Logs out of the identity interface" },
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
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LogoutUserCallbackProxy_eventLogoutUser_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::NewProp_PlayerController = { "PlayerController", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LogoutUserCallbackProxy_eventLogoutUser_Parms, PlayerController), Z_Construct_UClass_APlayerController_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(LogoutUserCallbackProxy_eventLogoutUser_Parms, ReturnValue), Z_Construct_UClass_ULogoutUserCallbackProxy_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::NewProp_PlayerController,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_ULogoutUserCallbackProxy, nullptr, "LogoutUser", Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::PropPointers), sizeof(Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::LogoutUserCallbackProxy_eventLogoutUser_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::Function_MetaDataParams), Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::LogoutUserCallbackProxy_eventLogoutUser_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(ULogoutUserCallbackProxy::execLogoutUser)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_OBJECT(APlayerController,Z_Param_PlayerController);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(ULogoutUserCallbackProxy**)Z_Param__Result=ULogoutUserCallbackProxy::LogoutUser(Z_Param_WorldContextObject,Z_Param_PlayerController);
	P_NATIVE_END;
}
// ********** End Class ULogoutUserCallbackProxy Function LogoutUser *******************************

// ********** Begin Class ULogoutUserCallbackProxy *************************************************
void ULogoutUserCallbackProxy::StaticRegisterNativesULogoutUserCallbackProxy()
{
	UClass* Class = ULogoutUserCallbackProxy::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "LogoutUser", &ULogoutUserCallbackProxy::execLogoutUser },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_ULogoutUserCallbackProxy;
UClass* ULogoutUserCallbackProxy::GetPrivateStaticClass()
{
	using TClass = ULogoutUserCallbackProxy;
	if (!Z_Registration_Info_UClass_ULogoutUserCallbackProxy.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("LogoutUserCallbackProxy"),
			Z_Registration_Info_UClass_ULogoutUserCallbackProxy.InnerSingleton,
			StaticRegisterNativesULogoutUserCallbackProxy,
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
	return Z_Registration_Info_UClass_ULogoutUserCallbackProxy.InnerSingleton;
}
UClass* Z_Construct_UClass_ULogoutUserCallbackProxy_NoRegister()
{
	return ULogoutUserCallbackProxy::GetPrivateStaticClass();
}
struct Z_Construct_UClass_ULogoutUserCallbackProxy_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "LogoutUserCallbackProxy.h" },
		{ "ModuleRelativePath", "Classes/LogoutUserCallbackProxy.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnSuccess_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called when there is a successful destroy\n" },
#endif
		{ "ModuleRelativePath", "Classes/LogoutUserCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when there is a successful destroy" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_OnFailure_MetaData[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Called when there is an unsuccessful destroy\n" },
#endif
		{ "ModuleRelativePath", "Classes/LogoutUserCallbackProxy.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Called when there is an unsuccessful destroy" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnSuccess;
	static const UECodeGen_Private::FMulticastDelegatePropertyParams NewProp_OnFailure;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_ULogoutUserCallbackProxy_LogoutUser, "LogoutUser" }, // 3592623946
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<ULogoutUserCallbackProxy>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::NewProp_OnSuccess = { "OnSuccess", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULogoutUserCallbackProxy, OnSuccess), Z_Construct_UDelegateFunction_Engine_EmptyOnlineDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnSuccess_MetaData), NewProp_OnSuccess_MetaData) }; // 1205031399
const UECodeGen_Private::FMulticastDelegatePropertyParams Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::NewProp_OnFailure = { "OnFailure", nullptr, (EPropertyFlags)0x0010000010080000, UECodeGen_Private::EPropertyGenFlags::InlineMulticastDelegate, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(ULogoutUserCallbackProxy, OnFailure), Z_Construct_UDelegateFunction_Engine_EmptyOnlineDelegate__DelegateSignature, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_OnFailure_MetaData), NewProp_OnFailure_MetaData) }; // 1205031399
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::NewProp_OnSuccess,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::NewProp_OnFailure,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UOnlineBlueprintCallProxyBase,
	(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSessions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::ClassParams = {
	&ULogoutUserCallbackProxy::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	UE_ARRAY_COUNT(Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::PropPointers),
	0,
	0x008800A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::Class_MetaDataParams), Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_ULogoutUserCallbackProxy()
{
	if (!Z_Registration_Info_UClass_ULogoutUserCallbackProxy.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_ULogoutUserCallbackProxy.OuterSingleton, Z_Construct_UClass_ULogoutUserCallbackProxy_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_ULogoutUserCallbackProxy.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(ULogoutUserCallbackProxy);
ULogoutUserCallbackProxy::~ULogoutUserCallbackProxy() {}
// ********** End Class ULogoutUserCallbackProxy ***************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LogoutUserCallbackProxy_h__Script_AdvancedSessions_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_ULogoutUserCallbackProxy, ULogoutUserCallbackProxy::StaticClass, TEXT("ULogoutUserCallbackProxy"), &Z_Registration_Info_UClass_ULogoutUserCallbackProxy, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(ULogoutUserCallbackProxy), 263300513U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LogoutUserCallbackProxy_h__Script_AdvancedSessions_3183277230(TEXT("/Script/AdvancedSessions"),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LogoutUserCallbackProxy_h__Script_AdvancedSessions_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LogoutUserCallbackProxy_h__Script_AdvancedSessions_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
