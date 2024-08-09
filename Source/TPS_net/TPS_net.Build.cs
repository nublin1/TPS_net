// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class TPS_net : ModuleRules
{
	public TPS_net(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore","RHI" ,"GameplayTags",
			"Slate", "SlateCore", "OnlineSubsystem", "OnlineSubsystemUtils", "AdvancedSteamSessions" });

		PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
        //DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
