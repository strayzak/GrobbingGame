// Copyright Epic Games, Inc. All Rights Reserved.

#include "GrobbingGameGameMode.h"
#include "GrobbingGameCharacter.h"
#include "UObject/ConstructorHelpers.h"

AGrobbingGameGameMode::AGrobbingGameGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
