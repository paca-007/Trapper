// Fill out your copyright notice in the Description page of Project Settings.


#include "Trap/TrabSnabEnviroment/GuillotineTrapSnabEnviroment.h"
#include "Components/BoxComponent.h"
#include "Trap/GuillotinePendulumTrap.h"
#include "Bow/Arrow.h"
#include "TrapperProject.h"

AGuillotineTrapSnabEnviroment::AGuillotineTrapSnabEnviroment()
{
	FirstMagneticTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("FirstMagneticTrigger"));
	SecondMagneticTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("SecondMagneticTrigger"));

	FirstMagneticTrigger->SetupAttachment(Mesh);
	SecondMagneticTrigger->SetupAttachment(Mesh);

	bFirstMagneticTriggerActivated = false;
	bSecondMagneticTriggerActivated = false;
}

void AGuillotineTrapSnabEnviroment::BeginPlay()
{
	Super::BeginPlay();

	FirstMagneticTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGuillotineTrapSnabEnviroment::OnOverlapBeginMagneticArrow);
	SecondMagneticTrigger->OnComponentBeginOverlap.AddDynamic(this, &AGuillotineTrapSnabEnviroment::OnOverlapBeginMagneticArrow);
}

bool AGuillotineTrapSnabEnviroment::IsMagneticTriggerActivated() const
{
	if (bFirstMagneticTriggerActivated || bSecondMagneticTriggerActivated)
	{
		return true;
	}

	return false;
}

void AGuillotineTrapSnabEnviroment::SetWallMagneticTriggerFalse()
{
	bFirstMagneticTriggerActivated = false;
	bSecondMagneticTriggerActivated = false;
}

void AGuillotineTrapSnabEnviroment::OnOverlapBeginMagneticArrow(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	if (!HasAuthority() || !IsValid(InstalledTrap) || !InstalledTrap->CanAttack())
	{
		return;
	}

	if (OtherActor && OtherActor->ActorHasTag("MagneticArrow"))
	{
		AActor* OwnerActor = OtherActor->GetOwner();
		if (!OwnerActor)
		{
			return;
		}

		if (OverlappedComponent == FirstMagneticTrigger)
		{
			if (bSecondMagneticTriggerActivated)
			{
				bSecondMagneticTriggerActivated = false;
			}

			bFirstMagneticTriggerActivated = true;

			// Ʈ���Ÿ� Ȱ��ȭ ��Ų �÷��̾� ����
			//SetActivatingPlayer(OtherActor);
			MulticastRPCSetActivingPlayer(OtherActor);

			// ���� Ȱ��ȭ ���� üũ �� ����
			CheckTrapActivationAndExcute(OtherActor);
		}
		else if (OverlappedComponent == SecondMagneticTrigger)
		{
			if (bFirstMagneticTriggerActivated)
			{
				bFirstMagneticTriggerActivated = false;
			}

			bSecondMagneticTriggerActivated = true;

			// Ʈ���Ÿ� Ȱ��ȭ ��Ų �÷��̾� ����
			//SetActivatingPlayer(OtherActor);
			MulticastRPCSetActivingPlayer(OtherActor);

			// ���� Ȱ��ȭ ���� üũ �� ����
			CheckTrapActivationAndExcute(OtherActor);
		}
	}
}

void AGuillotineTrapSnabEnviroment::CheckTrapActivationAndExcute(AActor* OtherActor)
{
	//UE_LOG(LogTrap, Warning, TEXT("CheckTrapActivationAndExcute"));
	
	// ���� �ǵ��
	InstalledTrap->AimFeedback(OtherActor);

	AGuillotinePendulumTrap* Trap = Cast<AGuillotinePendulumTrap>(InstalledTrap);
	if (IsValid(Trap))
	{
		if (Trap->IsMagneticTriggerActivated())
		{
			//Trap->SetTrapActive(true, bFirstMagneticTriggerActivated, this);
			Trap->MulticastRPCSetTrapActive(true, bFirstMagneticTriggerActivated);
		}
	}
}

void AGuillotineTrapSnabEnviroment::SetActivatingPlayer(AActor* OtherActor)
{
	AActor* OwnerActor = OtherActor->GetOwner();
	if (!OwnerActor)
	{
		return;
	}
	ActivatingPlayer = OwnerActor;
}

void AGuillotineTrapSnabEnviroment::MulticastRPCSetActivingPlayer_Implementation(AActor* OtherActor)
{
	AActor* OwnerActor = OtherActor->GetOwner();
	if (!OwnerActor)
	{
		//UE_LOG(LogTrap, Warning, TEXT("OwnerActor = nullptr"));
		return;
	}
	ActivatingPlayer = OwnerActor;
}
