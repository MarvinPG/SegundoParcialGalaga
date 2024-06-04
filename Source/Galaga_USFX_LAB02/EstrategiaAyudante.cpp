// Fill out your copyright notice in the Description page of Project Settings.


#include "EstrategiaAyudante.h"
#include "IEstrategias.h"
#include "Engine/Engine.h"
#include "NaveEstrategica.h"



bool AEstrategiaAyudante::bMensajeMostrado = false;
// Sets default values
AEstrategiaAyudante::AEstrategiaAyudante()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Asignar coordenadas de destino
	targetLocations.Add(FVector(1200, -1000, 200));    // Coordenada 1
	targetLocations.Add(FVector(1200, -500, 400));  // Coordenada 2
	targetLocations.Add(FVector(1200, 0, 200));  // Coordenada 3
	targetLocations.Add(FVector(1200, 500, 400));  // Coordenada 4
	targetLocations.Add(FVector(1200, 1000, 200));  // Coordenada 5
	targetLocations.Add(FVector(1200, 500, 400));    // Coordenada 6
	targetLocations.Add(FVector(1200, 0, 200));    // Coordenada 7
	targetLocations.Add(FVector(1200, -500, 400));  // Coordenada 8
	targetLocations.Add(FVector(1200, -1000, 200));  // Coordenada 9


	// Set the initial target location index

	currentTargetIndex = 0;

}

// Called when the game starts or when spawned
void AEstrategiaAyudante::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstrategiaAyudante::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstrategiaAyudante::Mover(class ANaveEstrategica* PADRIZA, float DeltaTime)
{
	if (PADRIZA) {
		// Calculate the new position based on the current direction and speed
		FVector newLocation = PADRIZA->GetActorLocation();
		FVector targetLocation = targetLocations[currentTargetIndex];
		FVector direction = (targetLocation - newLocation).GetSafeNormal();
		float distance = FVector::Distance(targetLocation, newLocation);
		newLocation += direction * speed * DeltaTime;

		PADRIZA->SetActorLocation(newLocation);

		// Verificar si la nave ha llegado a la ubicación de destino actual
		if (distance < 20.0f)
		{
			// Mover a la siguiente ubicación de destino
			currentTargetIndex = (currentTargetIndex + 1) % targetLocations.Num();
		}

		if (!AEstrategiaAyudante::bMensajeMostrado && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PADRIZA AYUDA A NODRIZA")));
			AEstrategiaAyudante::bMensajeMostrado = true;
		}

	}

}



