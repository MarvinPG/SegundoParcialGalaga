
#include "NaveEnemigaUwU.h"

ANaveEnemigaUwU::ANaveEnemigaUwU()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> malla(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_7.TwinStickUFO_7'"));
	mallaNaveEnemiga->SetStaticMesh(malla.Object);

	PrimaryActorTick.bCanEverTick = true;

}

void ANaveEnemigaUwU::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	Angulo += Speed * DeltaTime;

	float NuevaY = GetActorLocation().Y + Radio * FMath::Sin(Angulo) * DeltaTime;
	float NuevaX = GetActorLocation().X + Radio * FMath::Cos(Angulo) * DeltaTime;


	FVector NewLocation = FVector(NuevaX, NuevaY, GetActorLocation().Z);
	SetActorLocation(NewLocation);
}

void ANaveEnemigaUwU::Mover(float DeltaTime)
{
}
