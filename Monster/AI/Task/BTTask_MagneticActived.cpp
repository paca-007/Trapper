// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster/AI/Task/BTTask_MagneticActived.h"

#include "Monster/BaseMonster.h"
#include "Monster/AI/BaseMonsterAIController.h"

EBTNodeResult::Type UBTTask_MagneticActived::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMenory)
{
	

	Monster = Cast<ABaseMonster>(OwnerComp.GetAIOwner()->GetPawn());

	//�޾ƿ� ��ġ�� �̵�
	//GoToPillar Task

	//2�� ����
	WaitTime = Monster->MonsterPillarTime;
	
	//���� ��ȭ
	//IsStunEnd�� �־ Service���� üũ �� ����
	Monster->MonsterState = EMonsterStateType::IsStunEnd;


	return EBTNodeResult::Succeeded;
}

