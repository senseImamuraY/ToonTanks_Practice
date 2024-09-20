// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tower.h"
#include "TestMagoTower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATestMagoTower : public ATower
{
	GENERATED_BODY()

public:
	void ActorDied() override;
};
