// Psycho Games 2026. All rights reserved.


#include "VoiceNPC/Characters/VNPC_BaseCharacter.h"

// Sets default values
AVNPC_BaseCharacter::AVNPC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AVNPC_BaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void AVNPC_BaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}