// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedGameSession.h"
#include "GameFramework/OnlineReplStructs.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAdvancedGameSession() {}

// ********** Begin Cross Module References ********************************************************
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_AAdvancedGameSession();
ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_AAdvancedGameSession_NoRegister();
ENGINE_API UClass* Z_Construct_UClass_AGameSession();
ENGINE_API UScriptStruct* Z_Construct_UScriptStruct_FUniqueNetIdRepl();
UPackage* Z_Construct_UPackage__Script_AdvancedSessions();
// ********** End Cross Module References **********************************************************

// ********** Begin Class AAdvancedGameSession *****************************************************
void AAdvancedGameSession::StaticRegisterNativesAAdvancedGameSession()
{
}
FClassRegistrationInfo Z_Registration_Info_UClass_AAdvancedGameSession;
UClass* AAdvancedGameSession::GetPrivateStaticClass()
{
	using TClass = AAdvancedGameSession;
	if (!Z_Registration_Info_UClass_AAdvancedGameSession.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AdvancedGameSession"),
			Z_Registration_Info_UClass_AAdvancedGameSession.InnerSingleton,
			StaticRegisterNativesAAdvancedGameSession,
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
	return Z_Registration_Info_UClass_AAdvancedGameSession.InnerSingleton;
}
UClass* Z_Construct_UClass_AAdvancedGameSession_NoRegister()
{
	return AAdvancedGameSession::GetPrivateStaticClass();
}
struct Z_Construct_UClass_AAdvancedGameSession_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
#if !UE_BUILD_SHIPPING
		{ "Comment", "/**\n A quick wrapper around the game session to add a partial ban implementation. Just bans for the duration of the current session\n*/" },
#endif
		{ "HideCategories", "Input Movement Collision Rendering HLOD WorldPartition DataLayers Transformation" },
		{ "IncludePath", "AdvancedGameSession.h" },
		{ "ModuleRelativePath", "Classes/AdvancedGameSession.h" },
		{ "ShowCategories", "Input|MouseInput Input|TouchInput" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "A quick wrapper around the game session to add a partial ban implementation. Just bans for the duration of the current session" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_BanList_MetaData[] = {
		{ "ModuleRelativePath", "Classes/AdvancedGameSession.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FTextPropertyParams NewProp_BanList_ValueProp;
	static const UECodeGen_Private::FStructPropertyParams NewProp_BanList_Key_KeyProp;
	static const UECodeGen_Private::FMapPropertyParams NewProp_BanList;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static UObject* (*const DependentSingletons[])();
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<AAdvancedGameSession>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
const UECodeGen_Private::FTextPropertyParams Z_Construct_UClass_AAdvancedGameSession_Statics::NewProp_BanList_ValueProp = { "BanList", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Text, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 1, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UClass_AAdvancedGameSession_Statics::NewProp_BanList_Key_KeyProp = { "BanList_Key", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FUniqueNetIdRepl, METADATA_PARAMS(0, nullptr) }; // 774471623
const UECodeGen_Private::FMapPropertyParams Z_Construct_UClass_AAdvancedGameSession_Statics::NewProp_BanList = { "BanList", nullptr, (EPropertyFlags)0x0010000000002000, UECodeGen_Private::EPropertyGenFlags::Map, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AAdvancedGameSession, BanList), EMapPropertyFlags::None, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_BanList_MetaData), NewProp_BanList_MetaData) }; // 774471623
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UClass_AAdvancedGameSession_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAdvancedGameSession_Statics::NewProp_BanList_ValueProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAdvancedGameSession_Statics::NewProp_BanList_Key_KeyProp,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UClass_AAdvancedGameSession_Statics::NewProp_BanList,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAdvancedGameSession_Statics::PropPointers) < 2048);
UObject* (*const Z_Construct_UClass_AAdvancedGameSession_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_AGameSession,
	(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSessions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_AAdvancedGameSession_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_AAdvancedGameSession_Statics::ClassParams = {
	&AAdvancedGameSession::StaticClass,
	"Game",
	&StaticCppClassTypeInfo,
	DependentSingletons,
	nullptr,
	Z_Construct_UClass_AAdvancedGameSession_Statics::PropPointers,
	nullptr,
	UE_ARRAY_COUNT(DependentSingletons),
	0,
	UE_ARRAY_COUNT(Z_Construct_UClass_AAdvancedGameSession_Statics::PropPointers),
	0,
	0x008003A4u,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_AAdvancedGameSession_Statics::Class_MetaDataParams), Z_Construct_UClass_AAdvancedGameSession_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_AAdvancedGameSession()
{
	if (!Z_Registration_Info_UClass_AAdvancedGameSession.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_AAdvancedGameSession.OuterSingleton, Z_Construct_UClass_AAdvancedGameSession_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_AAdvancedGameSession.OuterSingleton;
}
DEFINE_VTABLE_PTR_HELPER_CTOR(AAdvancedGameSession);
AAdvancedGameSession::~AAdvancedGameSession() {}
// ********** End Class AAdvancedGameSession *******************************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedGameSession_h__Script_AdvancedSessions_Statics
{
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_AAdvancedGameSession, AAdvancedGameSession::StaticClass, TEXT("AAdvancedGameSession"), &Z_Registration_Info_UClass_AAdvancedGameSession, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(AAdvancedGameSession), 2861355461U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedGameSession_h__Script_AdvancedSessions_4276057329(TEXT("/Script/AdvancedSessions"),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedGameSession_h__Script_AdvancedSessions_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedGameSession_h__Script_AdvancedSessions_Statics::ClassInfo),
	nullptr, 0,
	nullptr, 0);
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
