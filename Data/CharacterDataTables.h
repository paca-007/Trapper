// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "CharacterDataTables.generated.h"

UENUM()
enum class ECharacterData : uint8
{
	Default			UMETA(DisplayName = "Default"),
	Upgrade			UMETA(DisplayName = "Upgrade"),
};

USTRUCT()
struct FCharacterInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FCharacterInfo()
		: Level()
		, MoveSpeed()
		, MaxHealth()
		, HealthCoolTime()
		, RecoveryDelayTime()
		, HealthRecoveryAmount()
		, ChargeTime()
		, ArrowMinSpeed()
		, ArrowMaxSpeed()
		, NormalArrowMinDamage()
		, NormalArrowMaxDamage()
		, MagneticArrowMinDamage()
		, MagneticArrowMaxDamage()
		, MagneticMoveSpeed()
		, StartMoney()

		, SlowReductionRate()
		, InvincibilityTime()
		, RevivalTime()
	{};

	// ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite) uint8 Level;

	// �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MoveSpeed;

	// �ִ� ü��
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MaxHealth;

	// ü�� ȸ�� ��Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float HealthCoolTime;

	// ȸ���� ���۵Ǵ� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float RecoveryDelayTime;

	// ü�� ȸ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float HealthRecoveryAmount;

	// ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ChargeTime;

	// ȭ�� �ּ� ����ü �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ArrowMinSpeed;

	// ȭ�� �ִ� ����ü �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float ArrowMaxSpeed;

	// �Ϲ� ȭ�� �ּ� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float NormalArrowMinDamage;

	// �Ϲ� ȭ�� �ִ� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float NormalArrowMaxDamage;

	// �ڼ� ȭ�� �ּ� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MagneticArrowMinDamage;

	// �ڼ� ȭ�� �ִ� ���ݷ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MagneticArrowMaxDamage;

	// �ڼ� �̵� �ӵ�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float MagneticMoveSpeed;

	// ���� ���� ��ȭ
	UPROPERTY(EditAnywhere, BlueprintReadWrite) int32 StartMoney;

	// ���ο� �̵� �ӵ� ������
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float SlowReductionRate;

	// �ǰ� �� ���� �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float InvincibilityTime;

	// ��Ȱ �ð�
	UPROPERTY(EditAnywhere, BlueprintReadWrite) float RevivalTime;
};

UCLASS()
class TRAPPERPROJECT_API ACharacterDataTables : public AActor
{
	GENERATED_BODY()
};
