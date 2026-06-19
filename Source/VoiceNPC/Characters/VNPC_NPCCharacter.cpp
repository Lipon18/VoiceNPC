// Psycho Games 2026. All rights reserved.


#include "Characters/VNPC_NPCCharacter.h"
#include "VNPCData/VNPC_PersonalityDataAsset.h"
#include "VNPCData/Personality.h"
#include "Components/BoxComponent.h"

AVNPC_NPCCharacter::AVNPC_NPCCharacter()
{
	InteractionVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionVolume"));
	InteractionVolume->SetupAttachment(RootComponent);

	InteractionVolume->SetBoxExtent(FVector(150.0f, 150.0f, 110.0f));

	InteractionVolume->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	InteractionVolume->SetCollisionObjectType(ECC_WorldDynamic);
	InteractionVolume->SetCollisionResponseToAllChannels(ECR_Ignore);
	InteractionVolume->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

FString AVNPC_NPCCharacter::GetSystemPrompt() const
{
	if (PersonalityAsset) return PersonalityAsset->PersonalityData.GenerateSystemPrompt();
	UE_LOG(LogTemp, Warning, TEXT("GetSystemPrompt called on %s, but no PersonalityAsset is assigned!"), *GetName());
	return TEXT("You are generic NPC helper.");
}
