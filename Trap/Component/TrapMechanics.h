// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Trap/Utillity/TrapParts.h"
#include "Trap/Utillity/TrapInfo.h"
#include "InputActionValue.h"
#include "TrapMechanics.generated.h"

UCLASS(Blueprintable, ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRAPPERPROJECT_API UTrapMechanics : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UTrapMechanics();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	FORCEINLINE bool IsTrapSelectMode() const { return bSelectMode; }
	void BlockSelectTrap();
	void UnBlockSelectTrap();
	void DemolishReInstallRaycastLoop();
	FORCEINLINE bool IsPlayDemolishRaycast() const { return bPlayDemolishRaycast; }
	void UpgradeCost(float CostIcreaseDecreaseRate);

private:
	/// ��� �Լ� ------------------------------------------------
	// ��ǲ ����
	void SetupInputComponent();

	// ��ġ ��� �߿� ���̸� ���� ������ �޽��� ���� ���� ����
	void PreviewLoop();

	// ��ġ ��� ����
	void EnterInstallationMode();

	// ��ġ ��� ����
public:
	void ReleaseInstallationMode();
private:
	void ReleaseInstallationModeToPlace();

	// ���� ��� ��ǲ
	void EnterSwitchSelectMode();
public:
	void ExitSwitchSelectMode();
private:
	// ���� ��� ����
	void EnterSelectMode();
public:
	// ���� ��� ����
	void ReleaseSelectMode();
private:
	// ������ �޽� ����
	void SetPreviewMesh();

	// ������ �޽� ����();
	void ReleasePreviewMesh();

	// ������ �޽� ���׸��� ����();
	void SetPreviewMeshMaterial(bool bMaterialBlue, class ATrapSnapTrigger* TSTrigger);

	// ������ �޽� ȸ��
	void RotatePreviewMesh(const FInputActionValue& Value);

	//// ������ �޽� ��ü
	//void ChangePreviewMesh();
	//void PermissionChangePreviewMesh();

	// Ʈ�� ��ġ
	void LeftMouseClick();
	void PlaceTrap();
	bool PermissionPlaceTrap();

	// Ʈ���̽� ä�ο� �ش��ϴ� �ݸ��� ä�� ��ȯ
	ECollisionChannel ConvertTraceTypeToCollisionChannel(ETraceTypeQuery TraceChannel);

	// ���� Ʈ���Źڽ��� ���̰� ��Ҵ��� üũ
	bool DetectSnapTriggerBoxes(const FHitResult& HitResult);

	// ���ƾ ����
	bool DetectSnapTriggerBox(const FHitResult& HitResult);

	void CheckSnabGuillotineTrap(FHitResult& HitResult, FQuat& CameraRotation);

	// ������ �ߺ� �˻� (��ġ �������� üũ)
	bool CheckForOverlap();

	bool CheckForOverlapSpearWall();

	// ���� ������ ���缭 ���� ���� ����
	void AlignToSurface();

	// �÷��̾�� ��ġ ��� ���� ����
	void NotifyPlayerInstallationMode() const;

	// ������޽�, Ŀ�� Ʈ������ ����
	void AllPreviewSetTransform();

	// ������ Ʈ�� �ʱ�ȭ
	void InitializeTrap(ATrapBase* Trap);

	// õ�� Ʈ���� ��� �߰� üũ ���
	bool CheckCellingTrap(FHitResult& HitResult, FVector& StartLocation, FVector& EndLocation, FVector& CameraForwardVector, FCollisionQueryParams& CollisionParams, bool& bHasHit);

	// ���� Ʈ���� ��� �߰� üũ ���
	void CheckSnapTrap(FHitResult& HitResult, bool& bDetectSnabTrigger, FQuat& CameraRotation);

	// RangeMesh ���������� üũ. (������)
	void CheckServerBroadCastSetHiddenRange(bool IsServer);

	// RangeMesh Ʈ������ ����
	void CalculateRangeMeshTransform();

	// ���ƾ ���� ������ ��ġ ����
	bool CheckForOverlapExclusivehGuillotine();

	// ���� ö��
	void DemolishTrap();
	void DestroyFocusTrap();

	// ���� �缳ġ
	void ReInstallTrap();

	void PlaySoundInstallTrap();

	void SafeNormalizeQuat();

	void ClientDestroyPreviweMeshTimerCallback();
	void AnimMulticastTimerCallback();
	void AnimServerTimerCallback();

	void IncreaseTrapHudNum(ETrapType Type, bool bInstall);
	void DecreaseTrapHudNum(ETrapType Type, bool bInstall);

public:
	UPROPERTY(EditAnywhere, Category = "Oil")
	float OilRange = 10.f;

	UPROPERTY(EditAnywhere, Category = "Celling Ray")
	float FirstCellingRay = 1500;

	UPROPERTY(EditAnywhere, Category = "Celling Ray")
	float SecondCellingRay = 2000;

	UPROPERTY(EditAnywhere, Category = "Celling Ray")
	float ThirdCellingRay = 625;

	UPROPERTY(EditAnywhere, Category = "Celling Ray")
	float FourthCellingRay = 1250;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<class UDataTable> TrapPartsDataTable;

	UPROPERTY(EditDefaultsOnly, Category = "Data")
	TObjectPtr<class UDataTable> TrapDataTable;

	/// Input Action ------------------------------------------------
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> EnterInstallationModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> ExitInstallationModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> RealeseInstallationModeAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> LeftMouseClickAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> RotatePreviewMeshAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> DemolishAction;

	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	//TObjectPtr<class UInputAction> ShowMeTheMoneyAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> ShowScoreHUDAction;

	/*UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> UpdateScoreHUDAction;*/

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	TObjectPtr<class UInputAction> SpawnMonsterSpikeTrapsAction;

	/// ������ �޽� ���׸��� ------------------------------------------------
	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterial> PreviewMaterialBlue;

	UPROPERTY(EditAnywhere, Category = "Trap")
	TObjectPtr<class UMaterial> PreviewMaterialRed;

	///  ------------- Sound  -------------
	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* SelectOverSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* SelectDisableSound = nullptr;

	UPROPERTY(EditDefaultsOnly, Category = "Sound")
	USoundBase* InstallFailSound = nullptr;

	/// �ڼ� ��� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Trap")
	TSubclassOf<class AActor> CheckClapPath;

	/// ��� ���� ------------------------------------------------
protected:
	// ���� �Ÿ� (������ġ ~ ������ġ + MaxRayDistance)
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RayDistance")
	float MaxInstallRayDistance = 500.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RayDistance")
	float MaxDemolishReInstallRayDistance = 400.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "RayDistance")
	float SpearLeftRightRayDistance = 3000.f;

private:
	UPROPERTY()
	TObjectPtr<class ATrapperPlayer> Player;

	UPROPERTY()
	TObjectPtr<class ATrapperPlayerController> PlayerController;

	UPROPERTY()
	TObjectPtr<class UCameraComponent> FollowCamera;

	// Ʈ�� ���� ���̺�
	UPROPERTY(VisibleAnywhere, Category = "Trap")
	TArray<FTrapParts> TrapPartsArray;

	TArray<FTrapInfo> TrapDataArray;

	// ������ �޽� �����̼�
	FTransform PreviewMeshTransform;
	FTransform PreviewCoupleTransform;
	//FTransform PreviewRangeTransform;
	FRotator PreviewMeshRotator;


	// bool ��
public:
	uint8 bInstallationMode : 1;

private:
	uint8 bSelectMode : 1;
	uint8 bCanSnap : 1;
	uint8 bResetTrapPartsTableIndex : 1;
	uint8 bCanInstall : 1;
	uint8 bAlignToSurface : 1;
	uint8 bCanSelect : 1;
	uint8 bCanRotationGuillotine : 1;
	uint8 bBlockSelectTrap : 1;
	uint8 bPlaceTrap : 1;
	uint8 bPlayDemolishRaycast : 1;
	uint8 bHitRayCanReInstall : 1;
	uint8 bCanInstallCouple : 1;

	uint8 bFirstArch : 1 = false;
	uint8 bSecondArch : 1 = false;

	// Ʈ���̽� ä��
	ECollisionChannel CollisionChannel = ECollisionChannel::ECC_Visibility;

	// Ʈ�� ���� ȯ�� ����
	TObjectPtr<class ATrapSnabEnviromentBase> TrapSnapEnviromentActor;

	UPROPERTY(Replicated)
	TObjectPtr<class ATrapSnapTrigger> TrapSnapTrigger;

	// Ÿ�̸� �ڵ�
	FTimerHandle PreviewLoopTimerHandle;
	FTimerHandle ClientDestroyPreviweMeshTimerHandle;
	FTimerHandle DemolishReInstallRaycastLoopTimerHandle;

	// ���� Ÿ�Ը��� ����� �������� ���� ���� ����� ���� ��ġ ������
	FVector GuillotinePendulumOffset = { 0.f,0.f,500.f };

	// �ڼ� ���� ������
	FVector ClapOffset = { 68.f,0.f,0.f };

	// ���� ��ġ ���
	int32 ItemCost = 0;

	// ȭ���� ���̾ư������� �������Ʈ Ŭ����
	TObjectPtr<UClass> LoadedBPGunpowderNiagaraClass;


	// Ŀ�� ���� ù��° ��ġ �� �ӽ� ����
	UPROPERTY(Replicated)
	TObjectPtr<class UStaticMeshComponent> PreviewFirstCoupleMeshTemp;

	float CostRate = 1;

	UPROPERTY(Replicated)
	TArray<TSoftObjectPtr<class ATrapSnapTrigger>> TrapSnapTriggerArray;
private:
	/// ��ġ UI ���� -----------------------------------------------
	FTimerHandle UpdateHoverCheckTimer;
	void CheckOnHovered();
	//UPROPERTY(ReplicatedUsing = OnRep_HoveredTrapType)
	ETrapType HoveredTrapType = ETrapType::None;
	int32 LastItemBoxCount = 0;
	//UFUNCTION()
	//void OnRep_HoveredTrapType();

private:
	/// ���ø����̼� -----------------------------------------------

	UPROPERTY(EditAnywhere, Category = "Trap", ReplicatedUsing = OnRep_PreviewMesh)
	TObjectPtr<class UStaticMeshComponent> PreviewMesh;

	/*UPROPERTY(EditAnywhere, Category = "Trap", ReplicatedUsing = OnRep_PreviewRange)
	TObjectPtr<class UStaticMeshComponent> PreviewRange;*/

	UPROPERTY(EditAnywhere, Category = "Trap", ReplicatedUsing = OnRep_PreviewCouple)
	TObjectPtr<class UStaticMeshComponent> PreviewCouple;

	UPROPERTY(EditAnywhere, Category = "Trap", ReplicatedUsing = OnRep_PreviewRangeDecal)
	TObjectPtr<class ADecalActor> PreviewRangeDecal;

	UPROPERTY(EditAnywhere, Category = "Trap", ReplicatedUsing = OnRep_PreviewNiagara)
	TObjectPtr<class AActor> PreviewNiagara;

	UPROPERTY(ReplicatedUsing = OnRep_TrapPartsTableIndex, VisibleAnywhere, Category = "Trap")
	uint8 TrapPartsTableIndex = 0;

	UPROPERTY(ReplicatedUsing = OnRep_PreviewMeshRotationYaw)
	float PreviewMeshRotationYaw = 0.f;

	// Ʈ�� ö�� �� �缳ġ �뵵 ��Ŀ�� ���� 
	UPROPERTY(Replicated)
	TObjectPtr<class ATrapBase> FocusTrap;

	TWeakObjectPtr<class ATrapperGameState> TrapperGameState;

	/// On_Rep -----------------------------------------------

	UFUNCTION()
	void OnRep_PreviewMesh();

	/*UFUNCTION()
	void OnRep_PreviewRange();*/

	UFUNCTION()
	void OnRep_PreviewCouple();

	UFUNCTION()
	void OnRep_PreviewNiagara();

	UFUNCTION()
	void OnRep_PreviewRangeDecal();

	UFUNCTION()
	void OnRep_TrapPartsTableIndex();

	UFUNCTION()
	void OnRep_PreviewMeshRotationYaw();

	/// RPC --------------------------------------------------------

	// ������ �޽� ���� �� �ʱ�ȭ
	UFUNCTION(Server, Reliable)
	void ServerRPCSetPreviewMesh(uint8 TableIndex);

	// ������ �޽� Ʈ������ ������Ʈ
	UFUNCTION(Server, Unreliable)
	void ServerRPCUpdatePreviewMeshTransform(FTransform PMTransform, FTransform PCTransform, /*FTransform PRTransform, */float PMRotationYaw);

	// ������ �޽� ���׸��� ������Ʈ
	UFUNCTION(Server, Unreliable)
	void ServerRPCUpdatePreviewMeshMaterial(bool bMaterialBlue, class ATrapSnapTrigger* TSTrigger);

	UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCUpdatePreviewMeshMaterial(bool bMaterialBlue, class ATrapSnapTrigger* TSTrigger);

	//������ �޽� ���� �� ����
	UFUNCTION(Server, Reliable)
	void ServerRPCRealesePreviewMesh(class ATrapSnapTrigger* TSTrigger);

	// ������ �޽� ��ġ
	UFUNCTION(Server, Reliable)
	void ServerRPCPlaceTrap(class ATrapSnabEnviromentBase* ClientTrapSnabEnviromentActor, class ATrapSnapTrigger* ClientTrapSnabTrigger, bool FirstArch, bool SecondArch);

	//// ������ �޽� ��ü (�޽� �ε��� ����)
	//UFUNCTION(Server, Reliable)
	//void ServerRPCChangePreviewMesh();

	UFUNCTION(Server, Reliable)
	void ServerRPCSetHiddenNiagara(bool Value);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetHiddenNiagara(bool Value);

	// ���ƾ
	UFUNCTION(Server, Reliable)
	void ServerRPCSnapGuillotineControl(ATrapBase* SnapGuillotine, bool bIsHidden, bool bMaterialBlue, bool bMaterialGray);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSnapGuillotineControl(ATrapBase* SnapGuillotine, bool bIsHidden, bool bMaterialBlue, bool bMaterialGray);


	UFUNCTION(Server, Reliable)
	void ServerRPCSetFocusTSTrigger(class ATrapSnapTrigger* TSTrigger);

	UFUNCTION(Server, Reliable)
	void ServerRPCSetHiddenPreviewMesh(bool bIsHidden, class ATrapSnapTrigger* TSTrigger);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSetHiddenPreviewMesh(bool bIsHidden);

	// Ʈ�� ö��
	UFUNCTION(Server, Reliable)
	void ServerRPCDestroyFocusTrap(ATrapBase* Trap);

	// Ʈ�� �缳ġ
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCReInstallTrap();

	UFUNCTION(Server, Reliable)
	void ServerRPCReInstallTrap(ATrapBase* Trap);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSnapTriggerSetTrapNullptr(ATrapSnapTrigger* TSTrigger, ATrapBase* Trap);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCGuillotineSpawn(ATrapSnapTrigger* TSTrigger);

	// Ʈ�� ��ġ �ִϸ��̼�
	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCStartInstallAnim();

	UFUNCTION(Server, Reliable)
	void ServerRPCStartInstallAnim();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCEndInstallAnim();

	UFUNCTION(Server, Reliable)
	void ServerRPCEndInstallAnim();

	/*UFUNCTION(NetMulticast, Unreliable)
	void MulticastRPCPlaySoundInstallTrap();*/

	UFUNCTION(Client, Unreliable)
	void ClientRPCPlaySoundInstallTrap();

	void SafeReleasePreviewMesh();

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSafeReleasePreviewMesh();

	/*UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCFirstCoupleInstall(ADecalActor* PRDecal);*/

	UFUNCTION(Server, Reliable)
	void ServerRPCFirstCoupleInstall();

	//UFUNCTION(NetMulticast, Reliable)
	//void MulticastRPCSnapGuillotineMaterial

	UFUNCTION(Server, Reliable)
	void ServerRPCUpdateScoreHUD();

	// �ӽ� ġƮ
	//void ShowMeTheMoney(); // Ű���� 1
	void ShowScoreHUD(); // Ű���� 2
	void UpdateScoreHUD(); // Ű���� 3
	void SpawnMonsterSpikeTraps(); // Ű���� 4

	UFUNCTION(Server, Reliable)
	void ServerRPCSpawnMonsterSpikeTraps(FTransform Transform);

	UFUNCTION(Server, Reliable)
	void ServerUseBone(int32 Count);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastRPCSnapGuillotineControlSorry(ATrapBase* SnapGuillotine, bool bIsHidden, bool bMaterialBlue, bool bMaterialGray);

	UFUNCTION(Server, Reliable)
	void ServerRPCSnapGuillotineControlSorry(ATrapBase* SnapGuillotine, bool bIsHidden, bool bMaterialBlue, bool bMaterialGray);
};
