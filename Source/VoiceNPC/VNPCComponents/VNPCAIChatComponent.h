// Psycho Games 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Http.h"
#include "VNPCAIChatComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAIChatResponseReceived, const FString&, NPCName, const FString&, ResponseText);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAIChatError, const FString&, ErrorMessage);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class VOICENPC_API UVNPCAIChatComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UVNPCAIChatComponent();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI Chat")
	FString ServerUrl = TEXT("http://127.0.0.1:8000/chat");

	UPROPERTY(BlueprintAssignable, Category = "AI Chat")
	FOnAIChatResponseReceived OnResponseReceived;

	UPROPERTY(BlueprintAssignable, Category = "AI Chat")
	FOnAIChatError OnChatError;

	UFUNCTION(BlueprintCallable, Category = "AI Chat")
	void SendPromptToNPC(const FString& FullSystemPrompt, const FString& PlayerPrompt, const FString& NPCName);

private:
	FString CurrentSpeakerName;

	void OnResponseCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful);
		
};
