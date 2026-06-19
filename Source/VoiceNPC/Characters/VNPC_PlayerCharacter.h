// Psycho Games 2026. All rights reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "VoiceNPC/Characters/VNPC_BaseCharacter.h"
#include "Logging/LogMacros.h"
#include "VNPC_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
class UInputAction;
class UVNPCAIChatComponent;
struct FInputActionValue;	

DECLARE_LOG_CATEGORY_EXTERN(LogTemplateCharacter, Log, All);

UCLASS(config=Game)
class AVNPC_PlayerCharacter : public AVNPC_BaseCharacter
{
	GENERATED_BODY()

	/** Camera boom positioning the camera behind the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* CameraBoom;

	/** Follow camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	UCameraComponent* FollowCamera;
	
	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputMappingContext* DefaultMappingContext;

	/** Jump Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* JumpAction;

	/** Move Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* MoveAction;

	/** Look Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* LookAction;

	/** Chat Input Action */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	UInputAction* ChatAction;

public:
	AVNPC_PlayerCharacter();

	void OnChatKeyPressed(const FInputActionValue& Value);

	UFUNCTION(BlueprintCallable, Category = "Voice NPC | AI Chat")
	void TalkToTargetNPC(const FString& PlayerMessage);

	UFUNCTION(BlueprintCallable, Category = "AI Chat")
	void CloseChatUI();

	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	/** Returns FollowCamera subobject **/
	FORCEINLINE class UCameraComponent* GetFollowCamera() const { return FollowCamera; }

protected:

	/** Called for movement input */
	void Move(const FInputActionValue& Value);

	/** Called for looking input */
	void Look(const FInputActionValue& Value);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Voice NPC | AI Chat")
	UVNPCAIChatComponent* ChatComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Voice NPC | AI Chat")
	AActor* CurrentTargetNPC;

	UPROPERTY(EditAnywhere, Category = "Voice NPC | AI Chat")
	float InteractionDistance = 300.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Voice NPC | AI Chat |UI")
	TSubclassOf<UUserWidget> ChatWidgetClass;

	UPROPERTY()
	UUserWidget* ActiveChatWidget;

	virtual void NotifyControllerChanged() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};

