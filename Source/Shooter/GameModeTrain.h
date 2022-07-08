// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameModeTrain.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AGameModeTrain : public AGameModeBase
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay();

public:
	AGameModeTrain();

	virtual AActor* FindPlayerStart_Implementation(AController* Player, const FString& IncomingName) override;
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	

private:
	class ATrainManager* TrainManager;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ATrain> TrainClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ALevelGenerator> LevelGeneratorClass;

	FVector PlayerStartLocation;

	ALevelGenerator* LevelGenerator;
	ATrain* Train;
	class APlayerStart* PlayerStart;

public:
	
};
