// Copyright Epic Games, Inc. All Rights Reserved.

#include "GD3_Lino_CppGameMode.h"
#include "GD3_Lino_CppCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGD3_Lino_CppGameMode::AGD3_Lino_CppGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
