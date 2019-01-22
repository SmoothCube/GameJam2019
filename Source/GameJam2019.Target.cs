// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class GameJam2019Target : TargetRules
{
	public GameJam2019Target(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "GameJam2019" } );
	}
}
