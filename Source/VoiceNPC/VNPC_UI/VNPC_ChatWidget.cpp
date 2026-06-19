// Psycho Games 2026. All rights reserved.


#include "VNPC_UI/VNPC_ChatWidget.h"
#include "Components/ScrollBox.h"
#include "Components/TextBlock.h"
#include "Components/EditableTextBox.h"
#include "Characters/VNPC_PlayerCharacter.h"
#include "VNPCComponents/VNPCAIChatComponent.h"
#include "Input/Reply.h"

void UVNPC_ChatWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (INP_PlayerPrompt)
	{
		// Bind the Enter key event
		INP_PlayerPrompt->OnTextCommitted.AddDynamic(this, &UVNPC_ChatWidget::HandleTextCommitted);
	}
}

void UVNPC_ChatWidget::SetupWidgetReferences(AVNPC_PlayerCharacter* InPlayerCharacter)
{
	if (!InPlayerCharacter) return;

	OwningPlayerChar = InPlayerCharacter;

	// Find the network chat component on the player and listen to server responses
	auto* ChatComp = OwningPlayerChar->FindComponentByClass<UVNPCAIChatComponent>();
	if (ChatComp)
	{
		ChatComp->OnResponseReceived.AddDynamic(this, &UVNPC_ChatWidget::HandleAIResponse);
		ChatComp->OnChatError.AddDynamic(this, &UVNPC_ChatWidget::HandleAIError);
	}
}

void UVNPC_ChatWidget::HandleTextCommitted(const FText& Text, ETextCommit::Type CommitMethod)
{
	if (CommitMethod == ETextCommit::OnEnter && !Text.IsEmpty())
	{
		FString PlayerString = Text.ToString();

		if (TXT_ChatHistory)
		{
			FString CurrentHistory = TXT_ChatHistory->GetText().ToString();
			FString NewHistory = CurrentHistory + FString::Printf(TEXT("Player: %s\n"), *PlayerString);
			TXT_ChatHistory->SetText(FText::FromString(NewHistory));
		}

		if (ChatScrollBox)
		{
			ChatScrollBox->ScrollToEnd();
		}

		if (OwningPlayerChar)
		{
			OwningPlayerChar->TalkToTargetNPC(PlayerString);
		}

		INP_PlayerPrompt->SetText(FText::GetEmpty());
		INP_PlayerPrompt->SetUserFocus(GetOwningPlayer());
	}
}

void UVNPC_ChatWidget::HandleAIResponse(const FString& NPCName, const FString& ResponseText)
{
	if (TXT_ChatHistory)
	{
		FString CurrentHistory = TXT_ChatHistory->GetText().ToString();
		FString NewHistory = CurrentHistory + FString::Printf(TEXT("%s: %s\n\n"), *NPCName, *ResponseText);
		TXT_ChatHistory->SetText(FText::FromString(NewHistory));
	}

	if (ChatScrollBox)
	{
		ChatScrollBox->ScrollToEnd();
	}
}

void UVNPC_ChatWidget::HandleAIError(const FString& ErrorMessage)
{
	if (TXT_ChatHistory)
	{
		FString CurrentHistory = TXT_ChatHistory->GetText().ToString();
		FString NewHistory = CurrentHistory + FString::Printf(TEXT("[System Error: %s]\n\n"), *ErrorMessage);
		TXT_ChatHistory->SetText(FText::FromString(NewHistory));
	}
}

void UVNPC_ChatWidget::NativeDestruct()
{
	if (OwningPlayerChar)
	{
		auto* ChatComp = OwningPlayerChar->FindComponentByClass<UVNPCAIChatComponent>();
		if (ChatComp)
		{
			ChatComp->OnResponseReceived.RemoveDynamic(this, &UVNPC_ChatWidget::HandleAIResponse);
			ChatComp->OnChatError.RemoveDynamic(this, &UVNPC_ChatWidget::HandleAIError);
		}
	}

	Super::NativeDestruct();
}

FReply UVNPC_ChatWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::T)
	{
		if (OwningPlayerChar)
		{
			OwningPlayerChar->CloseChatUI();
			return FReply::Handled();
		}
	}
	return Super::NativeOnKeyDown(InGeometry, InKeyEvent);
}

