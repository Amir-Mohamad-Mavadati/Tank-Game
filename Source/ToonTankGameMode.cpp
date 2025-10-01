// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTankGameMode.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "ToonTankPlayerController.h"

void AToonTankGameMode::ActorDied(AActor* DeadActor)
{
	TorgetTowers = GetTorgertTowerCount();
	if (DeadActor == Tank)
	{
		Tank->HandleDestruction();
		if (ToonTankPlayerController)
		{
			ToonTankPlayerController->SetPlayerEnabledState(false);
		}
		GameOver(false);
	}
	else if (ATower* DestroyTower = Cast<ATower>(DeadActor))
	{
		DestroyTower->HandleDestruction();
		--TorgetTowers;
		if (TorgetTowers == 0) GameOver(true);
	}
}

void AToonTankGameMode::BeginPlay()
{
	Super::BeginPlay();
	HandleGameStart();
}

void AToonTankGameMode::HandleGameStart()
{
	Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
	ToonTankPlayerController = Cast<AToonTankPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

	StartGame();
	
	if (ToonTankPlayerController)
	{
		ToonTankPlayerController->SetPlayerEnabledState(false);
		FTimerHandle PlayerEnableTimerHandle;
		FTimerDelegate PlayerEnableTimerDelegate = FTimerDelegate::CreateUObject(
			ToonTankPlayerController,
			&AToonTankPlayerController::SetPlayerEnabledState,
			true
			);
		GetWorldTimerManager().SetTimer(
			PlayerEnableTimerHandle,
			PlayerEnableTimerDelegate,
			StartDelay,
			false
			);
	}
}

int32 AToonTankGameMode::GetTorgertTowerCount()
{
	TArray<AActor*> Tower;
	UGameplayStatics::GetAllActorsOfClass(
		this,
		ATower::StaticClass(),
		Tower
		);
	return Tower.Num();
}
