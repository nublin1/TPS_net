// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

#include "UObject/GeneratedCppIncludes.h"
#include "AdvancedSteamFriendsLibrary.h"
#include "BlueprintDataDefinitions.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

void EmptyLinkFunctionForGeneratedCodeAdvancedSteamFriendsLibrary() {}

// ********** Begin Cross Module References ********************************************************
ADVANCEDSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSessions_EBlueprintAsyncResultSwitch();
ADVANCEDSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSessions_EBlueprintResultSwitch();
ADVANCEDSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPUniqueNetId();
ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary();
ADVANCEDSTEAMSESSIONS_API UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary_NoRegister();
ADVANCEDSTEAMSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext();
ADVANCEDSTEAMSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType();
ADVANCEDSTEAMSESSIONS_API UEnum* Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize();
ADVANCEDSTEAMSESSIONS_API UScriptStruct* Z_Construct_UScriptStruct_FBPSteamGroupInfo();
ENGINE_API UClass* Z_Construct_UClass_UBlueprintFunctionLibrary();
ENGINE_API UClass* Z_Construct_UClass_UTexture2D_NoRegister();
UPackage* Z_Construct_UPackage__Script_AdvancedSteamSessions();
// ********** End Cross Module References **********************************************************

// ********** Begin Enum SteamAvatarSize ***********************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_SteamAvatarSize;
static UEnum* SteamAvatarSize_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_SteamAvatarSize.OuterSingleton)
	{
		Z_Registration_Info_UEnum_SteamAvatarSize.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize, (UObject*)Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("SteamAvatarSize"));
	}
	return Z_Registration_Info_UEnum_SteamAvatarSize.OuterSingleton;
}
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<SteamAvatarSize>()
{
	return SteamAvatarSize_StaticEnum();
}
struct Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "SteamAvatar_INVALID.Name", "SteamAvatarSize::SteamAvatar_INVALID" },
		{ "SteamAvatar_Large.Name", "SteamAvatarSize::SteamAvatar_Large" },
		{ "SteamAvatar_Medium.Name", "SteamAvatarSize::SteamAvatar_Medium" },
		{ "SteamAvatar_Small.Name", "SteamAvatarSize::SteamAvatar_Small" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "SteamAvatarSize::SteamAvatar_INVALID", (int64)SteamAvatarSize::SteamAvatar_INVALID },
		{ "SteamAvatarSize::SteamAvatar_Small", (int64)SteamAvatarSize::SteamAvatar_Small },
		{ "SteamAvatarSize::SteamAvatar_Medium", (int64)SteamAvatarSize::SteamAvatar_Medium },
		{ "SteamAvatarSize::SteamAvatar_Large", (int64)SteamAvatarSize::SteamAvatar_Large },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
	nullptr,
	"SteamAvatarSize",
	"SteamAvatarSize",
	Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize()
{
	if (!Z_Registration_Info_UEnum_SteamAvatarSize.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_SteamAvatarSize.InnerSingleton, Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_SteamAvatarSize.InnerSingleton;
}
// ********** End Enum SteamAvatarSize *************************************************************

// ********** Begin Enum ESteamUserOverlayType *****************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_ESteamUserOverlayType;
static UEnum* ESteamUserOverlayType_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_ESteamUserOverlayType.OuterSingleton)
	{
		Z_Registration_Info_UEnum_ESteamUserOverlayType.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType, (UObject*)Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("ESteamUserOverlayType"));
	}
	return Z_Registration_Info_UEnum_ESteamUserOverlayType.OuterSingleton;
}
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<ESteamUserOverlayType>()
{
	return ESteamUserOverlayType_StaticEnum();
}
struct Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "achievements.Comment", "/*Opens the overlay web browser to the specified user's achievements.*/" },
		{ "achievements.Name", "ESteamUserOverlayType::achievements" },
		{ "achievements.ToolTip", "Opens the overlay web browser to the specified user's achievements." },
		{ "BlueprintType", "true" },
		{ "chat.Comment", "/*Opens a chat window to the specified user, or joins the group chat.*/" },
		{ "chat.Name", "ESteamUserOverlayType::chat" },
		{ "chat.ToolTip", "Opens a chat window to the specified user, or joins the group chat." },
		{ "friendadd.Comment", "/*Opens the overlay in minimal mode prompting the user to add the target user as a friend.*/" },
		{ "friendadd.Name", "ESteamUserOverlayType::friendadd" },
		{ "friendadd.ToolTip", "Opens the overlay in minimal mode prompting the user to add the target user as a friend." },
		{ "friendremove.Comment", "/*Opens the overlay in minimal mode prompting the user to remove the target friend.*/" },
		{ "friendremove.Name", "ESteamUserOverlayType::friendremove" },
		{ "friendremove.ToolTip", "Opens the overlay in minimal mode prompting the user to remove the target friend." },
		{ "friendrequestaccept.Comment", "/*Opens the overlay in minimal mode prompting the user to accept an incoming friend invite.*/" },
		{ "friendrequestaccept.Name", "ESteamUserOverlayType::friendrequestaccept" },
		{ "friendrequestaccept.ToolTip", "Opens the overlay in minimal mode prompting the user to accept an incoming friend invite." },
		{ "friendrequestignore.Comment", "/*Opens the overlay in minimal mode prompting the user to ignore an incoming friend invite.*/" },
		{ "friendrequestignore.Name", "ESteamUserOverlayType::friendrequestignore" },
		{ "friendrequestignore.ToolTip", "Opens the overlay in minimal mode prompting the user to ignore an incoming friend invite." },
		{ "invitetolobby.Comment", "/*Opens the invite overlay, invitations sent from this dialog will be for the provided lobby*/" },
		{ "invitetolobby.Name", "ESteamUserOverlayType::invitetolobby" },
		{ "invitetolobby.ToolTip", "Opens the invite overlay, invitations sent from this dialog will be for the provided lobby" },
		{ "IsBlueprintBase", "true" },
		{ "jointrade.Comment", "/*Opens a window to a Steam Trading session that was started with the ISteamEconomy / StartTrade Web API.*/" },
		{ "jointrade.Name", "ESteamUserOverlayType::jointrade" },
		{ "jointrade.ToolTip", "Opens a window to a Steam Trading session that was started with the ISteamEconomy / StartTrade Web API." },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
		{ "stats.Comment", "/*Opens the overlay web browser to the specified user's stats.*/" },
		{ "stats.Name", "ESteamUserOverlayType::stats" },
		{ "stats.ToolTip", "Opens the overlay web browser to the specified user's stats." },
		{ "steamid.Comment", "/*Opens the overlay web browser to the specified user or groups profile.*/" },
		{ "steamid.Name", "ESteamUserOverlayType::steamid" },
		{ "steamid.ToolTip", "Opens the overlay web browser to the specified user or groups profile." },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "ESteamUserOverlayType::steamid", (int64)ESteamUserOverlayType::steamid },
		{ "ESteamUserOverlayType::chat", (int64)ESteamUserOverlayType::chat },
		{ "ESteamUserOverlayType::jointrade", (int64)ESteamUserOverlayType::jointrade },
		{ "ESteamUserOverlayType::stats", (int64)ESteamUserOverlayType::stats },
		{ "ESteamUserOverlayType::achievements", (int64)ESteamUserOverlayType::achievements },
		{ "ESteamUserOverlayType::friendadd", (int64)ESteamUserOverlayType::friendadd },
		{ "ESteamUserOverlayType::friendremove", (int64)ESteamUserOverlayType::friendremove },
		{ "ESteamUserOverlayType::friendrequestaccept", (int64)ESteamUserOverlayType::friendrequestaccept },
		{ "ESteamUserOverlayType::friendrequestignore", (int64)ESteamUserOverlayType::friendrequestignore },
		{ "ESteamUserOverlayType::invitetolobby", (int64)ESteamUserOverlayType::invitetolobby },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
	nullptr,
	"ESteamUserOverlayType",
	"ESteamUserOverlayType",
	Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType()
{
	if (!Z_Registration_Info_UEnum_ESteamUserOverlayType.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_ESteamUserOverlayType.InnerSingleton, Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_ESteamUserOverlayType.InnerSingleton;
}
// ********** End Enum ESteamUserOverlayType *******************************************************

// ********** Begin ScriptStruct FBPSteamGroupInfo *************************************************
static FStructRegistrationInfo Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo;
class UScriptStruct* FBPSteamGroupInfo::StaticStruct()
{
	if (!Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo.OuterSingleton)
	{
		Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo.OuterSingleton = GetStaticStruct(Z_Construct_UScriptStruct_FBPSteamGroupInfo, (UObject*)Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("BPSteamGroupInfo"));
	}
	return Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo.OuterSingleton;
}
struct Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Struct_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroupID_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroupName_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Uint64 representation\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Uint64 representation" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_GroupTag_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_numOnline_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_numInGame_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_numChatting_MetaData[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_GroupID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GroupName;
	static const UECodeGen_Private::FStrPropertyParams NewProp_GroupTag;
	static const UECodeGen_Private::FIntPropertyParams NewProp_numOnline;
	static const UECodeGen_Private::FIntPropertyParams NewProp_numInGame;
	static const UECodeGen_Private::FIntPropertyParams NewProp_numChatting;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static void* NewStructOps()
	{
		return (UScriptStruct::ICppStructOps*)new UScriptStruct::TCppStructOps<FBPSteamGroupInfo>();
	}
	static const UECodeGen_Private::FStructParams StructParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupID = { "GroupID", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBPSteamGroupInfo, GroupID), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroupID_MetaData), NewProp_GroupID_MetaData) }; // 2620465461
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupName = { "GroupName", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBPSteamGroupInfo, GroupName), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroupName_MetaData), NewProp_GroupName_MetaData) };
const UECodeGen_Private::FStrPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupTag = { "GroupTag", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBPSteamGroupInfo, GroupTag), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_GroupTag_MetaData), NewProp_GroupTag_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numOnline = { "numOnline", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBPSteamGroupInfo, numOnline), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_numOnline_MetaData), NewProp_numOnline_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numInGame = { "numInGame", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBPSteamGroupInfo, numInGame), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_numInGame_MetaData), NewProp_numInGame_MetaData) };
const UECodeGen_Private::FIntPropertyParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numChatting = { "numChatting", nullptr, (EPropertyFlags)0x0010000000000015, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(FBPSteamGroupInfo, numChatting), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_numChatting_MetaData), NewProp_numChatting_MetaData) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupName,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_GroupTag,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numOnline,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numInGame,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewProp_numChatting,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FStructParams Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::StructParams = {
	(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
	nullptr,
	&NewStructOps,
	"BPSteamGroupInfo",
	Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::PropPointers,
	UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::PropPointers),
	sizeof(FBPSteamGroupInfo),
	alignof(FBPSteamGroupInfo),
	RF_Public|RF_Transient|RF_MarkAsNative,
	EStructFlags(0x00000001),
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::Struct_MetaDataParams), Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::Struct_MetaDataParams)
};
UScriptStruct* Z_Construct_UScriptStruct_FBPSteamGroupInfo()
{
	if (!Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo.InnerSingleton)
	{
		UECodeGen_Private::ConstructUScriptStruct(Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo.InnerSingleton, Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::StructParams);
	}
	return Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo.InnerSingleton;
}
// ********** End ScriptStruct FBPSteamGroupInfo ***************************************************

// ********** Begin Enum EBPTextFilteringContext ***************************************************
static FEnumRegistrationInfo Z_Registration_Info_UEnum_EBPTextFilteringContext;
static UEnum* EBPTextFilteringContext_StaticEnum()
{
	if (!Z_Registration_Info_UEnum_EBPTextFilteringContext.OuterSingleton)
	{
		Z_Registration_Info_UEnum_EBPTextFilteringContext.OuterSingleton = GetStaticEnum(Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext, (UObject*)Z_Construct_UPackage__Script_AdvancedSteamSessions(), TEXT("EBPTextFilteringContext"));
	}
	return Z_Registration_Info_UEnum_EBPTextFilteringContext.OuterSingleton;
}
template<> ADVANCEDSTEAMSESSIONS_API UEnum* StaticEnum<EBPTextFilteringContext>()
{
	return EBPTextFilteringContext_StaticEnum();
}
struct Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Enum_MetaDataParams[] = {
		{ "BlueprintType", "true" },
		{ "FContext_Chat.Comment", "/*Char from another player.*/" },
		{ "FContext_Chat.Name", "EBPTextFilteringContext::FContext_Chat" },
		{ "FContext_Chat.ToolTip", "Char from another player." },
		{ "FContext_GameContent.Comment", "/*Game content, only legally required filtering is performed.*/" },
		{ "FContext_GameContent.Name", "EBPTextFilteringContext::FContext_GameContent" },
		{ "FContext_GameContent.ToolTip", "Game content, only legally required filtering is performed." },
		{ "FContext_Name.Comment", "/*Character or item name.*/" },
		{ "FContext_Name.Name", "EBPTextFilteringContext::FContext_Name" },
		{ "FContext_Name.ToolTip", "Character or item name." },
		{ "FContext_Unknown.Comment", "/*Unknown context.*/" },
		{ "FContext_Unknown.Name", "EBPTextFilteringContext::FContext_Unknown" },
		{ "FContext_Unknown.ToolTip", "Unknown context." },
		{ "IsBlueprintBase", "true" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif // WITH_METADATA
	static constexpr UECodeGen_Private::FEnumeratorParam Enumerators[] = {
		{ "EBPTextFilteringContext::FContext_Unknown", (int64)EBPTextFilteringContext::FContext_Unknown },
		{ "EBPTextFilteringContext::FContext_GameContent", (int64)EBPTextFilteringContext::FContext_GameContent },
		{ "EBPTextFilteringContext::FContext_Chat", (int64)EBPTextFilteringContext::FContext_Chat },
		{ "EBPTextFilteringContext::FContext_Name", (int64)EBPTextFilteringContext::FContext_Name },
	};
	static const UECodeGen_Private::FEnumParams EnumParams;
};
const UECodeGen_Private::FEnumParams Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext_Statics::EnumParams = {
	(UObject*(*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
	nullptr,
	"EBPTextFilteringContext",
	"EBPTextFilteringContext",
	Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext_Statics::Enumerators,
	RF_Public|RF_Transient|RF_MarkAsNative,
	UE_ARRAY_COUNT(Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext_Statics::Enumerators),
	EEnumFlags::None,
	(uint8)UEnum::ECppForm::EnumClass,
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext_Statics::Enum_MetaDataParams), Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext_Statics::Enum_MetaDataParams)
};
UEnum* Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext()
{
	if (!Z_Registration_Info_UEnum_EBPTextFilteringContext.InnerSingleton)
	{
		UECodeGen_Private::ConstructUEnum(Z_Registration_Info_UEnum_EBPTextFilteringContext.InnerSingleton, Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext_Statics::EnumParams);
	}
	return Z_Registration_Info_UEnum_EBPTextFilteringContext.InnerSingleton;
}
// ********** End Enum EBPTextFilteringContext *****************************************************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function CreateSteamIDFromString ************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics
{
	struct AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms
	{
		FString SteamID64;
		FBPUniqueNetId ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Creates a unique steam id directly from a string holding a uint64 value, useful for testing\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Creates a unique steam id directly from a string holding a uint64 value, useful for testing" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_SteamID64_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_SteamID64;
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_SteamID64 = { "SteamID64", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms, SteamID64), METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_SteamID64_MetaData), NewProp_SteamID64_MetaData) };
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms, ReturnValue), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(0, nullptr) }; // 2620465461
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_SteamID64,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "CreateSteamIDFromString", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::AdvancedSteamFriendsLibrary_eventCreateSteamIDFromString_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execCreateSteamIDFromString)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_SteamID64);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBPUniqueNetId*)Z_Param__Result=UAdvancedSteamFriendsLibrary::CreateSteamIDFromString(Z_Param_SteamID64);
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function CreateSteamIDFromString **************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function FilterText *************************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics
{
	struct AdvancedSteamFriendsLibrary_eventFilterText_Parms
	{
		FString TextToFilter;
		EBPTextFilteringContext Context;
		FBPUniqueNetId TextSourceID;
		FString FilteredText;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|SteamAPI|TextFiltering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Attempts to filter a string with the given filtering context\n// Returns true if the text has been filtered, false if it hasn't (no filtering required or operation failed)\n// If false it will still output the original text\n// Textsource is the steam id that is the source of the text (player name / chat)\n// Requires that InitTextFiltering be called first!!\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Attempts to filter a string with the given filtering context\nReturns true if the text has been filtered, false if it hasn't (no filtering required or operation failed)\nIf false it will still output the original text\nTextsource is the steam id that is the source of the text (player name / chat)\nRequires that InitTextFiltering be called first!!" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_TextSourceID_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStrPropertyParams NewProp_TextToFilter;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Context_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Context;
	static const UECodeGen_Private::FStructPropertyParams NewProp_TextSourceID;
	static const UECodeGen_Private::FStrPropertyParams NewProp_FilteredText;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_TextToFilter = { "TextToFilter", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventFilterText_Parms, TextToFilter), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_Context_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_Context = { "Context", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventFilterText_Parms, Context), Z_Construct_UEnum_AdvancedSteamSessions_EBPTextFilteringContext, METADATA_PARAMS(0, nullptr) }; // 2533580417
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_TextSourceID = { "TextSourceID", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventFilterText_Parms, TextSourceID), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_TextSourceID_MetaData), NewProp_TextSourceID_MetaData) }; // 2620465461
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_FilteredText = { "FilteredText", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventFilterText_Parms, FilteredText), METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedSteamFriendsLibrary_eventFilterText_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventFilterText_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_TextToFilter,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_Context_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_Context,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_TextSourceID,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_FilteredText,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "FilterText", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::AdvancedSteamFriendsLibrary_eventFilterText_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::AdvancedSteamFriendsLibrary_eventFilterText_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execFilterText)
{
	P_GET_PROPERTY(FStrProperty,Z_Param_TextToFilter);
	P_GET_ENUM(EBPTextFilteringContext,Z_Param_Context);
	P_GET_STRUCT(FBPUniqueNetId,Z_Param_TextSourceID);
	P_GET_PROPERTY_REF(FStrProperty,Z_Param_Out_FilteredText);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::FilterText(Z_Param_TextToFilter,EBPTextFilteringContext(Z_Param_Context),Z_Param_TextSourceID,Z_Param_Out_FilteredText);
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function FilterText ***************************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function GetFriendSteamLevel ****************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics
{
	struct AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms
	{
		FBPUniqueNetId UniqueNetId;
		int32 ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Gets the level of a friends steam account, STEAM ONLY, Returns -1 if the steam level is not known, might need RequestSteamFriendInfo called first.\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gets the level of a friends steam account, STEAM ONLY, Returns -1 if the steam level is not known, might need RequestSteamFriendInfo called first." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static const UECodeGen_Private::FIntPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetFriendSteamLevel", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::AdvancedSteamFriendsLibrary_eventGetFriendSteamLevel_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execGetFriendSteamLevel)
{
	P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(int32*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetFriendSteamLevel(Z_Param_UniqueNetId);
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function GetFriendSteamLevel ******************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function GetLocalSteamIDFromSteam ***********
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics
{
	struct AdvancedSteamFriendsLibrary_eventGetLocalSteamIDFromSteam_Parms
	{
		FBPUniqueNetId ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Retreives the local steam ID from steam\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Retreives the local steam ID from steam" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetLocalSteamIDFromSteam_Parms, ReturnValue), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(0, nullptr) }; // 2620465461
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetLocalSteamIDFromSteam", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::AdvancedSteamFriendsLibrary_eventGetLocalSteamIDFromSteam_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::AdvancedSteamFriendsLibrary_eventGetLocalSteamIDFromSteam_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execGetLocalSteamIDFromSteam)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FBPUniqueNetId*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetLocalSteamIDFromSteam();
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function GetLocalSteamIDFromSteam *************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function GetSteamFriendAvatar ***************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics
{
	struct AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms
	{
		FBPUniqueNetId UniqueNetId;
		EBlueprintAsyncResultSwitch Result;
		SteamAvatarSize AvatarSize;
		UTexture2D* ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Get a texture of a valid friends avatar, STEAM ONLY, Returns invalid texture if the subsystem hasn't loaded that size of avatar yet\n" },
#endif
		{ "CPP_Default_AvatarSize", "SteamAvatar_Medium" },
		{ "ExpandEnumAsExecs", "Result" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a texture of a valid friends avatar, STEAM ONLY, Returns invalid texture if the subsystem hasn't loaded that size of avatar yet" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Result_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Result;
	static const UECodeGen_Private::FBytePropertyParams NewProp_AvatarSize_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_AvatarSize;
	static const UECodeGen_Private::FObjectPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, Result), Z_Construct_UEnum_AdvancedSessions_EBlueprintAsyncResultSwitch, METADATA_PARAMS(0, nullptr) }; // 1911516857
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize = { "AvatarSize", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, AvatarSize), Z_Construct_UEnum_AdvancedSteamSessions_SteamAvatarSize, METADATA_PARAMS(0, nullptr) }; // 194323626
const UECodeGen_Private::FObjectPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Object, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms, ReturnValue), Z_Construct_UClass_UTexture2D_NoRegister, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_Result,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_AvatarSize,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamFriendAvatar", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::AdvancedSteamFriendsLibrary_eventGetSteamFriendAvatar_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execGetSteamFriendAvatar)
{
	P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId);
	P_GET_ENUM_REF(EBlueprintAsyncResultSwitch,Z_Param_Out_Result);
	P_GET_ENUM(SteamAvatarSize,Z_Param_AvatarSize);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(UTexture2D**)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetSteamFriendAvatar(Z_Param_UniqueNetId,(EBlueprintAsyncResultSwitch&)(Z_Param_Out_Result),SteamAvatarSize(Z_Param_AvatarSize));
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function GetSteamFriendAvatar *****************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function GetSteamFriendGamePlayed ***********
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics
{
	struct AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms
	{
		FBPUniqueNetId UniqueNetId;
		EBlueprintResultSwitch Result;
		int32 AppID;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "/*, FString & GameName*/" },
#endif
		{ "ExpandEnumAsExecs", "Result" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", ", FString & GameName" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_Result_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_Result;
	static const UECodeGen_Private::FIntPropertyParams NewProp_AppID;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result = { "Result", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms, Result), Z_Construct_UEnum_AdvancedSessions_EBlueprintResultSwitch, METADATA_PARAMS(0, nullptr) }; // 1157740906
const UECodeGen_Private::FIntPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_AppID = { "AppID", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Int, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms, AppID), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_Result,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::NewProp_AppID,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamFriendGamePlayed", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::AdvancedSteamFriendsLibrary_eventGetSteamFriendGamePlayed_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execGetSteamFriendGamePlayed)
{
	P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId);
	P_GET_ENUM_REF(EBlueprintResultSwitch,Z_Param_Out_Result);
	P_GET_PROPERTY_REF(FIntProperty,Z_Param_Out_AppID);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedSteamFriendsLibrary::GetSteamFriendGamePlayed(Z_Param_UniqueNetId,(EBlueprintResultSwitch&)(Z_Param_Out_Result),Z_Param_Out_AppID);
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function GetSteamFriendGamePlayed *************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function GetSteamGroups *********************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics
{
	struct AdvancedSteamFriendsLibrary_eventGetSteamGroups_Parms
	{
		TArray<FBPSteamGroupInfo> SteamGroups;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|SteamAPI|SteamGroups" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Get a full list of steam groups\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Get a full list of steam groups" },
#endif
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_SteamGroups_Inner;
	static const UECodeGen_Private::FArrayPropertyParams NewProp_SteamGroups;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups_Inner = { "SteamGroups", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, Z_Construct_UScriptStruct_FBPSteamGroupInfo, METADATA_PARAMS(0, nullptr) }; // 3145522780
const UECodeGen_Private::FArrayPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups = { "SteamGroups", nullptr, (EPropertyFlags)0x0010000000000180, UECodeGen_Private::EPropertyGenFlags::Array, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamGroups_Parms, SteamGroups), EArrayPropertyFlags::None, METADATA_PARAMS(0, nullptr) }; // 3145522780
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups_Inner,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::NewProp_SteamGroups,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamGroups", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::AdvancedSteamFriendsLibrary_eventGetSteamGroups_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04422401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::AdvancedSteamFriendsLibrary_eventGetSteamGroups_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execGetSteamGroups)
{
	P_GET_TARRAY_REF(FBPSteamGroupInfo,Z_Param_Out_SteamGroups);
	P_FINISH;
	P_NATIVE_BEGIN;
	UAdvancedSteamFriendsLibrary::GetSteamGroups(Z_Param_Out_SteamGroups);
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function GetSteamGroups ***********************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function GetSteamPersonaName ****************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics
{
	struct AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms
	{
		FBPUniqueNetId UniqueNetId;
		FString ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Gets the persona name of a steam ID, STEAM ONLY, Returns empty if no result, might need RequestSteamFriendInfo called first.\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Gets the persona name of a steam ID, STEAM ONLY, Returns empty if no result, might need RequestSteamFriendInfo called first." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static const UECodeGen_Private::FStrPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
const UECodeGen_Private::FStrPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Str, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms, ReturnValue), METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "GetSteamPersonaName", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::AdvancedSteamFriendsLibrary_eventGetSteamPersonaName_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execGetSteamPersonaName)
{
	P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(FString*)Z_Param__Result=UAdvancedSteamFriendsLibrary::GetSteamPersonaName(Z_Param_UniqueNetId);
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function GetSteamPersonaName ******************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function InitTextFiltering ******************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics
{
	struct AdvancedSteamFriendsLibrary_eventInitTextFiltering_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|SteamAPI|TextFiltering" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Initializes text filtering (pre-loading dictonaries)\n// Returns if it succeeded, false if filtering is unavailable for the games language\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Initializes text filtering (pre-loading dictonaries)\nReturns if it succeeded, false if filtering is unavailable for the games language" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedSteamFriendsLibrary_eventInitTextFiltering_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventInitTextFiltering_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "InitTextFiltering", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::AdvancedSteamFriendsLibrary_eventInitTextFiltering_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::AdvancedSteamFriendsLibrary_eventInitTextFiltering_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execInitTextFiltering)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::InitTextFiltering();
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function InitTextFiltering ********************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function IsOverlayEnabled *******************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics
{
	struct AdvancedSteamFriendsLibrary_eventIsOverlayEnabled_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Returns if the steam overlay is currently active (this can return false during initial overlay hooking)\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns if the steam overlay is currently active (this can return false during initial overlay hooking)" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedSteamFriendsLibrary_eventIsOverlayEnabled_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventIsOverlayEnabled_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "IsOverlayEnabled", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::AdvancedSteamFriendsLibrary_eventIsOverlayEnabled_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::AdvancedSteamFriendsLibrary_eventIsOverlayEnabled_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execIsOverlayEnabled)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::IsOverlayEnabled();
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function IsOverlayEnabled *********************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function IsSteamInBigPictureMode ************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics
{
	struct AdvancedSteamFriendsLibrary_eventIsSteamInBigPictureMode_Parms
	{
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Returns if steam is running in big picture mode\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Returns if steam is running in big picture mode" },
#endif
	};
#endif // WITH_METADATA
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedSteamFriendsLibrary_eventIsSteamInBigPictureMode_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventIsSteamInBigPictureMode_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "IsSteamInBigPictureMode", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::AdvancedSteamFriendsLibrary_eventIsSteamInBigPictureMode_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x14022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::AdvancedSteamFriendsLibrary_eventIsSteamInBigPictureMode_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execIsSteamInBigPictureMode)
{
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::IsSteamInBigPictureMode();
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function IsSteamInBigPictureMode **************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function OpenSteamUserOverlay ***************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics
{
	struct AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms
	{
		FBPUniqueNetId UniqueNetId;
		ESteamUserOverlayType DialogType;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Opens the steam overlay to go to the specified user dialog\n" },
#endif
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Opens the steam overlay to go to the specified user dialog" },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static const UECodeGen_Private::FBytePropertyParams NewProp_DialogType_Underlying;
	static const UECodeGen_Private::FEnumPropertyParams NewProp_DialogType;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
const UECodeGen_Private::FBytePropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType_Underlying = { "UnderlyingType", nullptr, (EPropertyFlags)0x0000000000000000, UECodeGen_Private::EPropertyGenFlags::Byte, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, 0, nullptr, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FEnumPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType = { "DialogType", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Enum, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms, DialogType), Z_Construct_UEnum_AdvancedSteamSessions_ESteamUserOverlayType, METADATA_PARAMS(0, nullptr) }; // 1877924798
void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType_Underlying,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_DialogType,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "OpenSteamUserOverlay", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::AdvancedSteamFriendsLibrary_eventOpenSteamUserOverlay_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execOpenSteamUserOverlay)
{
	P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId);
	P_GET_ENUM(ESteamUserOverlayType,Z_Param_DialogType);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::OpenSteamUserOverlay(Z_Param_UniqueNetId,ESteamUserOverlayType(Z_Param_DialogType));
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function OpenSteamUserOverlay *****************

// ********** Begin Class UAdvancedSteamFriendsLibrary Function RequestSteamFriendInfo *************
struct Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics
{
	struct AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms
	{
		FBPUniqueNetId UniqueNetId;
		bool bRequireNameOnly;
		bool ReturnValue;
	};
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Function_MetaDataParams[] = {
		{ "Category", "Online|AdvancedFriends|SteamAPI" },
#if !UE_BUILD_SHIPPING
		{ "Comment", "// Preloads the avatar and name of a steam friend, return whether it is already available or not, STEAM ONLY, Takes time to actually load everything after this is called.\n" },
#endif
		{ "CPP_Default_bRequireNameOnly", "false" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
#if !UE_BUILD_SHIPPING
		{ "ToolTip", "Preloads the avatar and name of a steam friend, return whether it is already available or not, STEAM ONLY, Takes time to actually load everything after this is called." },
#endif
	};
	static constexpr UECodeGen_Private::FMetaDataPairParam NewProp_UniqueNetId_MetaData[] = {
		{ "NativeConst", "" },
	};
#endif // WITH_METADATA
	static const UECodeGen_Private::FStructPropertyParams NewProp_UniqueNetId;
	static void NewProp_bRequireNameOnly_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_bRequireNameOnly;
	static void NewProp_ReturnValue_SetBit(void* Obj);
	static const UECodeGen_Private::FBoolPropertyParams NewProp_ReturnValue;
	static const UECodeGen_Private::FPropertyParamsBase* const PropPointers[];
	static const UECodeGen_Private::FFunctionParams FuncParams;
};
const UECodeGen_Private::FStructPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_UniqueNetId = { "UniqueNetId", nullptr, (EPropertyFlags)0x0010000000000082, UECodeGen_Private::EPropertyGenFlags::Struct, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, STRUCT_OFFSET(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms, UniqueNetId), Z_Construct_UScriptStruct_FBPUniqueNetId, METADATA_PARAMS(UE_ARRAY_COUNT(NewProp_UniqueNetId_MetaData), NewProp_UniqueNetId_MetaData) }; // 2620465461
void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly_SetBit(void* Obj)
{
	((AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms*)Obj)->bRequireNameOnly = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly = { "bRequireNameOnly", nullptr, (EPropertyFlags)0x0010000000000080, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly_SetBit, METADATA_PARAMS(0, nullptr) };
void Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue_SetBit(void* Obj)
{
	((AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms*)Obj)->ReturnValue = 1;
}
const UECodeGen_Private::FBoolPropertyParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue = { "ReturnValue", nullptr, (EPropertyFlags)0x0010000000000580, UECodeGen_Private::EPropertyGenFlags::Bool | UECodeGen_Private::EPropertyGenFlags::NativeBool, RF_Public|RF_Transient|RF_MarkAsNative, nullptr, nullptr, 1, sizeof(bool), sizeof(AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue_SetBit, METADATA_PARAMS(0, nullptr) };
const UECodeGen_Private::FPropertyParamsBase* const Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::PropPointers[] = {
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_UniqueNetId,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_bRequireNameOnly,
	(const UECodeGen_Private::FPropertyParamsBase*)&Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::NewProp_ReturnValue,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::PropPointers) < 2048);
const UECodeGen_Private::FFunctionParams Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::FuncParams = { { (UObject*(*)())Z_Construct_UClass_UAdvancedSteamFriendsLibrary, nullptr, "RequestSteamFriendInfo", Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::PropPointers, UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::PropPointers), sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms), RF_Public|RF_Transient|RF_MarkAsNative, (EFunctionFlags)0x04022401, 0, 0, METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::Function_MetaDataParams), Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::Function_MetaDataParams)},  };
static_assert(sizeof(Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::AdvancedSteamFriendsLibrary_eventRequestSteamFriendInfo_Parms) < MAX_uint16);
UFunction* Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo()
{
	static UFunction* ReturnFunction = nullptr;
	if (!ReturnFunction)
	{
		UECodeGen_Private::ConstructUFunction(&ReturnFunction, Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo_Statics::FuncParams);
	}
	return ReturnFunction;
}
DEFINE_FUNCTION(UAdvancedSteamFriendsLibrary::execRequestSteamFriendInfo)
{
	P_GET_STRUCT(FBPUniqueNetId,Z_Param_UniqueNetId);
	P_GET_UBOOL(Z_Param_bRequireNameOnly);
	P_FINISH;
	P_NATIVE_BEGIN;
	*(bool*)Z_Param__Result=UAdvancedSteamFriendsLibrary::RequestSteamFriendInfo(Z_Param_UniqueNetId,Z_Param_bRequireNameOnly);
	P_NATIVE_END;
}
// ********** End Class UAdvancedSteamFriendsLibrary Function RequestSteamFriendInfo ***************

// ********** Begin Class UAdvancedSteamFriendsLibrary *********************************************
void UAdvancedSteamFriendsLibrary::StaticRegisterNativesUAdvancedSteamFriendsLibrary()
{
	UClass* Class = UAdvancedSteamFriendsLibrary::StaticClass();
	static const FNameNativePtrPair Funcs[] = {
		{ "CreateSteamIDFromString", &UAdvancedSteamFriendsLibrary::execCreateSteamIDFromString },
		{ "FilterText", &UAdvancedSteamFriendsLibrary::execFilterText },
		{ "GetFriendSteamLevel", &UAdvancedSteamFriendsLibrary::execGetFriendSteamLevel },
		{ "GetLocalSteamIDFromSteam", &UAdvancedSteamFriendsLibrary::execGetLocalSteamIDFromSteam },
		{ "GetSteamFriendAvatar", &UAdvancedSteamFriendsLibrary::execGetSteamFriendAvatar },
		{ "GetSteamFriendGamePlayed", &UAdvancedSteamFriendsLibrary::execGetSteamFriendGamePlayed },
		{ "GetSteamGroups", &UAdvancedSteamFriendsLibrary::execGetSteamGroups },
		{ "GetSteamPersonaName", &UAdvancedSteamFriendsLibrary::execGetSteamPersonaName },
		{ "InitTextFiltering", &UAdvancedSteamFriendsLibrary::execInitTextFiltering },
		{ "IsOverlayEnabled", &UAdvancedSteamFriendsLibrary::execIsOverlayEnabled },
		{ "IsSteamInBigPictureMode", &UAdvancedSteamFriendsLibrary::execIsSteamInBigPictureMode },
		{ "OpenSteamUserOverlay", &UAdvancedSteamFriendsLibrary::execOpenSteamUserOverlay },
		{ "RequestSteamFriendInfo", &UAdvancedSteamFriendsLibrary::execRequestSteamFriendInfo },
	};
	FNativeFunctionRegistrar::RegisterFunctions(Class, Funcs, UE_ARRAY_COUNT(Funcs));
}
FClassRegistrationInfo Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary;
UClass* UAdvancedSteamFriendsLibrary::GetPrivateStaticClass()
{
	using TClass = UAdvancedSteamFriendsLibrary;
	if (!Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary.InnerSingleton)
	{
		GetPrivateStaticClassBody(
			StaticPackage(),
			TEXT("AdvancedSteamFriendsLibrary"),
			Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary.InnerSingleton,
			StaticRegisterNativesUAdvancedSteamFriendsLibrary,
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
	return Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary.InnerSingleton;
}
UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary_NoRegister()
{
	return UAdvancedSteamFriendsLibrary::GetPrivateStaticClass();
}
struct Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics
{
#if WITH_METADATA
	static constexpr UECodeGen_Private::FMetaDataPairParam Class_MetaDataParams[] = {
		{ "IncludePath", "AdvancedSteamFriendsLibrary.h" },
		{ "ModuleRelativePath", "Classes/AdvancedSteamFriendsLibrary.h" },
	};
#endif // WITH_METADATA
	static UObject* (*const DependentSingletons[])();
	static constexpr FClassFunctionLinkInfo FuncInfo[] = {
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_CreateSteamIDFromString, "CreateSteamIDFromString" }, // 1065408745
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_FilterText, "FilterText" }, // 2790355525
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetFriendSteamLevel, "GetFriendSteamLevel" }, // 2174970233
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetLocalSteamIDFromSteam, "GetLocalSteamIDFromSteam" }, // 1968289249
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendAvatar, "GetSteamFriendAvatar" }, // 4039202713
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamFriendGamePlayed, "GetSteamFriendGamePlayed" }, // 3460643319
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamGroups, "GetSteamGroups" }, // 726300350
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_GetSteamPersonaName, "GetSteamPersonaName" }, // 475548267
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_InitTextFiltering, "InitTextFiltering" }, // 2512254508
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsOverlayEnabled, "IsOverlayEnabled" }, // 85629807
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_IsSteamInBigPictureMode, "IsSteamInBigPictureMode" }, // 3174770534
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_OpenSteamUserOverlay, "OpenSteamUserOverlay" }, // 2849056362
		{ &Z_Construct_UFunction_UAdvancedSteamFriendsLibrary_RequestSteamFriendInfo, "RequestSteamFriendInfo" }, // 167532536
	};
	static_assert(UE_ARRAY_COUNT(FuncInfo) < 2048);
	static constexpr FCppClassTypeInfoStatic StaticCppClassTypeInfo = {
		TCppClassTypeTraits<UAdvancedSteamFriendsLibrary>::IsAbstract,
	};
	static const UECodeGen_Private::FClassParams ClassParams;
};
UObject* (*const Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::DependentSingletons[])() = {
	(UObject* (*)())Z_Construct_UClass_UBlueprintFunctionLibrary,
	(UObject* (*)())Z_Construct_UPackage__Script_AdvancedSteamSessions,
};
static_assert(UE_ARRAY_COUNT(Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::DependentSingletons) < 16);
const UECodeGen_Private::FClassParams Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::ClassParams = {
	&UAdvancedSteamFriendsLibrary::StaticClass,
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
	METADATA_PARAMS(UE_ARRAY_COUNT(Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::Class_MetaDataParams), Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::Class_MetaDataParams)
};
UClass* Z_Construct_UClass_UAdvancedSteamFriendsLibrary()
{
	if (!Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary.OuterSingleton)
	{
		UECodeGen_Private::ConstructUClass(Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary.OuterSingleton, Z_Construct_UClass_UAdvancedSteamFriendsLibrary_Statics::ClassParams);
	}
	return Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary.OuterSingleton;
}
UAdvancedSteamFriendsLibrary::UAdvancedSteamFriendsLibrary(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer) {}
DEFINE_VTABLE_PTR_HELPER_CTOR(UAdvancedSteamFriendsLibrary);
UAdvancedSteamFriendsLibrary::~UAdvancedSteamFriendsLibrary() {}
// ********** End Class UAdvancedSteamFriendsLibrary ***********************************************

// ********** Begin Registration *******************************************************************
struct Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_Statics
{
	static constexpr FEnumRegisterCompiledInInfo EnumInfo[] = {
		{ SteamAvatarSize_StaticEnum, TEXT("SteamAvatarSize"), &Z_Registration_Info_UEnum_SteamAvatarSize, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 194323626U) },
		{ ESteamUserOverlayType_StaticEnum, TEXT("ESteamUserOverlayType"), &Z_Registration_Info_UEnum_ESteamUserOverlayType, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 1877924798U) },
		{ EBPTextFilteringContext_StaticEnum, TEXT("EBPTextFilteringContext"), &Z_Registration_Info_UEnum_EBPTextFilteringContext, CONSTRUCT_RELOAD_VERSION_INFO(FEnumReloadVersionInfo, 2533580417U) },
	};
	static constexpr FStructRegisterCompiledInInfo ScriptStructInfo[] = {
		{ FBPSteamGroupInfo::StaticStruct, Z_Construct_UScriptStruct_FBPSteamGroupInfo_Statics::NewStructOps, TEXT("BPSteamGroupInfo"), &Z_Registration_Info_UScriptStruct_FBPSteamGroupInfo, CONSTRUCT_RELOAD_VERSION_INFO(FStructReloadVersionInfo, sizeof(FBPSteamGroupInfo), 3145522780U) },
	};
	static constexpr FClassRegisterCompiledInInfo ClassInfo[] = {
		{ Z_Construct_UClass_UAdvancedSteamFriendsLibrary, UAdvancedSteamFriendsLibrary::StaticClass, TEXT("UAdvancedSteamFriendsLibrary"), &Z_Registration_Info_UClass_UAdvancedSteamFriendsLibrary, CONSTRUCT_RELOAD_VERSION_INFO(FClassReloadVersionInfo, sizeof(UAdvancedSteamFriendsLibrary), 1201872263U) },
	};
};
static FRegisterCompiledInInfo Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_1199553785(TEXT("/Script/AdvancedSteamSessions"),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_Statics::ClassInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_Statics::ClassInfo),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_Statics::ScriptStructInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_Statics::ScriptStructInfo),
	Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_Statics::EnumInfo, UE_ARRAY_COUNT(Z_CompiledInDeferFile_FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSteamSessions_Source_AdvancedSteamSessions_Classes_AdvancedSteamFriendsLibrary_h__Script_AdvancedSteamSessions_Statics::EnumInfo));
// ********** End Registration *********************************************************************

PRAGMA_ENABLE_DEPRECATION_WARNINGS
