// Psycho Games 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Personality.generated.h"

USTRUCT(BlueprintType)
struct FNPCPersonality
{
    GENERATED_USTRUCT_BODY()

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Name;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    int32 Age = 18;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Gender;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Job;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString Country;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity", meta = (MultiLine = true))
    FString BackgroundStory;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString PersonalityTraits;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString SpeakingStyle;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Identity")
    FString CurrentObjective;

    FString GenerateSystemPrompt() const
    {
        FString Prompt = FString::Printf(TEXT("You are roleplaying as %s, a %d-year-old %s from %s.\n"), *Name, Age, *Job, *Country);
        Prompt += FString::Printf(TEXT("Gender: %s\n"), *Gender);
        Prompt += FString::Printf(TEXT("Personality: %s\n"), *PersonalityTraits);
        Prompt += FString::Printf(TEXT("Speaking Style: %s\n"), *SpeakingStyle);
        Prompt += FString::Printf(TEXT("Backstory: %s\n"), *BackgroundStory);
        Prompt += FString::Printf(TEXT("Current Goal: %s\n"), *CurrentObjective);
        Prompt += TEXT("\nCRITICAL RULE: Respond in one to two short sentence only. Do not write paragraphs.");
        return Prompt;
    }
};
