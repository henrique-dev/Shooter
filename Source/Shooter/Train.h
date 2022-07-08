// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Train.generated.h"

UCLASS()
class SHOOTER_API ATrain : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATrain();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Train Properties", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* TrainMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Train Properties", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Train Properties", meta = (AllowPrivateAccess = "true"))
		class UArrowComponent* DirectionComponent;

	bool bMoving;



public:

	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }
	FORCEINLINE UStaticMeshComponent* GetRailMesh() const { return TrainMesh; };
	FORCEINLINE void SetMoving(bool bIsMoving) { bMoving = bIsMoving; };

};
