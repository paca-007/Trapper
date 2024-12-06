// Fill out your copyright notice in the Description page of Project Settings.


#include "Opening/OpeningGM.h"
#include "Opening/OpeningGS.h"
#include "Opening/OpeningPC.h"
#include "Opening/OpeningWidgetBase.h"

void AOpeningGM::ServerTravelToTrapper_Implementation()
{
	GetWorld()->ServerTravel(TEXT("Trapper"));
}

void AOpeningGM::BeginPlay()
{
	Super::BeginPlay();

	ServerSkip = false;
	ClientSkip = false;

	CurrentClientNum = 0;
}

void AOpeningGM::PlayOpeningMediaGM()
{
	for (FConstPlayerControllerIterator Iterator = GetWorld()->GetPlayerControllerIterator(); Iterator; ++Iterator)
	{
		AOpeningPC* PC = Cast<AOpeningPC>(Iterator->Get());
		if (PC)
		{
			// ������ Ŭ���̾�Ʈ���� MediaPlayer�� ���
			if (PC->IsLocalController())
			{
				// ������ MediaPlayer ���
				PC->PlayOpeningMediaPC();
			}
			else
			{
				// Ŭ���̾�Ʈ���� MediaPlayer ���
				PC->ClientPlayMedia();
			}
		}
	}
}

void AOpeningGM::OnPlayerLoaded()
{
	CurrentClientNum++;
	if(CurrentClientNum == ExpectedClientNum)
	{
		PlayOpeningMediaGM();
	}
}

void AOpeningGM::PressedSkip(int32 Type)
{
	if (!this || (ClientSkip && ServerSkip))
	{
		return;
	}
	AOpeningGS* GS = GetGameState<AOpeningGS>();

	if (Type == 1 && ServerSkip == false)
	{
		ServerSkip = true;
		GS->SkipCount++;
		GS->OnRep_SkipCount();
	}
	else if (Type == 2 && ClientSkip == false)
	{
		ClientSkip = true;
		GS->SkipCount++;
		GS->OnRep_SkipCount();
	}
	
	// �Ѵ� ��ŵ�� �����ٸ�
	if (ClientSkip && ServerSkip)
	{
		for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
		{
			AOpeningPC* PC = Cast<AOpeningPC>(It->Get());
			if (PC)
			{
				PC->ClientShowLoading();  // Ŭ���̾�Ʈ���� �ε� �г��� ���� ���� RPC ȣ��
			}
		}

		GetWorld()->ServerTravel(TEXT("Trapper"));
	}

}
