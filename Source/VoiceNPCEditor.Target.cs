// Psycho Games 2026. All rights reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class VoiceNPCEditorTarget : TargetRules
{
	public VoiceNPCEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.Add("VoiceNPC");
	}
}
