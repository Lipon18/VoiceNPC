// Psycho Games 2026. All rights reserved.

#include "VNPC_GameMode.h"
#include "VoiceNPC/Characters/VNPC_PlayerCharacter.h"
#include "UObject/ConstructorHelpers.h"

AVNPC_GameMode::AVNPC_GameMode()
{
	DefaultPawnClass = AVNPC_PlayerCharacter::StaticClass();
}
