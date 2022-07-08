// Fill out your copyright notice in the Description page of Project Settings.


#include "Train.h"
#include "Components/BoxComponent.h"
#include "Components/ArrowComponent.h"

// Sets default values
ATrain::ATrain() :
	bMoving(false)
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TrainMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TrainMesh"));
	SetRootComponent(TrainMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(GetRootComponent());

	DirectionComponent = CreateDefaultSubobject<UArrowComponent>(TEXT("DirectionComponent"));
	DirectionComponent->SetupAttachment(GetRootComponent());

}

// Called when the game starts or when spawned
void ATrain::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATrain::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!bMoving) return;

	const FVector ForwardVector = DirectionComponent->GetForwardVector();	
	FVector Location = GetActorLocation() + ForwardVector * 2;
	SetActorLocation(Location);

}

