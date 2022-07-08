// Fill out your copyright notice in the Description page of Project Settings.


#include "GameModeTrain.h"
#include "LevelGenerator.h"
#include "Train.h"
#include "GameFramework/PlayerStart.h"
#include "ShooterCharacter.h"

AGameModeTrain::AGameModeTrain() :
	PlayerStartLocation(FVector(0.f, 0.f, 250.f))
{

}

void AGameModeTrain::BeginPlay()
{
	UE_LOG(LogTemp, Warning, TEXT("GameModeTrain BeginPlay"));

	if (LevelGeneratorClass && TrainClass)
	{
		LevelGenerator = GetWorld()->SpawnActor<ALevelGenerator>(LevelGeneratorClass);
		Train = GetWorld()->SpawnActor<ATrain>(TrainClass);
		LevelGenerator->SetTrain(Train);
		LevelGenerator->GenerateLevel(5, 5);
	}
}

AActor* AGameModeTrain::FindPlayerStart_Implementation(AController* Player, const FString& IncomingName)
{
	return Super::FindPlayerStart_Implementation(Player, IncomingName);
}

AActor* AGameModeTrain::ChoosePlayerStart_Implementation(AController* Player)
{
	PlayerStart = GetWorld()->SpawnActor<APlayerStart>(APlayerStart::StaticClass(), PlayerStartLocation, FRotator(0.f, 0.f, 0.f));
	return PlayerStart;
}
