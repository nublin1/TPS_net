// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "AdvancedVoiceLibrary.h"

#ifdef ADVANCEDSESSIONS_AdvancedVoiceLibrary_generated_h
#error "AdvancedVoiceLibrary.generated.h already included, missing '#pragma once' in AdvancedVoiceLibrary.h"
#endif
#define ADVANCEDSESSIONS_AdvancedVoiceLibrary_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class UObject;
struct FBPUniqueNetId;

// ********** Begin Class UAdvancedVoiceLibrary ****************************************************
#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	DECLARE_FUNCTION(execGetNumLocalTalkers); \
	DECLARE_FUNCTION(execUnMuteRemoteTalker); \
	DECLARE_FUNCTION(execMuteRemoteTalker); \
	DECLARE_FUNCTION(execIsPlayerMuted); \
	DECLARE_FUNCTION(execIsRemotePlayerTalking); \
	DECLARE_FUNCTION(execIsLocalPlayerTalking); \
	DECLARE_FUNCTION(execRemoveAllRemoteTalkers); \
	DECLARE_FUNCTION(execUnRegisterRemoteTalker); \
	DECLARE_FUNCTION(execRegisterRemoteTalker); \
	DECLARE_FUNCTION(execUnRegisterAllLocalTalkers); \
	DECLARE_FUNCTION(execUnRegisterLocalTalker); \
	DECLARE_FUNCTION(execRegisterAllLocalTalkers); \
	DECLARE_FUNCTION(execRegisterLocalTalker); \
	DECLARE_FUNCTION(execStopNetworkedVoice); \
	DECLARE_FUNCTION(execStartNetworkedVoice); \
	DECLARE_FUNCTION(execIsHeadsetPresent);


ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_UAdvancedVoiceLibrary_NoRegister();

#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_INCLASS_NO_PURE_DECLS \
private: \
	static void StaticRegisterNativesUAdvancedVoiceLibrary(); \
	friend struct Z_Construct_UClass_UAdvancedVoiceLibrary_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_UAdvancedVoiceLibrary_NoRegister(); \
public: \
	DECLARE_CLASS2(UAdvancedVoiceLibrary, UBlueprintFunctionLibrary, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSessions"), Z_Construct_UClass_UAdvancedVoiceLibrary_NoRegister) \
	DECLARE_SERIALIZER(UAdvancedVoiceLibrary)


#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_ENHANCED_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	NO_API UAdvancedVoiceLibrary(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	/** Deleted move- and copy-constructors, should never be used */ \
	UAdvancedVoiceLibrary(UAdvancedVoiceLibrary&&) = delete; \
	UAdvancedVoiceLibrary(const UAdvancedVoiceLibrary&) = delete; \
	DECLARE_VTABLE_PTR_HELPER_CTOR(NO_API, UAdvancedVoiceLibrary); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(UAdvancedVoiceLibrary); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(UAdvancedVoiceLibrary) \
	NO_API virtual ~UAdvancedVoiceLibrary();


#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_26_PROLOG
#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_GENERATED_BODY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_RPC_WRAPPERS_NO_PURE_DECLS \
	FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_INCLASS_NO_PURE_DECLS \
	FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h_29_ENHANCED_CONSTRUCTORS \
private: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class UAdvancedVoiceLibrary;

// ********** End Class UAdvancedVoiceLibrary ******************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_AdvancedVoiceLibrary_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
