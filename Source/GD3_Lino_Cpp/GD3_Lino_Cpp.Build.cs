// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class GD3_Lino_Cpp : ModuleRules
{
	public GD3_Lino_Cpp(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
