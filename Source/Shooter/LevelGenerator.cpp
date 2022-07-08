// Fill out your copyright notice in the Description page of Project Settings.


#include "LevelGenerator.h"
#include "Tile.h"
#include "Train.h"
#include "ShooterCharacter.h"
#include "Math/BoxSphereBounds.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ALevelGenerator::ALevelGenerator()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ALevelGenerator::BeginPlay()
{
	Super::BeginPlay();

	ShooterCharacter = Cast<AShooterCharacter>(UGameplayStatics::GetPlayerCharacter(this, 0));
}

// Called every frame
void ALevelGenerator::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("ALevelGenerator Tick"));
}

void ALevelGenerator::ResetTileMap()
{
	for (int i = 0; i < MAX_ROWS; i++)
	{
		for (int j = 0; j < MAX_COLS; j++)
		{
			TileMap[i][j] = nullptr;
		}
	}
}

void ALevelGenerator::GenerateLevel(int8 X, int8 Y)
{
	if (Train == nullptr) return;
	if ((X < 0 || X > MAX_ROWS) || (Y < 0 || Y > MAX_COLS)) return;

	ResetTileMap();

	TilesRendered.Empty();

	ATile* TempTile = GetWorld()->SpawnActor<ATile>(TileClass);
	//const FVector3d Size = TempTile->GetComponentsBoundingBox().GetSize();
	const FVector3d Size = TempTile->GetTileMesh()->GetStaticMesh()->GetBoundingBox().GetSize() * TempTile->GetTileMesh()->GetComponentScale();
	TempTile->Destroy();

	float MaxWidth = Size.X * MAX_COLS;
	float MaxHeight = Size.Y * MAX_ROWS;
	// float StartX = -(MaxWidth / 2.f) + Size.X / 2.f;
	float StartX = 0.f;
	// float StartY = -(MaxHeight / 2.f) + Size.Y / 2.f;
	float StartY = 0.f;

	for (int i = X - RENDER_DISTANCE; i <= X + RENDER_DISTANCE; i++)
	{
		for (int j = Y - RENDER_DISTANCE; j <= Y + RENDER_DISTANCE; j++)
		{
			if (i < 0 || i >= MAX_ROWS) continue;
			if (j < 0 || j >= MAX_COLS) continue;

			ATile* Tile = GetWorld()->SpawnActor<ATile>(TileClass);
			if (Tile)
			{
				const FVector TileLocation = FVector(StartX + (i * Size.X), StartY + (j * Size.Y), 0.f);
				Tile->SetActorLocation(TileLocation);
				Tile->SetX(i);
				Tile->SetY(j);
				Tile->SetLevelGenerator(this);

				TileMap[i][j] = Tile;
				TilesRendered.Add(FString::Printf(TEXT("%i,%i"), i, j), Tile);
			}
		}
	}

	CurrentX = X;
	CurrentY = Y;

	FVector TrainSpawnPoint = FVector{ StartX + (X * Size.X), StartY + (Y * Size.Y), 0.f };
	FVector CharacterSpawnPoint = FVector{ StartX + (X * Size.X), StartY + (Y * Size.Y), 500.f };
	Train->SetActorLocation(TrainSpawnPoint);
	if (ShooterCharacter)
	{
		ShooterCharacter->SetActorLocation(CharacterSpawnPoint);
		Train->SetMoving(true);
	}

	// UE_LOG(LogTemp, Warning, TEXT("Center Location => X: %s"));	
}

void ALevelGenerator::UpdateTileMap(ATile* Tile)
{
	if (Tile == nullptr) return;
	if ((Tile->GetX() == CurrentX && Tile->GetY() == CurrentY)) return;
	if (Train == nullptr) return;
	if ((Tile->GetX() < 0 || Tile->GetX() > MAX_ROWS) || (Tile->GetY() < 0 || Tile->GetY() > MAX_COLS))
	{
		UE_LOG(LogTemp, Warning, TEXT("TENTANDO CRIAR AREA FORA DO MAPA"));
		Train->SetMoving(false);
		return;
	}

	UE_LOG(LogTemp, Warning, TEXT("LOCALIZAÇÃO ATUAL: %i,%i"), Tile->GetX(), Tile->GetY());

	ATile* TempTile = GetWorld()->SpawnActor<ATile>(TileClass);
	//const FVector3d Size = TempTile->GetComponentsBoundingBox().GetSize();
	const FVector3d Size = TempTile->GetTileMesh()->GetStaticMesh()->GetBoundingBox().GetSize() * TempTile->GetTileMesh()->GetComponentScale();
	TempTile->Destroy();

	float MaxWidth = Size.X * MAX_COLS;
	float MaxHeight = Size.Y * MAX_ROWS;
	// float StartX = -(MaxWidth / 2.f) + Size.X / 2.f;
	float StartX = 0.f;
	// float StartY = -(MaxHeight / 2.f) + Size.Y / 2.f;
	float StartY = 0.f;

	TMap<FString, ATile*> TilesToRemove;
	for (auto& Elem : TilesRendered)
	{
		TilesToRemove.Add(Elem.Key, Elem.Value);
	}

	for (int i = Tile->GetX() - RENDER_DISTANCE; i <= Tile->GetX() + RENDER_DISTANCE; i++)
	{
		for (int j = Tile->GetY() - RENDER_DISTANCE; j <= Tile->GetY() + RENDER_DISTANCE; j++)
		{
			if (i < 0 || i >= MAX_ROWS) continue;
			if (j < 0 || j >= MAX_COLS) continue;
			if (TileMap[i][j] != nullptr)
			{
				TilesToRemove.Remove(FString::Printf(TEXT("%i,%i"), i, j));
				continue;
			}
			TilesToRemove.Remove(FString::Printf(TEXT("%i,%i"), i, j));

			ATile* Tile = GetWorld()->SpawnActor<ATile>(TileClass);
			if (Tile)
			{
				const FVector TileLocation = FVector(StartX + (i * Size.X), StartY + (j * Size.Y), 0.f);
				Tile->SetActorLocation(TileLocation);
				Tile->SetX(i);
				Tile->SetY(j);
				Tile->SetLevelGenerator(this);

				TileMap[i][j] = Tile;
				TilesRendered.Add(FString::Printf(TEXT("%i,%i"), i, j), Tile);
			}
		}
	}

	TArray<FString> Keys;
	TilesToRemove.GetKeys(Keys);
	for (FString Key : Keys)
	{
		ATile* TileToRemove = TilesToRemove[Key];
		if (TileToRemove)
		{
			TileMap[TileToRemove->GetX()][TileToRemove->GetY()] = nullptr;
			if (!TileToRemove->IsPendingKill())
			{
				TilesRendered.Remove(FString::Printf(TEXT("%i,%i"), TileToRemove->GetX(), TileToRemove->GetY()));
				TileToRemove->HandleDestroy();
			}
		}
	}

	CurrentX = Tile->GetX();
	CurrentY = Tile->GetY();
}
