// Psycho Games 2026. All rights reserved.


#include "VNPCAIChatComponent.h"
#include "Json.h"

// Sets default values for this component's properties
UVNPCAIChatComponent::UVNPCAIChatComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UVNPCAIChatComponent::SendPromptToNPC(const FString& FullSystemPrompt, const FString& PlayerPrompt, const FString& NPCName)
{
	if (PlayerPrompt.IsEmpty()) return;

	CurrentSpeakerName = NPCName.IsEmpty() ? TEXT("NPC") : NPCName;

	FString FullPayload = FString::Printf(TEXT("%s \nUser: %s"), *FullSystemPrompt, *PlayerPrompt);

	FHttpRequestRef Request = FHttpModule::Get().CreateRequest();
	Request->OnProcessRequestComplete().BindUObject(this, &UVNPCAIChatComponent::OnResponseCompleted);
	Request->SetURL(ServerUrl);
	Request->SetVerb(TEXT("POST"));
	Request->SetHeader(TEXT("Content-Type"), TEXT("application/json"));
	Request->SetTimeout(100.0f);

	TSharedPtr<FJsonObject> JsonObject = MakeShareable(new FJsonObject());
	JsonObject->SetStringField(TEXT("prompt"), FullPayload);

	FString PayloadString;
	TSharedRef<TJsonWriter<>> Writer = TJsonWriterFactory<>::Create(&PayloadString);
	FJsonSerializer::Serialize(JsonObject.ToSharedRef(), Writer);

	Request->SetContentAsString(PayloadString);
	Request->ProcessRequest();
}

void UVNPCAIChatComponent::OnResponseCompleted(FHttpRequestPtr Request, FHttpResponsePtr Response, bool bWasSuccessful)
{
	if (!bWasSuccessful || !Response.IsValid())
	{
		OnChatError.Broadcast(TEXT("Failed to connect to FastAPI server."));
		return;
	}

	if (Response->GetResponseCode() == 200)
	{
		FString ResponseBody = Response->GetContentAsString();
		TSharedPtr<FJsonObject> JsonObject;
		TSharedRef<TJsonReader<>> Reader = TJsonReaderFactory<>::Create(ResponseBody);

		if (FJsonSerializer::Deserialize(Reader, JsonObject) && JsonObject.IsValid())
		{
			FString AIResponseText = JsonObject->GetStringField(TEXT("response"));
			OnResponseReceived.Broadcast(CurrentSpeakerName, AIResponseText);
			return;
		}
	}
	OnChatError.Broadcast(FString::Printf(TEXT("Server error. Code: %d"), Response->GetResponseCode()));
}


