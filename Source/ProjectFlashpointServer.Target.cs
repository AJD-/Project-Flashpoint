// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

[SupportedPlatforms(UnrealPlatformClass.Server)]
public class ProjectFlashpointServerTarget : TargetRules   // Change this line as shown previously
{
       public ProjectFlashpointServerTarget(TargetInfo Target) : base(Target)  // Change this line as shown previously
       {
        Type = TargetType.Server;
        ExtraModuleNames.Add("ProjectFlashpoint");    // Change this line as shown previously
       }
}