// Fill out your copyright notice in the Description page of Project Settings.


#include "EstrategiaDisparadora.h"
#include "IEstrategias.h"
#include "Engine/Engine.h" 
#include "NaveEstrategica.h"

bool AEstrategiaDisparadora::bMensajeMostrado = false;
// Sets default values
AEstrategiaDisparadora::AEstrategiaDisparadora()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;


	// Asignar coordenadas de destino
	targetLocations.Add(FVector(1200, 900, 400));  // Coordenada 1
	targetLocations.Add(FVector(1200, 950, 300));  // Coordenada 2
	targetLocations.Add(FVector(1200, 900, 600));  // Coordenada 3
	targetLocations.Add(FVector(1200, 850, 500));  // Coordenada 4
	targetLocations.Add(FVector(1200, 900, 850));  // Coordenada 5
	targetLocations.Add(FVector(-10000, 900, 1000)); // Coordenada 6

	currentTargetIndex = 0;

}

// Called when the game starts or when spawned
void AEstrategiaDisparadora::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AEstrategiaDisparadora::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstrategiaDisparadora::Mover(class ANaveEstrategica* PADRIZA, float DeltaTime)
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
		if (!AEstrategiaDisparadora::bMensajeMostrado && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PADRIZA HUYE")));
			AEstrategiaDisparadora::bMensajeMostrado = true;
		}

	}
}





