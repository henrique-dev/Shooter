// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Rail.generated.h"

UCLASS()
class SHOOTER_API ARail : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARail();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rail Properties", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* RailMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Rail Properties", meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* CollisionBox;

public:

	FORCEINLINE UBoxComponent* GetCollisionBox() const { return CollisionBox; }
	FORCEINLINE UStaticMeshComponent* GetRailMesh() const { return RailMesh; };
};
