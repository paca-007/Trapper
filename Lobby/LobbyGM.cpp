// Fill out your copyright notice in the Description page of Project Settings.


#include "LobbyGM.h"
#include "LobbyGS.h"
#include "LobbyPC.h"
#include "Protocol.pb.h"
#include "ServerPacketHandler.h"
#include "TrapperGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraActor.h"

#include "MediaPlayer.h"
#include "MediaSource.h"
#include "MediaTexture.h"

void ALobbyGM::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);
}

void ALobbyGM::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (!Exiting->IsLocalController())
	{
		if (bServerPlayerTitleTravle)
		{
			UGameplayStatics::OpenLevel(this, "Title");
			Cast<UTrapperGameInstance>(GetGameInstance())->SetRoomNumber(0);
			Cast<UTrapperGameInstance>(GetGameInstance())->SetRoomIp("");
		}
	}
}

void ALobbyGM::BeginPlay()
{
	Super::BeginPlay();
}

void ALobbyGM::DecreaseTime()
{
	ALobbyGS* GS = GetGameState<ALobbyGS>();
	if (GS)
	{
		GS->LeftTime--;
		GS->OnRep_LeftTime();

		if (GS->LeftTime == 0)
		{
			// ��� Ŭ���̾�Ʈ�� �ε� �г� ����
			for (FConstPlayerControllerIterator It = GetWorld()->GetPlayerControllerIterator(); It; ++It)
			{
				ALobbyPC* PC = Cast<ALobbyPC>(It->Get());
				if (PC)
				{
					PC->ClientShowLoading();  // Ŭ���̾�Ʈ���� �ε� �г��� ���� ���� RPC ȣ��
				}
			}

			// ���� ���� 
			GetWorld()->ServerTravel(TEXT("Opening"));

			// ���� ���������� �� ������ ������ ����
			Protocol::C_DESTROY_ROOM Msg;
			Msg.set_roomnum(Cast<UTrapperGameInstance>(GetGameInstance())->GetRoomNumber());
			SendBufferRef SendBuffer = ServerPacketHandler::MakeSendBuffer(Msg);
			Cast<UTrapperGameInstance>(GetGameInstance())->SendPacket(SendBuffer);
			Cast<UTrapperGameInstance>(GetGameInstance())->SetRoomNumber(0);
			Cast<UTrapperGameInstance>(GetGameInstance())->SetRoomIp("");

			// Ÿ�̸� Ŭ����
			GetWorldTimerManager().ClearTimer(LobbyTimer);
		}
	}
}

void ALobbyGM::StartGame()
{
	// 5�� ī��Ʈ �ٿ�
	CountDown();
}

void ALobbyGM::CountDown()
{
	GetWorldTimerManager().SetTimer(
		LobbyTimer,
		this,
		&ALobbyGM::DecreaseTime,
		1.0f,
		true,
		1.0f
	);
}