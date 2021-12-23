// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class WarlordsOfDarkness : ModuleRules
{
	public WarlordsOfDarkness(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "NavigationSystem", "AIModule" });
    }
}
