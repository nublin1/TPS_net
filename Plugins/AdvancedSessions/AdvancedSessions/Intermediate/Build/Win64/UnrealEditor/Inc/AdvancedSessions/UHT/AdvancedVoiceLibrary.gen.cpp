// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedVoiceLibrary.h"
#include "BlueprintDataDefinitions.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAdvancedVoiceLibrary() {}

// ********** Begin Cross Module References ********************************************************
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_UAdvancedVoiceLibrary();
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_UAdvancedVoiceLibrary_NoRegister();
ADVANCEDSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPUniqueNetId();
COREUOBJECT_API UClass* Z_Construct_UClass_UObject_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
UPackage* Z_Construct_UPackage__Script_AdvancedSessions();
// ********** End Cross Module References **********************************************************

// ********** Begin Class UAdvancedVoiceLibrary Function GetNumLocalTalkers ************************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics
{
	struct AdvancedVoiceLibrary_eventGetNumLocalTalkers_Parms
	{
		UObject* WorldContextObject;
		int32 NumLocalTalkers;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice|VoiceInfo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Gets the number of local talkers for this system\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gets the number of local talkers for this system" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FIntPropertyParams NewProp_NumLocalTalkers;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventGetNumLocalTalkers_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::NewProp_NumLocalTalkers = { "NumLocalTalkers", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventGetNumLocalTalkers_Parms, NumLocalTalkers), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::NewProp_NumLocalTalkers,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "GetNumLocalTalkers", Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::AdvancedVoiceLibrary_eventGetNumLocalTalkers_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::AdvancedVoiceLibrary_eventGetNumLocalTalkers_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execGetNumLocalTalkers)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_NumLocalTalkers);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::GetNumLocalTalkers(Z_Param_WorldContextObject,Z_Param_Out_NumLocalTalkers);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function GetNumLocalTalkers **************************

// ********** Begin Class UAdvancedVoiceLibrary Function IsHeadsetPresent **************************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics
{
	struct AdvancedVoiceLibrary_eventIsHeadsetPresent_Parms
	{
		UObject* WorldContextObject;
		bool bHasHeadset;
		uint8 LocalPlayerNum;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice|VoiceInfo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Get if a headset is present for the specified local user\n" },
#endif
		{ "CPP_Default_LocalPlayerNum", "0" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get if a headset is present for the specified local user" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static void NewProp_bHasHeadset_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bHasHeadset;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalPlayerNum;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsHeadsetPresent_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_bHasHeadset_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventIsHeadsetPresent_Parms*)Obj)->bHasHeadset = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_bHasHeadset = { "bHasHeadset", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventIsHeadsetPresent_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_bHasHeadset_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_LocalPlayerNum = { "LocalPlayerNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsHeadsetPresent_Parms, LocalPlayerNum), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_bHasHeadset,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::NewProp_LocalPlayerNum,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "IsHeadsetPresent", Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::AdvancedVoiceLibrary_eventIsHeadsetPresent_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::AdvancedVoiceLibrary_eventIsHeadsetPresent_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execIsHeadsetPresent)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_UBOOL_REF(Z_Param_Out_bHasHeadset);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalPlayerNum);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::IsHeadsetPresent(Z_Param_WorldContextObject,Z_Param_Out_bHasHeadset,Z_Param_LocalPlayerNum);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function IsHeadsetPresent ****************************

// ********** Begin Class UAdvancedVoiceLibrary Function IsLocalPlayerTalking **********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics
{
	struct AdvancedVoiceLibrary_eventIsLocalPlayerTalking_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalPlayerNum;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice|VoiceInfo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Returns whether a local player is currently talking\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns whether a local player is currently talking" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalPlayerNum;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsLocalPlayerTalking_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_LocalPlayerNum = { "LocalPlayerNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsLocalPlayerTalking_Parms, LocalPlayerNum), nullptr, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventIsLocalPlayerTalking_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventIsLocalPlayerTalking_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_LocalPlayerNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "IsLocalPlayerTalking", Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::AdvancedVoiceLibrary_eventIsLocalPlayerTalking_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::AdvancedVoiceLibrary_eventIsLocalPlayerTalking_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execIsLocalPlayerTalking)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalPlayerNum);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsLocalPlayerTalking(Z_Param_WorldContextObject,Z_Param_LocalPlayerNum);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function IsLocalPlayerTalking ************************

// ********** Begin Class UAdvancedVoiceLibrary Function IsPlayerMuted *****************************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics
{
	struct AdvancedVoiceLibrary_eventIsPlayerMuted_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalUserNumChecking;
		FBPUniqueNetId UniqueNetId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice|VoiceInfo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Returns whether a player is muted for the specified local player\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns whether a player is muted for the specified local player" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalUserNumChecking;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsPlayerMuted_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_LocalUserNumChecking = { "LocalUserNumChecking", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsPlayerMuted_Parms, LocalUserNumChecking), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsPlayerMuted_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
void Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventIsPlayerMuted_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventIsPlayerMuted_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_LocalUserNumChecking,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "IsPlayerMuted", Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::AdvancedVoiceLibrary_eventIsPlayerMuted_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::AdvancedVoiceLibrary_eventIsPlayerMuted_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execIsPlayerMuted)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalUserNumChecking);
	P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsPlayerMuted(Z_Param_WorldContextObject,Z_Param_LocalUserNumChecking,Z_Param_Out_UniqueNetId);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function IsPlayerMuted *******************************

// ********** Begin Class UAdvancedVoiceLibrary Function IsRemotePlayerTalking *********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics
{
	struct AdvancedVoiceLibrary_eventIsRemotePlayerTalking_Parms
	{
		UObject* WorldContextObject;
		FBPUniqueNetId UniqueNetId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice|VoiceInfo" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Returns whether a remote player is currently talking\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns whether a remote player is currently talking" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsRemotePlayerTalking_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventIsRemotePlayerTalking_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
void Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventIsRemotePlayerTalking_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventIsRemotePlayerTalking_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "IsRemotePlayerTalking", Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::AdvancedVoiceLibrary_eventIsRemotePlayerTalking_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::AdvancedVoiceLibrary_eventIsRemotePlayerTalking_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execIsRemotePlayerTalking)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::IsRemotePlayerTalking(Z_Param_WorldContextObject,Z_Param_Out_UniqueNetId);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function IsRemotePlayerTalking ***********************

// ********** Begin Class UAdvancedVoiceLibrary Function MuteRemoteTalker **************************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics
{
	struct AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalUserNum;
		FBPUniqueNetId UniqueNetId;
		bool bIsSystemWide;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Mutes the player associated with the uniquenetid for the specified local player, if IsSystemWide is true then it will attempt to mute globally for the player\n" },
#endif
		{ "CPP_Default_bIsSystemWide", "false" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Mutes the player associated with the uniquenetid for the specified local player, if IsSystemWide is true then it will attempt to mute globally for the player" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalUserNum;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static void NewProp_bIsSystemWide_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsSystemWide;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_LocalUserNum = { "LocalUserNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms, LocalUserNum), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
void Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_bIsSystemWide_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms*)Obj)->bIsSystemWide = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_bIsSystemWide = { "bIsSystemWide", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_bIsSystemWide_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_LocalUserNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_bIsSystemWide,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "MuteRemoteTalker", Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::AdvancedVoiceLibrary_eventMuteRemoteTalker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execMuteRemoteTalker)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalUserNum);
	P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId);
	P_GET_UBOOL(Z_Param_bIsSystemWide);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::MuteRemoteTalker(Z_Param_WorldContextObject,Z_Param_LocalUserNum,Z_Param_Out_UniqueNetId,Z_Param_bIsSystemWide);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function MuteRemoteTalker ****************************

// ********** Begin Class UAdvancedVoiceLibrary Function RegisterAllLocalTalkers *******************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics
{
	struct AdvancedVoiceLibrary_eventRegisterAllLocalTalkers_Parms
	{
		UObject* WorldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Registers all signed in players as local talkers\n// This is already done automatically, only do it manually if you unregistered someone\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Registers all signed in players as local talkers\nThis is already done automatically, only do it manually if you unregistered someone" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventRegisterAllLocalTalkers_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::NewProp_WorldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "RegisterAllLocalTalkers", Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::AdvancedVoiceLibrary_eventRegisterAllLocalTalkers_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::AdvancedVoiceLibrary_eventRegisterAllLocalTalkers_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execRegisterAllLocalTalkers)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::RegisterAllLocalTalkers(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function RegisterAllLocalTalkers *********************

// ********** Begin Class UAdvancedVoiceLibrary Function RegisterLocalTalker ***********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics
{
	struct AdvancedVoiceLibrary_eventRegisterLocalTalker_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalPlayerNum;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Registers a local player as someone interested in voice data\n" },
#endif
		{ "CPP_Default_LocalPlayerNum", "0" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Registers a local player as someone interested in voice data" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalPlayerNum;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventRegisterLocalTalker_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_LocalPlayerNum = { "LocalPlayerNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventRegisterLocalTalker_Parms, LocalPlayerNum), nullptr, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventRegisterLocalTalker_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventRegisterLocalTalker_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_LocalPlayerNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "RegisterLocalTalker", Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::AdvancedVoiceLibrary_eventRegisterLocalTalker_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::AdvancedVoiceLibrary_eventRegisterLocalTalker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execRegisterLocalTalker)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalPlayerNum);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::RegisterLocalTalker(Z_Param_WorldContextObject,Z_Param_LocalPlayerNum);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function RegisterLocalTalker *************************

// ********** Begin Class UAdvancedVoiceLibrary Function RegisterRemoteTalker **********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics
{
	struct AdvancedVoiceLibrary_eventRegisterRemoteTalker_Parms
	{
		UObject* WorldContextObject;
		FBPUniqueNetId UniqueNetId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Registers a remote player as a talker\n// This is already done automatically, only do it manually if you unregistered someone\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Registers a remote player as a talker\nThis is already done automatically, only do it manually if you unregistered someone" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventRegisterRemoteTalker_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventRegisterRemoteTalker_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
void Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventRegisterRemoteTalker_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventRegisterRemoteTalker_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "RegisterRemoteTalker", Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::AdvancedVoiceLibrary_eventRegisterRemoteTalker_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::AdvancedVoiceLibrary_eventRegisterRemoteTalker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execRegisterRemoteTalker)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::RegisterRemoteTalker(Z_Param_WorldContextObject,Z_Param_Out_UniqueNetId);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function RegisterRemoteTalker ************************

// ********** Begin Class UAdvancedVoiceLibrary Function RemoveAllRemoteTalkers ********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics
{
	struct AdvancedVoiceLibrary_eventRemoveAllRemoteTalkers_Parms
	{
		UObject* WorldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// UnRegisters all remote players as talkers\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UnRegisters all remote players as talkers" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventRemoveAllRemoteTalkers_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::NewProp_WorldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "RemoveAllRemoteTalkers", Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::AdvancedVoiceLibrary_eventRemoveAllRemoteTalkers_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::AdvancedVoiceLibrary_eventRemoveAllRemoteTalkers_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execRemoveAllRemoteTalkers)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::RemoveAllRemoteTalkers(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function RemoveAllRemoteTalkers **********************

// ********** Begin Class UAdvancedVoiceLibrary Function StartNetworkedVoice ***********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics
{
	struct AdvancedVoiceLibrary_eventStartNetworkedVoice_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalPlayerNum;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Starts networked voice, allows push to talk in coordination with StopNetworkedVoice\n" },
#endif
		{ "CPP_Default_LocalPlayerNum", "0" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Starts networked voice, allows push to talk in coordination with StopNetworkedVoice" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalPlayerNum;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventStartNetworkedVoice_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::NewProp_LocalPlayerNum = { "LocalPlayerNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventStartNetworkedVoice_Parms, LocalPlayerNum), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::NewProp_LocalPlayerNum,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "StartNetworkedVoice", Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::AdvancedVoiceLibrary_eventStartNetworkedVoice_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::AdvancedVoiceLibrary_eventStartNetworkedVoice_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execStartNetworkedVoice)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalPlayerNum);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::StartNetworkedVoice(Z_Param_WorldContextObject,Z_Param_LocalPlayerNum);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function StartNetworkedVoice *************************

// ********** Begin Class UAdvancedVoiceLibrary Function StopNetworkedVoice ************************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics
{
	struct AdvancedVoiceLibrary_eventStopNetworkedVoice_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalPlayerNum;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Stops networked voice, allows push to talk in coordination with StartNetworkedVoice\n" },
#endif
		{ "CPP_Default_LocalPlayerNum", "0" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Stops networked voice, allows push to talk in coordination with StartNetworkedVoice" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalPlayerNum;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventStopNetworkedVoice_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::NewProp_LocalPlayerNum = { "LocalPlayerNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventStopNetworkedVoice_Parms, LocalPlayerNum), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::NewProp_LocalPlayerNum,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "StopNetworkedVoice", Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::AdvancedVoiceLibrary_eventStopNetworkedVoice_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::AdvancedVoiceLibrary_eventStopNetworkedVoice_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execStopNetworkedVoice)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalPlayerNum);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::StopNetworkedVoice(Z_Param_WorldContextObject,Z_Param_LocalPlayerNum);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function StopNetworkedVoice **************************

// ********** Begin Class UAdvancedVoiceLibrary Function UnMuteRemoteTalker ************************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics
{
	struct AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalUserNum;
		FBPUniqueNetId UniqueNetId;
		bool bIsSystemWide;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// UnMutes the player associated with the uniquenetid for the specified local player, if IsSystemWide is true then it will attempt to unmute globally for the player\n" },
#endif
		{ "CPP_Default_bIsSystemWide", "false" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UnMutes the player associated with the uniquenetid for the specified local player, if IsSystemWide is true then it will attempt to unmute globally for the player" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalUserNum;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static void NewProp_bIsSystemWide_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bIsSystemWide;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_LocalUserNum = { "LocalUserNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms, LocalUserNum), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
void Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_bIsSystemWide_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms*)Obj)->bIsSystemWide = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_bIsSystemWide = { "bIsSystemWide", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_bIsSystemWide_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_LocalUserNum,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_bIsSystemWide,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "UnMuteRemoteTalker", Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::AdvancedVoiceLibrary_eventUnMuteRemoteTalker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execUnMuteRemoteTalker)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalUserNum);
	P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId);
	P_GET_UBOOL(Z_Param_bIsSystemWide);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::UnMuteRemoteTalker(Z_Param_WorldContextObject,Z_Param_LocalUserNum,Z_Param_Out_UniqueNetId,Z_Param_bIsSystemWide);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function UnMuteRemoteTalker **************************

// ********** Begin Class UAdvancedVoiceLibrary Function UnRegisterAllLocalTalkers *****************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics
{
	struct AdvancedVoiceLibrary_eventUnRegisterAllLocalTalkers_Parms
	{
		UObject* WorldContextObject;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// UnRegisters all signed in players as local talkers\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UnRegisters all signed in players as local talkers" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnRegisterAllLocalTalkers_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::NewProp_WorldContextObject,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "UnRegisterAllLocalTalkers", Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::AdvancedVoiceLibrary_eventUnRegisterAllLocalTalkers_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::AdvancedVoiceLibrary_eventUnRegisterAllLocalTalkers_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execUnRegisterAllLocalTalkers)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::UnRegisterAllLocalTalkers(Z_Param_WorldContextObject);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function UnRegisterAllLocalTalkers *******************

// ********** Begin Class UAdvancedVoiceLibrary Function UnRegisterLocalTalker *********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics
{
	struct AdvancedVoiceLibrary_eventUnRegisterLocalTalker_Parms
	{
		UObject* WorldContextObject;
		uint8 LocalPlayerNum;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// UnRegisters local player as a local talker\n" },
#endif
		{ "CPP_Default_LocalPlayerNum", "0" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UnRegisters local player as a local talker" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FBytePropertyParams NewProp_LocalPlayerNum;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnRegisterLocalTalker_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::NewProp_LocalPlayerNum = { "LocalPlayerNum", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnRegisterLocalTalker_Parms, LocalPlayerNum), nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::NewProp_LocalPlayerNum,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "UnRegisterLocalTalker", Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::AdvancedVoiceLibrary_eventUnRegisterLocalTalker_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::AdvancedVoiceLibrary_eventUnRegisterLocalTalker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execUnRegisterLocalTalker)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_PROPERTY(FByteProperty,Z_Param_LocalPlayerNum);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedVoiceLibrary::UnRegisterLocalTalker(Z_Param_WorldContextObject,Z_Param_LocalPlayerNum);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function UnRegisterLocalTalker ***********************

// ********** Begin Class UAdvancedVoiceLibrary Function UnRegisterRemoteTalker ********************
struct Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics
{
	struct AdvancedVoiceLibrary_eventUnRegisterRemoteTalker_Parms
	{
		UObject* WorldContextObject;
		FBPUniqueNetId UniqueNetId;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedVoice" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// UnRegisters a remote player as a talker\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "UnRegisters a remote player as a talker" },
#endif
		{ "WorldContext", "WorldContextObject" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FObjectPropertyParams NewProp_WorldContextObject;
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_WorldContextObject = { "WorldContextObject", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnRegisterRemoteTalker_Parms, WorldContextObject), Z_Construct_UClass_UObject_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000008000182, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedVoiceLibrary_eventUnRegisterRemoteTalker_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
void Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedVoiceLibrary_eventUnRegisterRemoteTalker_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedVoiceLibrary_eventUnRegisterRemoteTalker_Parms), &Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_WorldContextObject,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedVoiceLibrary, nullptr, "UnRegisterRemoteTalker", Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::AdvancedVoiceLibrary_eventUnRegisterRemoteTalker_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::AdvancedVoiceLibrary_eventUnRegisterRemoteTalker_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedVoiceLibrary::execUnRegisterRemoteTalker)
{
	P_GET_OBJECT(UObject,Z_Param_WorldContextObject);
	P_GET_STRUCT_REF(FBPUniqueNetId,Z_Param_Out_UniqueNetId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedVoiceLibrary::UnRegisterRemoteTalker(Z_Param_WorldContextObject,Z_Param_Out_UniqueNetId);
	P_NATIVE_END;
}
// ********** End Class UAdvancedVoiceLibrary Function UnRegisterRemoteTalker **********************

// ********** Begin Class UAdvancedVoiceLibrary ****************************************************
void UAdvancedVoiceLibrary::StaticRegisterNativesUAdvancedVoiceLibrary()
{
	UClass* Class = UAdvancedVoiceLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "GetNumLocalTalkers", &UAdvancedVoiceLibrary::execGetNumLocalTalkers },
		{ "IsHeadsetPresent", &UAdvancedVoiceLibrary::execIsHeadsetPresent },
		{ "IsLocalPlayerTalking", &UAdvancedVoiceLibrary::execIsLocalPlayerTalking },
		{ "IsPlayerMuted", &UAdvancedVoiceLibrary::execIsPlayerMuted },
		{ "IsRemotePlayerTalking", &UAdvancedVoiceLibrary::execIsRemotePlayerTalking },
		{ "MuteRemoteTalker", &UAdvancedVoiceLibrary::execMuteRemoteTalker },
		{ "RegisterAllLocalTalkers", &UAdvancedVoiceLibrary::execRegisterAllLocalTalkers },
		{ "RegisterLocalTalker", &UAdvancedVoiceLibrary::execRegisterLocalTalker },
		{ "RegisterRemoteTalker", &UAdvancedVoiceLibrary::execRegisterRemoteTalker },
		{ "RemoveAllRemoteTalkers", &UAdvancedVoiceLibrary::execRemoveAllRemoteTalkers },
		{ "StartNetworkedVoice", &UAdvancedVoiceLibrary::execStartNetworkedVoice },
		{ "StopNetworkedVoice", &UAdvancedVoiceLibrary::execStopNetworkedVoice },
		{ "UnMuteRemoteTalker", &UAdvancedVoiceLibrary::execUnMuteRemoteTalker },
		{ "UnRegisterAllLocalTalkers", &UAdvancedVoiceLibrary::execUnRegisterAllLocalTalkers },
		{ "UnRegisterLocalTalker", &UAdvancedVoiceLibrary::execUnRegisterLocalTalker },
		{ "UnRegisterRemoteTalker", &UAdvancedVoiceLibrary::execUnRegisterRemoteTalker },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAdvancedVoiceLibrary;
UClass* UAdvancedVoiceLibrary::GetPrivateStaticClass()
{
	using TClass = UAdvancedVoiceLibrary;
	if (!Z_Registration_Info_UClass_UAdvancedVoiceLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AdvancedVoiceLibrary"),
			Z_Registration_Info_UClass_UAdvancedVoiceLibrary.InnerSingleton,
			StaticRegisterNativesUAdvancedVoiceLibrary,
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
	return Z_Registration_Info_UClass_UAdvancedVoiceLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UAdvancedVoiceLibrary_NoRegister()
{
	return UAdvancedVoiceLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAdvancedVoiceLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "AdvancedVoiceLibrary.h" },
		{ "ModuleRelativePath", "Classes/AdvancedVoiceLibrary.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_GetNumLocalTalkers, "GetNumLocalTalkers" }, // 431207453
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsHeadsetPresent, "IsHeadsetPresent" }, // 4250188585
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsLocalPlayerTalking, "IsLocalPlayerTalking" }, // 2379087559
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsPlayerMuted, "IsPlayerMuted" }, // 3253779980
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_IsRemotePlayerTalking, "IsRemotePlayerTalking" }, // 3474762154
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_MuteRemoteTalker, "MuteRemoteTalker" }, // 1219453057
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterAllLocalTalkers, "RegisterAllLocalTalkers" }, // 2460940668
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterLocalTalker, "RegisterLocalTalker" }, // 1581102306
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_RegisterRemoteTalker, "RegisterRemoteTalker" }, // 2953707772
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_RemoveAllRemoteTalkers, "RemoveAllRemoteTalkers" }, // 3508891379
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_StartNetworkedVoice, "StartNetworkedVoice" }, // 793174332
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_StopNetworkedVoice, "StopNetworkedVoice" }, // 1014093703
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_UnMuteRemoteTalker, "UnMuteRemoteTalker" }, // 922505082
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterAllLocalTalkers, "UnRegisterAllLocalTalkers" }, // 3579568098
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterLocalTalker, "UnRegisterLocalTalker" }, // 1289061431
		{ &Z_Construct_UFunction_UAdvancedVoiceLibrary_UnRegisterRemoteTalker, "UnRegisterRemoteTalker" }, // 1664338008
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAdvancedVoiceLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAdvancedVoiceLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSessions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAdvancedVoiceLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAdvancedVoiceLibrary_Statics::ClassParams = {
	&UAdvancedVoiceLibrary::StaticClass,
	nullptr,
	&StaticCppClassTypeInfo,
	DependentSingletons,
	FuncInfo,
	nullptr,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	UE_ARRAY_COUNT(FuncInfo),
	0,
	0,
	0x000000A0u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAdvancedVoiceLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UAdvancedVoiceLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAdvancedVoiceLibrary()
{
	if (!Z_Registration_Info_UClass_UAdvancedVoiceLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAdvancedVoiceLibrary.OuterSingleton, Z_Construct_UClass_UAdvancedVoiceLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAdvancedVoiceLibrary.OuterSingleton;
}
UAdvancedVoiceLibrary::UAdvancedVoiceLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAdvancedVoiceLibrary);
UAdvancedVoiceLibrary::~UAdvancedVoiceLibrary() {}
// ********** End Class UAdvancedVoiceLibrary ******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h__Script_AdvancedSessions_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAdvancedVoiceLibrary, UAdvancedVoiceLibrary::StaticClass, TEXT("UAdvancedVoiceLibrary"), &Z_Registration_Info_UClass_UAdvancedVoiceLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAdvancedVoiceLibrary), 1181613832U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h__Script_AdvancedSessions_384114617(TEXT("/Script/AdvancedSessions"),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h__Script_AdvancedSessions_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h__Script_AdvancedSessions_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
