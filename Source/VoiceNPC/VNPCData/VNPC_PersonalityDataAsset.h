// Psycho Games 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "VNPCData/Personality.h"
#include "VNPC_PersonalityDataAsset.generated.h"

UCLASS()
class VOICENPC_API UVNPC_PersonalityDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "NPC Personality")
	FNPCPersonality PersonalityData;
};
