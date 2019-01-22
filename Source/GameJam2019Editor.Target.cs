// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GameJam2019EditorTarget : TargetRules
{
	public GameJam2019EditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "GameJam2019" } );
	}
}
