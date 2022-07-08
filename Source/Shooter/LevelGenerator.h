// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelGenerator.generated.h"

const int MAX_ROWS = 20;
const int MAX_COLS = 20;
const int RENDER_DISTANCE = 5;

UCLASS()
class SHOOTER_API ALevelGenerator : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ALevelGenerator();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	class ATrain* Train;
	class AShooterCharacter* ShooterCharacter;

	TArray<TArray<class ATile*>> TATiles;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Level, meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ATile> TileClass;

	ATile* TileMap[MAX_ROWS][MAX_COLS];
	TMap<FString, ATile*> TilesRendered;	

	int16 CurrentX;
	int16 CurrentY;	

	void ResetTileMap();

public:

	FORCEINLINE void SetTrain(ATrain* CurrentTrain) { Train = CurrentTrain; };
	FORCEINLINE void SetShooterCharacter(AShooterCharacter* ShooterChar) { ShooterCharacter = ShooterChar; };
	FORCEINLINE int16 GetCurrentX() const { return CurrentX; };
	FORCEINLINE int16 GetCurrentY() const { return CurrentY; };

	void GenerateLevel(int8 X, int8 Y);
	void UpdateTileMap(ATile* Tile);

};
