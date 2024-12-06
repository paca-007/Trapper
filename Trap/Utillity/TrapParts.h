// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Trap/Utillity/TrapEnums.h"
#include "TrapParts.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FTrapParts : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Name = "";

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMesh> PreviewMesh = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMesh> PreviewRange = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMesh> PreviewCouple = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ADecalActor> PreviewRangeDecal = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> Effect = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class ATrapBase> ClassType = nullptr;

	// ��ġ ���
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 InstallCost = 0;

	// Ʈ���̽� ä��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TEnumAsByte<ETraceTypeQuery> TraceChannel = ETraceTypeQuery::TraceTypeQuery1;

	// Ʈ�� Ÿ��
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETrapType Type = ETrapType::None;

	// ��ȸ��, �ݺ��� ����
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bVolatile : 1 = false;

	// ���� �������� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bCanSnap : 1 = false;

	// õ�� �������� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsCeling : 1 = false;

	// �� �������� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsWall : 1 = false;

	// Ŀ������ üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsCouple : 1 = false;

	// ������ �������� �ִ��� üũ
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsPreviewRange : 1 = false;
};