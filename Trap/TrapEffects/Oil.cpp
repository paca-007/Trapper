// Fill out your copyright notice in the Description page of Project Settings.

#include "Trap/TrapEffects/Oil.h"
#include "Components/BoxComponent.h"
#include "TrapperProject.h"
#include "Character/TrapperPlayer.h"
#include "Monster/BaseMonster.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Trap/OilBagTrap.h"
#include "Character/TrapperPlayerMovementComponent.h"


AOil::AOil()
{
	// 리플리케이트
	bReplicates = true;

	// 틱 사용 안함
	PrimaryActorTick.bCanEverTick = false;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));

	RootComponent = Mesh;
	Trigger->SetupAttachment(Mesh);

	SlowReductionRate = 0.5f;
	//ReducedSpeedTime = 5.f;
}

void AOil::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTrap, Warning, TEXT("AOil::BeginPlay"));

	if (GetOwner() && !GetOwner()->HasAuthority())
	{
		
		return;
	}

	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AOil::OnOverlapBeginCharacter);
	Trigger->OnComponentEndOverlap.AddDynamic(this, &AOil::OnOverlapEndCharacter);
}

void AOil::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	GetWorld()->GetTimerManager().ClearTimer(ReducedSpeedTimerHandle);
}

void AOil::SetReduceTime(float Duration, float Scale)
{
	Trigger->SetWorldScale3D(FVector(Scale, Scale, 1));
	//UE_LOG(LogTrap, Warning, TEXT("SetReduceTime"));
	//UE_LOG(LogTrap, Warning, TEXT("Duration : %f"), Duration);
	ReducedSpeedTime = Duration;
	//UE_LOG(LogTrap, Warning, TEXT("Duration : %f"), Duration);
	GetWorld()->GetTimerManager().SetTimer(ReducedSpeedTimerHandle, this, &AOil::ReducedSpeedTimerCallback, ReducedSpeedTime, false);
	//UE_LOG(LogTrap, Warning, TEXT("ReducedSpeedTime : %f"), ReducedSpeedTime);
}

void AOil::OnOverlapBeginCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepHitResult)
{
	//UE_LOG(LogTrap, Warning, TEXT("Oil OnOverlapBeginCharacter"));

	if (!GetOwner())
	{
		return;
	}

	if (!GetOwner()->HasAuthority() || !IsValid(OtherActor))
	{
		return;
	}

	ACharacter* Character = nullptr;

	if (OtherActor->ActorHasTag("Player"))
	{
		ATrapperPlayer* Player = Cast<ATrapperPlayer>(OtherActor);
		if (IsValid(Player))
		{
			if (Player->GetOverlapOilCount() == 0)
			{
				Character = Player;
			}

			Player->Movement->MaxWalkSpeed;

			Player->OverlapOilCountUp();
		}
	}
	else
	{
		ABaseMonster* Monster = Cast<ABaseMonster>(OtherActor);
		if (IsValid(Monster))
		{
			if (Monster->GetOverlapOilCount() == 0)
			{
				Character = Monster;
			}

			Monster->OverlapOilCountUp();
		}
	}

	if (Character)
	{
		ReduceCharacterSpeed(Character);
	}
}

void AOil::OnOverlapEndCharacter(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//UE_LOG(LogTrap, Warning, TEXT("Oil OnOverlapEndCharacter"));

	if (!GetOwner())
	{
		return;
	}

	if (!GetOwner()->HasAuthority() || !IsValid(OtherActor))
	{
		return;
	}

	ACharacter* Character = nullptr;

	if (OtherActor->ActorHasTag("Player"))
	{
		ATrapperPlayer* Player = Cast<ATrapperPlayer>(OtherActor);
		if (IsValid(Player))
		{
			if (Player->GetOverlapOilCount() == 1)
			{
				Character = Player;
			}

			Player->OverlapOilCountDown();
		}
	}
	else
	{
		ABaseMonster* Monster = Cast<ABaseMonster>(OtherActor);
		if (IsValid(Monster))
		{
			if (Monster->GetOverlapOilCount() == 1)
			{
				Character = Monster;
			}

			Monster->OverlapOilCountDown();
		}
	}

	if (Character)
	{
		RestoreCharacterSpeed(Character);
	}
}

void AOil::ReduceCharacterSpeed(ACharacter* Character)
{
	//UE_LOG(LogTrap, Warning, TEXT("ReduceCharacterSpeed"));

	if (!Character)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	if (MovementComponent)
	{
		if (Character->ActorHasTag("Monster"))
		{
			ABaseMonster* Monster = Cast<ABaseMonster>(Character);
			if (IsValid(Monster))
			{
				Monster->bIsInOil = true;
			}
			//Cast<ABaseMonster>(Character)->bIsInOil = true;
			//MovementComponent->MaxWalkSpeed = MovementComponent->MaxWalkSpeed * SlowReductionRate;
		}
		else
		{
			MulticastRPCReduceCharacterSpeed(Character);
			//UTrapperPlayerMovementComponent* TrapperMoverment = Cast<UTrapperPlayerMovementComponent>(MovementComponent);
			//if (TrapperMoverment)
			//{
			//	//UE_LOG(LogTrap, Warning, TEXT("TrapperMoverment->MaxWalkSpeed : %f"), TrapperMoverment->MaxWalkSpeed);
			//	TrapperMoverment->MaxWalkSpeed = TrapperMoverment->MaxWalkSpeed * TrapperMoverment->SlowReductionRate;
			//	//UE_LOG(LogTrap, Warning, TEXT("TrapperMoverment->MaxWalkSpeed : %f"), TrapperMoverment->MaxWalkSpeed);
			//	//UE_LOG(LogTrap, Warning, TEXT("TrapperMoverment->SlowReductionRate : %f"), TrapperMoverment->SlowReductionRate);
			//}
		}

		//UE_LOG(LogTrap, Warning, TEXT("MaxWalkSpeed : %f"), MovementComponent->MaxWalkSpeed);
	}
}

void AOil::RestoreCharacterSpeed(ACharacter* Character)
{
	//UE_LOG(LogTrap, Warning, TEXT("RestoreCharacterSpeed"));

	if (!Character)
	{
		return;
	}

	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	if (MovementComponent)
	{
		if (Character->ActorHasTag("Monster"))
		{
			ABaseMonster* Monster = Cast<ABaseMonster>(Character);
			if (IsValid(Monster))
			{
				Monster->bIsInOil = false;
			}
			//MovementComponent->MaxWalkSpeed = MovementComponent->MaxWalkSpeed / SlowReductionRate;
		}
		else
		{
			MulticastRPCRestoreCharacterSpeed(Character);
			/*UTrapperPlayerMovementComponent* TrapperMoverment = Cast<UTrapperPlayerMovementComponent>(MovementComponent);
			if (TrapperMoverment)
			{
				TrapperMoverment->MaxWalkSpeed = TrapperMoverment->MaxWalkSpeed / TrapperMoverment->SlowReductionRate;
			}*/
		}

		//UE_LOG(LogTrap, Warning, TEXT("MaxWalkSpeed : %f"), MovementComponent->MaxWalkSpeed);
	}
}

void AOil::ReducedSpeedTimerCallback()
{
	SetActorEnableCollision(false);
	SetLifeSpan(1);
	MulticastRPCWreckActivation();
}

void AOil::MulticastRPCWreckActivation_Implementation()
{
	AOilBagTrap* OilBag = Cast<AOilBagTrap>(Owner);
	if (IsValid(OilBag))
	{
		OilBag->WreckageActivation();
	}
}

void AOil::MulticastRPCReduceCharacterSpeed_Implementation(class ACharacter* Character)
{
	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	UTrapperPlayerMovementComponent* TrapperMoverment = Cast<UTrapperPlayerMovementComponent>(MovementComponent);
	if (TrapperMoverment)
	{
		TrapperMoverment->MaxWalkSpeed = TrapperMoverment->MaxWalkSpeed * TrapperMoverment->SlowReductionRate;
		//UE_LOG(LogTrap, Warning, TEXT("MulticastRPCReduceCharacterSpeed_Implementation"));
		//UE_LOG(LogTrap, Warning, TEXT("MaxWalkSpeed : %f"), TrapperMoverment->MaxWalkSpeed);
	}
}

void AOil::MulticastRPCRestoreCharacterSpeed_Implementation(class ACharacter* Character)
{
	UCharacterMovementComponent* MovementComponent = Character->GetCharacterMovement();
	UTrapperPlayerMovementComponent* TrapperMoverment = Cast<UTrapperPlayerMovementComponent>(MovementComponent);
	if (TrapperMoverment)
	{
		TrapperMoverment->MaxWalkSpeed = TrapperMoverment->MaxWalkSpeed / TrapperMoverment->SlowReductionRate;
		//UE_LOG(LogTrap, Warning, TEXT("MulticastRPCRestoreCharacterSpeed_Implementation"));
		//UE_LOG(LogTrap, Warning, TEXT("MaxWalkSpeed : %f"), TrapperMoverment->MaxWalkSpeed);
	}
}
