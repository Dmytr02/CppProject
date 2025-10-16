// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class CppProject : ModuleRules
{
	public CppProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] {
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"EnhancedInput",
			"AIModule",
			"StateTreeModule",
			"GameplayStateTreeModule",
			"UMG",
			"Slate"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		PublicIncludePaths.AddRange(new string[] {
			"CppProject",
			"CppProject/Variant_Platforming",
			"CppProject/Variant_Platforming/Animation",
			"CppProject/Variant_Combat",
			"CppProject/Variant_Combat/AI",
			"CppProject/Variant_Combat/Animation",
			"CppProject/Variant_Combat/Gameplay",
			"CppProject/Variant_Combat/Interfaces",
			"CppProject/Variant_Combat/UI",
			"CppProject/Variant_SideScrolling",
			"CppProject/Variant_SideScrolling/AI",
			"CppProject/Variant_SideScrolling/Gameplay",
			"CppProject/Variant_SideScrolling/Interfaces",
			"CppProject/Variant_SideScrolling/UI"
		});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
