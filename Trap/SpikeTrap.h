// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trap/TrapBase.h"
#include "Components/TimelineComponent.h"
#include "SpikeTrap.generated.h"

/// <summary>
/// ���� ����
/// </summary>
UCLASS()
class TRAPPERPROJECT_API ASpikeTrap : public ATrapBase
{
	GENERATED_BODY()

public:
	ASpikeTrap();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;
	// WPQKFWHA// WPQKFWHA// WPQKFWHA// WPQKFWHA// WPQKFWHA// WPQKFWHA
public:
	virtual void Demolish() override;
	virtual void OnAttackedByBoss() override;

protected:
	UFUNCTION()
	void OnOverlapBeginCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

	UFUNCTION()
	void OnOverlapEndCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnOverlapBeginCharacterHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

private:
	void Attack();
	void SpikeDownTimerCallback();
	void ReAttackTimerCallback();

private:
	UFUNCTION()
	void HandleSpikeProgress(float Value);

	UFUNCTION()
	void OnSpikeTimelineFinished();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> SpikeUpSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> SpikeDownSound;

	// ������ũ �޽�
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UStaticMeshComponent> SpikeMesh;

	FVector InitialSpikeLocation;

	// Ÿ�̸� �ڵ�
	FTimerHandle ReAttackTimerHandle;
	FTimerHandle SpikeDownTimerHandle;

	// �ٽ� ���� ������ �ð� (��Ÿ��)
	UPROPERTY(EditAnywhere, Category = "Trap")
	float ReAttackTime;

	// �ٽ� ���� ������ �ð� (��Ÿ��)
	UPROPERTY(EditAnywhere, Category = "Trap")
	float SpikeUpAndPause;

	// ���� Ʈ���ſ� ������ �Ǿ� �ִ���
	uint8 bOverlappingTrigger : 1;

	// ���� �ߵ��� ���͸�
	TSet<TObjectPtr<AActor>> OverlappingMonsters;
	
	TSet<TObjectPtr<AActor>> HitCharacters;

	// ���ð� ���� �ڴ� �ִϸ��̼��� ���� Ÿ�Ӷ���
	FTimeline SpikeTimeline;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UCurveFloat> SpikeRiseCurve;

	uint8 bIsSpikeTimeline : 1;
	uint8 bIsSpikeUp : 1;

	uint8 bCanActive : 1;

	TWeakObjectPtr<AController> OwnerController;

	UPROPERTY(EditAnywhere, Category = "GC")
	TSubclassOf<class AActor> SpikeGC;

	/// RPC --------------------------------------------------------
	/*UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCActivateEffect();*/

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCSpikeUpSound();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCSpikeDownSound();

	/*UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCAttack();*/

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSpawnGC();
};
