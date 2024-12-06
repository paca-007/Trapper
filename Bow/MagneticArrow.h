// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Arrow.h"
#include "MagneticArrow.generated.h"

/**
 * 
 */
UCLASS()
class TRAPPERPROJECT_API AMagneticArrow : public AArrow
{
	GENERATED_BODY()
	
public:
	AMagneticArrow();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;
	
	
/// ��� �Լ� ------------------------------------------------	
public:
	virtual void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;


/// ��� ���� ------------------------------------------------
	virtual void FireArrow(FVector Direction, float Strength) override;
};
