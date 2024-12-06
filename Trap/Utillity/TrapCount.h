// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Trap/Utillity/TrapEnums.h"
#include "TrapCount.generated.h"

/**
 *
 */
USTRUCT(BlueprintType)
struct FTrapCount : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	ETrapType Type = ETrapType::None;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 Count = 0;

};