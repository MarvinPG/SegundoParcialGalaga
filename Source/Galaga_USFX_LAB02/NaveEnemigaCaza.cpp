#include "NaveEnemigaCaza.h"

ANaveEnemigaCaza::ANaveEnemigaCaza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> malla(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_11.TwinStickUFO_11'"));
	mallaNaveEnemiga->SetStaticMesh(malla.Object);

	PrimaryActorTick.bCanEverTick = true;


	// Asignar coordenadas de destino
	targetLocations.Add(FVector(-300, 1600, 200));    // Coordenada 1
	targetLocations.Add(FVector(-880, 1000, 200));  // Coordenada 2
	targetLocations.Add(FVector(-510, 560, 200));  // Coordenada 3
	targetLocations.Add(FVector(-880, 40, 200));  // Coordenada 4
	targetLocations.Add(FVector(-510, -480, 200));  // Coordenada 5
	targetLocations.Add(FVector(-880, -950, 200));    // Coordenada 6
	targetLocations.Add(FVector(-300, -1600, 200));    // Coordenada 7

	// Set the initial target location index

	currentTargetIndex = 0;



}

void ANaveEnemigaCaza::Tick(float DeltaTime)
{


	Super::Tick(DeltaTime);


	// Calculate the new position based on the current direction and speed
	FVector newLocation = GetActorLocation();
	FVector targetLocation = targetLocations[currentTargetIndex];
	FVector direction = (targetLocation - newLocation).GetSafeNormal();
	float distance = FVector::Distance(targetLocation, newLocation);
	newLocation += direction * speed * DeltaTime;

	SetActorLocation(newLocation);

	// Verificar si la nave ha llegado a la ubicación de destino actual
	if (distance < 10.0f)
	{
		// Mover a la siguiente ubicación de destino
		currentTargetIndex = (currentTargetIndex + 1) % targetLocations.Num();
	}
}

