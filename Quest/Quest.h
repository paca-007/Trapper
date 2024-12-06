// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Data/EventCode.h"
#include "Quest.generated.h"

USTRUCT()
struct FQuest
{
	GENERATED_USTRUCT_BODY()

public:
	FQuest() {}
	void Initialize(int32 InQuestCode, FString InTitle, FString InDescription, 
		int32 InGoalCount1P, int32 InGoalCount2P, FVector InEffectPosition,
		TArray<int32> InQuestActorCode, FString InTutorialText);

	// ����Ʈ �ڵ�
	int32 QuestCode;

	// ���� ����Ʈ ����
	uint8 bChangeMainQuest : 1 = false;

	// ���� & ����
	FString Title;
	FString Description;
	FString TutorialText;

	// �ؾ��ϴ� �ൿ�� Ƚ��
	int32 Count1P = 0;
	int32 Count2P = 0;
	int32 GoalCount1P = 0;
	int32 GoalCount2P = 0;
	int32 TotalGoalCount = 0;

	// ����Ʈ�� �������� �ƴҶ��� üũ�ؾ��� ��
	uint8 bIsAlwaysChecking : 1 = false;

	// Ȱ��ȭ�ؾ� �� ���� �ڵ�
	TArray<int32> QuestActorCode;

	// ����Ʈ ����Ʈ ��ġ
	FVector EffectPosition = FVector();

	// ����Ʈ ����ó����
	int32 ExceptionCode = 0;

	// �̺�Ʈ �߻�
	TArray<ETrapperEventCode> SendEventCode;
};