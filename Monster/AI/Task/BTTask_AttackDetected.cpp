// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/Task/BTTask_AttackDetected.h"

#include "BehaviorTree/BlackboardComponent.h"
#include "Monster/BaseMonster.h"
#include "Monster/AI/BaseMonsterAIController.h"
#include "Monster/DetectedMonster.h"

EBTNodeResult::Type UBTTask_AttackDetected::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	TObjectPtr<ADetectedMonster> Monster = Cast<ADetectedMonster>(OwnerComp.GetAIOwner()->GetPawn());

	if (IsValid(Monster))
	{
		//�÷��̾ ���� ���� ���� ������
		if (Monster->MonsterState == EMonsterStateType::IsAttack || 
			Monster->MonsterState == EMonsterStateType::IsTowerAttack)
		{
			if (IsValid(Monster->AttackkActionMontage1) && IsValid(Monster->AttackkActionMontage2))
			{
				Monster->AttackDetectedMontage();
				Monster->MonsterState = EMonsterStateType::IsAttackStart;
				
			}
		}
	}

	return EBTNodeResult::Succeeded;
}
