// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tile.generated.h"

UCLASS()
class SHOOTER_API ATile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UFUNCTION()
		void OnTileBeginOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex,
			bool bFromSweep,
			const FHitResult& SweepResult
		);
	
	UFUNCTION()
		void OnTileEndOverlap(
			UPrimitiveComponent* OverlappedComponent,
			AActor* OtherActor,
			UPrimitiveComponent* OtherComp,
			int32 OtherBodyIndex
		);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile Properties", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TileMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tile Properties", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

	class ALevelGenerator* LevelGenerator;

	int16 X;
	int16 Y;

public:
	FORCEINLINE UStaticMeshComponent* GetTileMesh() const { return TileMesh; };
	FORCEINLINE void SetX(int16 mX) { X = mX; };
	FORCEINLINE void SetY(int16 mY) { Y = mY; };
	FORCEINLINE int16 GetX() { return X; };
	FORCEINLINE int16 GetY() { return Y; };
	FORCEINLINE void SetLevelGenerator(ALevelGenerator* LevelGen) { LevelGenerator = LevelGen; };

	void HandleDestroy();

};
