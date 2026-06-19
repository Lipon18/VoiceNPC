// Psycho Games 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "VoiceNPC/Characters/VNPC_BaseCharacter.h"
#include "VNPCInterface/TalkableNPCInterface.h"
#include "VNPC_NPCCharacter.generated.h"

class UVNPC_PersonalityDataAsset;
class UBoxComponent;

UCLASS()
class VOICENPC_API AVNPC_NPCCharacter : public AVNPC_BaseCharacter, public ITalkableNPCInterface
{
	GENERATED_BODY()

public:
	AVNPC_NPCCharacter();

	UFUNCTION(BlueprintCallable, Category = "Voice NPC | AI")
	FString GetSystemPrompt() const;

	FORCEINLINE UVNPC_PersonalityDataAsset* GetNPCPersonalityAssetData() const { return PersonalityAsset; }

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice NPC | AI")
	TObjectPtr<UVNPC_PersonalityDataAsset> PersonalityAsset;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	TObjectPtr<UBoxComponent> InteractionVolume;
};
