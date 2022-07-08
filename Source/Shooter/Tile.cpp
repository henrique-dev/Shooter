// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "Components/BoxComponent.h"
#include "Train.h"
#include "LevelGenerator.h"

// Sets default values
ATile::ATile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	SetRootComponent(TileMesh);

	CollisionBox = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionBox"));
	CollisionBox->SetupAttachment(TileMesh);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();

	CollisionBox->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnTileBeginOverlap);
	CollisionBox->OnComponentEndOverlap.AddDynamic(this, &ATile::OnTileEndOverlap);
}

void ATile::OnTileBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ATrain* Train = Cast<ATrain>(OtherActor);
	if (Train)
	{
		if (LevelGenerator)
		{
			LevelGenerator->UpdateTileMap(this);
		}
	}
}

void ATile::OnTileEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

// Called every frame
void ATile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATile::HandleDestroy()
{
	if (IsPendingKill()) return;

	CollisionBox->OnComponentBeginOverlap.RemoveDynamic(this, &ATile::OnTileBeginOverlap);
	CollisionBox->OnComponentEndOverlap.RemoveDynamic(this, &ATile::OnTileEndOverlap);
	Destroy();
}

