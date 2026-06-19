// Psycho Games 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "VNPC_ChatWidget.generated.h"

class UScrollBox;
class UTextBlock;
class UEditableTextBox;
class AVNPC_PlayerCharacter;

UCLASS()
class VOICENPC_API UVNPC_ChatWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, Category = "Chat UI")
	void SetupWidgetReferences(AVNPC_PlayerCharacter* InPlayerCharacter);
	
protected:
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* ChatScrollBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* TXT_ChatHistory;

	UPROPERTY(meta = (BindWidget))
	UEditableTextBox* INP_PlayerPrompt;

	UPROPERTY(BlueprintReadOnly, Category = "Chat UI")
	AVNPC_PlayerCharacter* OwningPlayerChar;

	UFUNCTION()
	void HandleTextCommitted(const FText& Text, ETextCommit::Type CommitMethod);

	UFUNCTION()
	void HandleAIResponse(const FString& NPCName, const FString& ResponseText);

	UFUNCTION()
	void HandleAIError(const FString& ErrorMessage);
	
};
