// Psycho Games 2026. All rights reserved.

using UnrealBuildTool;

public class VoiceNPC : ModuleRules
{
	public VoiceNPC(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "HTTP" });
        PrivateDependencyModuleNames.AddRange(new string[] { "CoreUObject", "Engine", "InputCore", "EnhancedInput", "Slate", "SlateCore", "Json", "JsonUtilities" });

        PublicIncludePaths.AddRange(new string[] { ModuleDirectory });
	}
}
