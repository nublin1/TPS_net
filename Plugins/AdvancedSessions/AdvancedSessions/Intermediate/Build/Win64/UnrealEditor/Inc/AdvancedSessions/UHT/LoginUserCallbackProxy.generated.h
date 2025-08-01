// Copyright Epic Games, Inc. All Rights Reserved.
/*===========================================================================
	Generated code exported from UnrealHeaderTool.
	DO NOT modify this manually! Edit the corresponding .h files instead!
===========================================================================*/

// IWYU pragma: private, include "LoginUserCallbackProxy.h"

#ifdef ADVANCEDSESSIONS_LoginUserCallbackProxy_generated_h
#error "LoginUserCallbackProxy.generated.h already included, missing '#pragma once' in LoginUserCallbackProxy.h"
#endif
#define ADVANCEDSESSIONS_LoginUserCallbackProxy_generated_h

#include "UObject/ObjectMacros.h"
#include "UObject/ScriptMacros.h"

PRAGMA_DISABLE_DEPRECATION_WARNINGS

class APlayerController;
class ULoginUserCallbackProxy;
class UObject;

// ********** Begin Class ULoginUserCallbackProxy **************************************************
#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_13_RPC_WRAPPERS \
	DECLARE_FUNCTION(execLoginUser);


ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_ULoginUserCallbackProxy_NoRegister();

#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_13_INCLASS \
private: \
	static void StaticRegisterNativesULoginUserCallbackProxy(); \
	friend struct Z_Construct_UClass_ULoginUserCallbackProxy_Statics; \
	static UClass* GetPrivateStaticClass(); \
	friend ADVANCEDSESSIONS_API UClass* Z_Construct_UClass_ULoginUserCallbackProxy_NoRegister(); \
public: \
	DECLARE_CLASS2(ULoginUserCallbackProxy, UOnlineBlueprintCallProxyBase, COMPILED_IN_FLAGS(0), CASTCLASS_None, TEXT("/Script/AdvancedSessions"), Z_Construct_UClass_ULoginUserCallbackProxy_NoRegister) \
	DECLARE_SERIALIZER(ULoginUserCallbackProxy)


#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_13_STANDARD_CONSTRUCTORS \
	/** Standard constructor, called after all reflected properties have been initialized */ \
	ADVANCEDSESSIONS_API ULoginUserCallbackProxy(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get()); \
	DEFINE_DEFAULT_OBJECT_INITIALIZER_CONSTRUCTOR_CALL(ULoginUserCallbackProxy) \
	DECLARE_VTABLE_PTR_HELPER_CTOR(ADVANCEDSESSIONS_API, ULoginUserCallbackProxy); \
	DEFINE_VTABLE_PTR_HELPER_CTOR_CALLER(ULoginUserCallbackProxy); \
	/** Deleted move- and copy-constructors, should never be used */ \
	ULoginUserCallbackProxy(ULoginUserCallbackProxy&&) = delete; \
	ULoginUserCallbackProxy(const ULoginUserCallbackProxy&) = delete; \
	ADVANCEDSESSIONS_API virtual ~ULoginUserCallbackProxy();


#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_10_PROLOG
#define FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_13_GENERATED_BODY_LEGACY \
PRAGMA_DISABLE_DEPRECATION_WARNINGS \
public: \
	FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_13_RPC_WRAPPERS \
	FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_13_INCLASS \
	FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h_13_STANDARD_CONSTRUCTORS \
public: \
PRAGMA_ENABLE_DEPRECATION_WARNINGS


class ULoginUserCallbackProxy;

// ********** End Class ULoginUserCallbackProxy ****************************************************

#undef CURRENT_FILE_ID
#define CURRENT_FILE_ID FID_TPS_net_5_4_Plugins_AdvancedSessions_AdvancedSessions_Source_AdvancedSessions_Classes_LoginUserCallbackProxy_h

PRAGMA_ENABLE_DEPRECATION_WARNINGS
