// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trap/TrabSnabEnviroment/TrapSnabEnviromentBase.h"
#include "GuillotineTrapSnabEnviroment.generated.h"


/**
 *
 */
UCLASS()
class TRAPPERPROJECT_API AGuillotineTrapSnabEnviroment : public ATrapSnabEnviromentBase
{
	GENERATED_BODY()

public:
	AGuillotineTrapSnabEnviroment();

	virtual void BeginPlay() override;

public:
	bool IsMagneticTriggerActivated() const;
	void SetWallMagneticTriggerFalse();
	FORCEINLINE bool IsFirstMagneticTriggerActivated() const { return bFirstMagneticTriggerActivated; }
	FORCEINLINE AActor* GetActivatingPlayer() const { return ActivatingPlayer; }

protected:
	UFUNCTION()
	void OnOverlapBeginMagneticArrow(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

private:
	void CheckTrapActivationAndExcute(AActor* OtherActor);
	void SetActivatingPlayer(AActor* OtherActor);


private:
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UBoxComponent> FirstMagneticTrigger;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UBoxComponent> SecondMagneticTrigger;

	// ���׳�ƽ ȭ��� Ȱ��ȭ �ƴ��� ����
	uint8 bFirstMagneticTriggerActivated : 1;
	uint8 bSecondMagneticTriggerActivated : 1;

	// Ʈ���Ÿ� Ȱ��ȭ ��Ų �÷��̾� ����
	TObjectPtr<AActor> ActivatingPlayer;

	/// RPC ------------------------------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetActivingPlayer(AActor* OtherActor);
};
