// Psycho Games 2026. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VoiceNPCTarget : TargetRules
{
	public VoiceNPCTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("VoiceNPC");
	}
}
