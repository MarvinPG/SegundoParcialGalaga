
#include "NaveEnemigaRalentizadora.h"

ANaveEnemigaRalentizadora::ANaveEnemigaRalentizadora()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> malla(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_6.TwinStickUFO_6'"));
	mallaNaveEnemiga->SetStaticMesh(malla.Object);

	PrimaryActorTick.bCanEverTick = true;

	targetXLocations[0] = 400.0f;
	targetYLocations[0] = -1600.0f;
	targetXLocations[1] = -1300.0f;
	targetYLocations[1] = -306.0f;
	targetXLocations[2] = -1300.0f;
	targetYLocations[2] = 350.0f;
	targetXLocations[3] = 400.0f;
	targetYLocations[3] = 1600.0f;

	// Set the initial target location index
	currentTargetIndex = 0;
}

void ANaveEnemigaRalentizadora::Tick(float DeltaTime)
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

void ANaveEnemigaRalentizadora::Mover(float DeltaTime)
{
}
