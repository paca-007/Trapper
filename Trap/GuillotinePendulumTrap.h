// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Trap/TrapBase.h"
#include "Components/TimelineComponent.h"
#include "GuillotinePendulumTrap.generated.h"

/// <summary>
/// ���ƾ ���� ����
/// </summary>
UCLASS()
class TRAPPERPROJECT_API AGuillotinePendulumTrap : public ATrapBase
{
	GENERATED_BODY()

public:
	AGuillotinePendulumTrap();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void Tick(float DeltaTime) override;

public:
	virtual void Demolish() override;
	virtual void OnAttackedByBoss() override;
	FORCEINLINE bool IsMagneticTriggerActivated() const { return bMagneticTriggerActivated; }
	void SetActiveTrap(bool Value/*Ȱ��ȭ ����*/, bool FirstMagneticTriggerDirection /*ù ��° ���׳�ƽ Ʈ���� ��������*/);
	void SetEnableCanAttack();
	void TickSwing();
	FORCEINLINE AActor* GetActivatingPlayer() const { return ActivatingPlayer; }
	void AllMaterialBlue();
	void AllMaterialRed();
	void AllMaterialGray();
	bool IsCanInstall() const;
	void SetAllMaterialOriginal();
	void DemolishGuillotine();
	void SetMapmaker(bool IsAlive);

	void ShowInstallableGuillotine();
	void SetHiddenMeshes(bool IsHidden);

	void SetTrapSnapTrigger(class ATrapSnapTrigger* TSTrigger);
	 TWeakObjectPtr<class ATrapSnapTrigger> GetTrapSnapTrigger() const { return TrapSnapTrigger;}

	FORCEINLINE bool IsInstalled() const { return bInstallGuillotine; };
	FORCEINLINE void SetInstalled(bool Value) { bInstallGuillotine = Value; }

	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }
	FORCEINLINE UStaticMeshComponent* GetBeam() const { return Beam; }
	FORCEINLINE UStaticMeshComponent* GetPanel1() const { return Panel1; }
	FORCEINLINE UStaticMeshComponent* GetPanel2() const { return Panel2; }

protected:
	UFUNCTION()
	void OnHitArrow(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UFUNCTION()
	void OnOverapCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult);

private:
	virtual void HitRayAndChangeCollaborationPartsMaterial(class ATrapperPlayer* TrapperPlayer) override;
	virtual void ChangeCollaborationPartsRestoreOriginalMaterial(class ATrapperPlayer* TrapperPlayer) override;
	UPROPERTY(Replicated)
	TWeakObjectPtr<class ATrapperPlayer> TriggerPlayer;
	UPROPERTY(Replicated)
	uint8 bOnPendulum : 1 = true;

public:
	uint8 bIsWrapping : 1 = true;

private:
	void CalculatePendulum(float& NewRoll, float& SinValue, float& DampingFactor);
	void CalculateDamage(const float& NewRoll);
	void OutHitActor(AActor* OtherActor);
	void SetActivatingPlayer(AActor* OtherActor);
	void SetMeshMaterialBlue(bool Value, ATrapperPlayer* TrapperPlayer);
	void SetPanel1MaterialBlue(bool Value, ATrapperPlayer* TrapperPlayer);
	void SetPanel2MaterialBlue(bool Value, ATrapperPlayer* TrapperPlayer);
	void ClearTriggerTimer();
	void PlayMagneticSound();
	void MoveSoundCallback();
	void ReAttackTimeCallback();
	TMap<AActor*, FTimerHandle> HitActorTimers;

	void ClearTriggerTimerCallback();

	void TempSorry();

public:
	// For Niagara
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Niagara")
	uint8 bNiagaraDeactivate : 1;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "Niagara")
	TObjectPtr<class UNiagaraComponent> NiagaraComponentSand;

private:
	UPROPERTY(Replicated)
	TWeakObjectPtr<class ATrapperPlayer> FirstPlayer;

	uint8 bFirstPackaged : 1 = true;

	TWeakObjectPtr<class ATrapSnapTrigger> TrapSnapTrigger;
	uint8 bInstallGuillotine : 1 = false;

	TObjectPtr<class USoundWave> CurrentHitSound;
	TObjectPtr<class USoundWave> CurrentMoveSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> MagneticSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> MoveSound1;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> MoveSound2;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> HitSound1;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> HitSound2;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	TObjectPtr<class USoundWave> HitSound3;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UStaticMeshComponent> Panel1;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UStaticMeshComponent> Panel2;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UStaticMeshComponent> Beam;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterial> MaterialBlue;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterial> MaterialRed;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterial> MaterialGray;

	UPROPERTY(EditAnywhere, Category = "TrapEffect")
	TObjectPtr<class UNiagaraSystem> SandNiagara;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class USphereComponent> TriggerSphere;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UNiagaraSystem> RedNiagara;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UNiagaraSystem> BlueNiagara;

	/*UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UNiagaraComponent> ActivateNiagara;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UNiagaraSystem> ActivateNiagara1;*/

	// Ʈ�� ��Ȱ��ȭ �ð� (��Ÿ��)
	UPROPERTY(EditAnywhere, Category = "Trap")
	float ReEnableTime;

	// �������� ���� ���Ͱ� �ٽ� �������� ���� �� �ִ� �ð�
	UPROPERTY(EditAnywhere, Category = "Trap")
	float ReAttackTime;

	// �ڼ�ȭ��� Ȱ��ȭ �Ǿ�����
	uint8 bMagneticTriggerActivated : 1;

	uint8 bMeshMagneticTrigger : 1;

	uint8 bPanel1MagneticTrigger : 1;

	uint8 bPanel2MagneticTrigger : 1;

	TObjectPtr<AActor> MeshMagneticTriggerActivatingPlayer;
	TObjectPtr<AActor> Panel1MagneticTriggerActivatingPlayer;
	TObjectPtr<AActor> Panel2MagneticTriggerActivatingPlayer;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> MeshOriginalMaterialElement0;
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> MeshOriginalMaterialElement1;
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> MeshOriginalMaterialElement2;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> PanelOriginalMaterialElement0;
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> PanelOriginalMaterialElement1;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> BeamOriginalMaterialElement0;
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterialInterface> BeamOriginalMaterialElement1;

	// Ʈ���� Ȱ��ȭ �ƴ���
	uint8 bIsActiveTrap : 1;

	// Ʈ���� Ȱ��ȭ�� ���� �ð�
	float ActivateTrapTime;

	// ��ߵ� Ÿ�̸� �ڵ�
	FTimerHandle ReEnableTimerHandle;

	// ����� Ÿ�̸� �ڵ�
	FTimerHandle ClearTriggerTimerHandle;

	// ���� ȯ�� ���� ù ��° ���׳�ƽ Ʈ���� ��������
	uint8 bFirstMagneticTriggerDirection : 1;

	// ������ �ߵ��Ǹ� Ÿ�� �������� �ѹ� ���� ��Ų��.
	uint8 bIsLerpingToTarget : 1;

	// ������ �Ϸ� �ƴ���
	uint8 bLerpCompleted : 1;

	UINT8 bFirstRestrictionActivation : 1;

	// ���ڿ���� ����ϴ� ���� Roll ��
	float LastRoll;

	// ���ڿ ���� ����
	float MaxRoll;

	float InitialDamage = 0.f;

	// ���� ���� ���� �����̳�
	TSet<TObjectPtr<AActor>> OnHitActors;

	// Ʈ���Ÿ� Ȱ��ȭ ��Ų �÷��̾� ����
	TObjectPtr<AActor> ActivatingPlayer;

	TSet<TObjectPtr<AActor>> OverlappingTraps;

	FVector TrapPrevLocation;
	FVector TrapFrameNormal;
	float LaunchSpeed;

	FTransform InitialMeshTransform;

	// For Sound
	float PreviousRollForDetermineSwingDirection;
	float CurrentRollForDetermineSwingDirection;
	uint8 bSoundRight : 1;
	uint8 bPlayMoveSound : 1;
	float Volume;
	// WPQKFWHA
	uint8 bSoundChangeHit2 : 1;
	uint8 bSoundChangeHit1 : 1;

	uint8 bCanHit = true;

	TWeakObjectPtr<AController> TriggeredByController;
	uint8 bCheckKillCount : 1 = false;

	UPROPERTY(EditAnywhere, Category = "GC")
	TSubclassOf<class AActor> BeamGC;

	UPROPERTY(EditAnywhere, Category = "GC")
	TSubclassOf<class AActor> MeshGC;

	UPROPERTY(EditAnywhere, Category = "GC")
	TSubclassOf<class AActor> BeamSmallGC;

	UPROPERTY(EditAnywhere, Category = "GC")
	TSubclassOf<class AActor> MeshSmallGC;
	

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSpawnGC();

	/// RPC --------------------------------------------------------
public:
	// ȯ�� ���Ϳ����� ����ϱ⿡ public
	// ���� Ŭ�� ��� ���ڿ ����
	// �浹 ó���� ���������� 
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetTrapActive(bool Value1, bool Value2);

private:

	// ����Ʈ ��Ƽĳ��Ʈ
	/*UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCActivateEffectt(const FVector& ImpactPoint);*/

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetActivingPlayer(AActor* OtherActor);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSpawnNiagaraSystem(bool IsServer, const FVector& ImpactPoint);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetMeshMaterialBlue(bool Value, ATrapperPlayer* TrapperPlayer);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetPanel1MaterialBlue(bool Value, ATrapperPlayer* TrapperPlayer);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetPanel2MaterialBlue(bool Value, ATrapperPlayer* TrapperPlayer);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetMeshMaterialOriginal(ATrapperPlayer* TrapperPlayer);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetPanel1MaterialOriginal(bool Value, ATrapperPlayer* TrapperPlayer);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetAllMaterialOriginal();

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCPlayHitSound();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCAttachPlayerPing(uint32 ObjectID);
};


//ActivateTrapTime += GetWorld()->GetDeltaSeconds();
//
//// ���� ȸ������ �������� ���� ����
//float CurrentRoll = GetActorRotation().Roll;
//
//// �ִ� ȸ���� ����
//// Sin �Լ��� �̿��� ������ ���
//float TargetRoll = 0.f;
//float SinValue = 0.f;
//if (InitialRoll > 0.f)
//{
//	TargetRoll = 70.f;
//	SinValue = FMath::Sin(ActivateTrapTime * 3) * (TargetRoll - InitialRoll);
//}
//else if (InitialRoll < 0.f)
//{
//	TargetRoll = -70.f;
//	SinValue = FMath::Sin(ActivateTrapTime * 3) * (TargetRoll - InitialRoll);
//}
//else
//{
//	SinValue = FMath::Sin(ActivateTrapTime * 3);
//}


// ù ��° ���׳�ƽ Ʈ���� ������ �ƴ϶�� �ݴ�� ����
	/*if (!bFirstMagneticTriggerDirection)
	{
		SinValue *= -1;
	}*/