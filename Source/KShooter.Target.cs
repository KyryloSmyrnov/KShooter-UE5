// KShooter - All Rights Reserved

using UnrealBuildTool;
using System.Collections.Generic;

public class KShooterTarget : TargetRules
{
	public KShooterTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V2;

		ExtraModuleNames.AddRange( new string[] { "KShooter" } );
	}
}
