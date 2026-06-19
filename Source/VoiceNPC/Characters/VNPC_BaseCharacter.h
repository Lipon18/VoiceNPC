// Psycho Games 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VNPC_BaseCharacter.generated.h"

UCLASS()
class VOICENPC_API AVNPC_BaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	AVNPC_BaseCharacter();

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;
};
