// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Trap/Utillity/TrapEnums.h"
#include "Trap/Utillity/TrapParts.h"
#include "TrapBase.generated.h"


DECLARE_MULTICAST_DELEGATE(FOnTrapActivatedDelegate)

/// <summary>
/// ��� Ʈ���� ��ӹ޴� ���̽� Ŭ����
/// </summary>
UCLASS()
class TRAPPERPROJECT_API ATrapBase : public AActor
{
	GENERATED_BODY()

public:
	ATrapBase();

	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FORCEINLINE void SetTrapType(ETrapType Type) { TrapType = Type; }
	FORCEINLINE void SetVolatile(bool Value) { bVolatile = Value; }
	void SetEffectParticle(class UParticleSystem* Value);
	FORCEINLINE bool CanAttack() const { return bCanAttack; }
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return Mesh; }

	void SetInstallCost(uint32 Cost) { InstallCost = Cost; }
	int32 GetInstallCost() const { return InstallCost; }

	FORCEINLINE bool IsWeckage() const { return bWreckage; }
	void AimFeedback(AActor* OtherActor);
	virtual void ReInstall() {};
	void UpgradeDamage(float DamageIncreaseDecreaseRate);
	virtual void OnAttackedByBoss() {}
	virtual void Demolish() {};

	FORCEINLINE bool IsOutline() const { return bOutline; }
	FORCEINLINE void SetOutline(bool Value) { bOutline = Value; }

	void SetDataTableInfo(float DataInstallCost, float DataDamage, float DataIncreaseDamage, float DataSpeed, float DataIncreaseSpeed,
		float DataStrength, float DataIncreaseStrength, float DataDuration);

	FORCEINLINE bool IsInstalled1P() const { return bInstalled1P; }
	FORCEINLINE void SetIsInstalled1P(bool Is1P) { bInstalled1P = Is1P; }


	// RayMaterial : M_Blade
	virtual void HitRayAndChangeCollaborationPartsMaterial(class ATrapperPlayer* TrapperPlayer) {};
	virtual void ChangeCollaborationPartsRestoreOriginalMaterial(class ATrapperPlayer* TrapperPlayer) {};
	uint8 bChangeRayMaterial : 1 = true;

protected:
	void OnTrapActivatedBroadcast();

	// Multikill
	void CheckKillCount(AController* EventInstigator, AActor* DamageCauser);
	void ResetKillCount(AActor* DamageCauser);
	void CheckAndResetKillCount(AController* EventInstigator, AActor* DamageCauser);
	void CheckKillCountCollaboration(AActor* DamageCauser);
	void CheckAndResetKillCountCollaboration(AActor* DamageCauser);

	void ChangeAliveMapMarker();
	void ChangeWreckageMapMarker();
	void ChangeWreckageMaterial(UStaticMeshComponent* WreckageMesh);

	template<typename... Args>
	void ChangeWreckageMaterials(UStaticMeshComponent* FirstMesh, Args... OtherMeshes);

public:
	// tutorial
	UPROPERTY(EditInstanceOnly, Category = "Tutorial")
	uint8 bTutorialTrap : 1;

protected:
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class USceneComponent> DummyRoot;
	// WPQKFWHA// WPQKFWHA// WPQKFWHA// WPQKFWHA
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UStaticMeshComponent> Mesh;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UBoxComponent> Trigger;

	/*UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class USphereComponent> DemolishTrigger;*/

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UParticleSystemComponent> EffectSystem;

	TObjectPtr<class UParticleSystem> EffectParticle;

	// Ʈ�� ������ 
	UPROPERTY(EditAnywhere, Category = "Trap")
	float Damage = 50.f;
	float IncreaseDamage = 0;

	UPROPERTY(Replicated)
	float Speed = 0;
	UPROPERTY(Replicated)
	float IncreaseSpeed = 0;

	float Strength = 0;
	float IncreaseStrength = 0;

	float Duration = 0;

	// ���� ������ ��������
	uint8 bCanAttack : 1;

	// ö�ŵ� ��������
	uint8 bWreckage : 1;

	// �� ��Ŀ
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "MapMarker")
	TObjectPtr<class UMapMarkerComponent> MapMarkerwpqkfwpqkf;

	// ���� ���׸��� 
	UPROPERTY(EditAnywhere, Category = "Material")
	TObjectPtr<class UMaterialInterface> WreckageMaterial;

	UPROPERTY(EditAnywhere, Category = "Material")
	TObjectPtr<class UMaterialInterface> MaterialRay;

	float DamageRate = 1;

	uint8 bOutline : 1 = false;

	TWeakObjectPtr<class ATrapperGameState> TrapperGameState;

	uint8 bInstalled1P : 1 = false;

	/// ���ø����̼� -----------------------------------------------
	// Ʈ�� Ÿ��
	UPROPERTY(Replicated, EditAnywhere, Category = Trap)
	ETrapType TrapType;

	// ��ȸ��, �ݺ��� ����
	UPROPERTY(Replicated, EditAnywhere, Category = Trap)
	uint8 bVolatile : 1;

	UPROPERTY(Replicated, EditAnywhere, Category = Trap)
	int32 InstallCost;

	/// ��������Ʈ ----------------------------------------------------
public:
	FOnTrapActivatedDelegate OnTrapActivated;
};

template<typename... Args>
void ATrapBase::ChangeWreckageMaterials(UStaticMeshComponent* FirstMesh, Args... OtherMeshes)
{
	ChangeWreckageMaterial(FirstMesh);
	(ChangeWreckageMaterial(OtherMeshes), ...);
}
