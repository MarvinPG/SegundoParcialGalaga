#include "NaveEnemigaEspia.h"


ANaveEnemigaEspia::ANaveEnemigaEspia()
{
    static ConstructorHelpers::FObjectFinder<UStaticMesh> malla(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_4.TwinStickUFO_4'"));
    mallaNaveEnemiga->SetStaticMesh(malla.Object);
    PrimaryActorTick.bCanEverTick = true;

	targetXLocations[0] = 100.0f;
	targetYLocations[0] = 1000.0f;
	targetXLocations[1] = 1300.0f;
	targetYLocations[1] = 1000.0f;
	targetXLocations[2] = 1300.0f;
	targetYLocations[2] = -1000.0f;
	targetXLocations[3] = 100.0f;
	targetYLocations[3] = -1000.0f;

	// Set the initial target location index
	currentTargetIndex = 0;
}

void ANaveEnemigaEspia::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); 

	// Calculate the new position based on the current direction and speed
	FVector newLocation = GetActorLocation();
	float dx = targetXLocations[currentTargetIndex] - newLocation.X;
	float dy = targetYLocations[currentTargetIndex] - newLocation.Y;
	float distance = sqrt(dx * dx + dy * dy);
	float direction = atan2(dy, dx);
	newLocation.X += speed * DeltaTime * cos(direction);
	newLocation.Y += speed * DeltaTime * sin(direction);
	SetActorLocation(newLocation);

	// Check if the ship has reached the current target location
	if (distance < 10.0f)
	{
		// Move to the next target location
		currentTargetIndex = (currentTargetIndex + 1) % 4;
	}
}

void ANaveEnemigaEspia::Mover(float DeltaTime)
{

}