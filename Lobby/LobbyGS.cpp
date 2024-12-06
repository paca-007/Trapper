// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGS.h"
#include "Net/UnrealNetwork.h"
#include "Kismet/GameplayStatics.h"
#include "LobbyPC.h"
#include "LobbyWidgetBase.h"
#include "TrapperGameInstance.h"

void ALobbyGS::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ALobbyGS, LeftTime);
}

void ALobbyGS::OnRep_LeftTime()
{
	ALobbyPC* PC = Cast<ALobbyPC>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (PC && PC->LobbyWidgetObject)
	{
		PC->LobbyWidgetObject->SetPublicMessage(LeftTime);
	}

	if (LeftTime == 0)
	{
		PC->ShowLoading();  // �������� �ε� �г��� ���� ���� RPC ȣ��
	}
}