// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trap/TrapBase.h"
#include "PlankTrap.generated.h"

/// <summary>
/// ���� ����
/// �ùķ��̼��� �������� �����µ� Ŭ���̾�Ʈ���� �Ҷ� ���ܺ��δ�
/// ������ �ؼ� �ε巴�� �������ϴµ� �ϴ� NetUpdateFrequency �� 500���� �ø�
/// </summary>
UCLASS()
class TRAPPERPROJECT_API APlankTrap : public ATrapBase
{
	GENERATED_BODY()

public:
	APlankTrap();

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Demolish() override;
	virtual void ReInstall() override;
	FORCEINLINE uint8 IsTriggered1P() const { return bTriggered1P; }

protected:
	UFUNCTION()
	void OnHitArrow(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

private:
	void CheckPlankVelocity();
	void DestroyTrap();
	void WreckageActivation();
	void ChangeOriginalMaterial();
	void PlaySound();

private:
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> ActivateSound;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> RingAndRopeOriginalMaterialFirstElement;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> MeshOriginalMaterialFirstElement;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UStaticMeshComponent> RopeMesh;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UStaticMeshComponent> RingMesh;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UNiagaraSystem> ActivateNiagara;

	// ���� ���� ���� �����̳�
	TSet<TObjectPtr<AActor>> OnHitActors;

	// �ùķ��̼� ������
	uint8 bIsSimulate : 1;

	// Ÿ�̸� �ڵ�
	FTimerHandle CheckPlankVelocityTimerHandle;
	FTimerHandle DestroyTrapTimerHandle;

	// Ʈ���� �����ϴ� �Լ� ȣ�� �ð�
	UPROPERTY(EditAnywhere, Category = "Trap")
	float DestroyTrapTime;

	// ������ �ӷ��� üũ�ϴ� �Լ� ȣ�� �ð�
	float CheckPlankVelocityTime;

	// ��ü�� �������� �� �� �ִ� �ּ� �ӷ��� ������ �� (vector.size)
	float StopDamageOfVelocity;

	FTransform ReInstallTransform;

	// Sound
	uint8 bPlayHitSound : 1;

	TWeakObjectPtr<AController> TriggeredByController;

	uint8 bTriggered1P : 1 = false;

	uint8 bActivateNiagara : 1 = false;

	UPROPERTY(EditAnywhere, Category = "GC")
	TSubclassOf<class AActor> PlankGC;
	// WPQKFWHA
	/// RPC --------------------------------------------------------
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCWreckActivation();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetCollisionResponseOfVelocity();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetCollisionResponseOfSimulating();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCActivateNiagara(FVector ImpactPoint);
};
