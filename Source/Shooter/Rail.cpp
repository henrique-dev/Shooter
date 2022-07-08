// Fill out your copyright notice in the Description page of Project Settings.


#include "Rail.h"
#include "Components/BoxComponent.h"

// Sets default values
ARail::ARail()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RailMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("RailMesh"));
	SetRootComponent(RailMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(RailMesh);

}

// Called when the game starts or when spawned
void ARail::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ARail::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

