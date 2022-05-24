// KShooter - All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class KShooterEditorTarget : TargetRules
{
	public KShooterEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "KShooter" } );
	}
}
