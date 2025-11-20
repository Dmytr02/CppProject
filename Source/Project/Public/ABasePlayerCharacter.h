#pragma once

#include "CoreMinimal.h"
#include "ABaseCharacter.h"
#include "InputActionValue.h"
#include "ABasePlayerCharacter.generated.h"

UCLASS()
class PROJECT_API AABasePlayerCharacter : public AABaseCharacter
{
	GENERATED_BODY()

public:
	AABasePlayerCharacter();

	UFUNCTION(BlueprintCallable)
	
	void EquipWeapon(class AWeapon* Weapon);

	virtual void EnableWeaponCollision() override;

	virtual void DisableWeaponCollision() override;

	void StopAnim();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	AWeapon* CurrentWeapon;

protected:
	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void Move(const FInputActionValue& Value);
	void Look(const FInputActionValue& Value);
	void Interact(const FInputActionValue& Value);
	void Attack(const FInputActionValue& Value);
	void Jump(const FInputActionValue& Value);

	virtual void OnJumped_Implementation() override;

	virtual void GetHit_Implementation(int value) override;
	virtual void Death_Implementation() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	class UCameraComponent* FollowCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* MoveAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* LookAction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* InteractAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* AttackAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Input")
	class UInputAction* JumpAction;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input")
	class UInteractionComponent* InteractionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Combat")
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
	UAnimMontage* GetHitMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Audio")
	USoundBase* MySound;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Stamina SP")
	int StaminaCostJump;
};