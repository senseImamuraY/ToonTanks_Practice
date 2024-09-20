// Fill out your copyright notice in the Description page of Project Settings.


#include "TestMagoTower.h"

void ATestMagoTower::ActorDied()
{
	if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow, "TestMagoTowerCalled");
}
