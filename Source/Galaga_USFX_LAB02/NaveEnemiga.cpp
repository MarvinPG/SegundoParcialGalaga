#include "NaveEnemiga.h"
#include "ProyectilEnemiga.h"



ANaveEnemiga::ANaveEnemiga()
{

	PrimaryActorTick.bCanEverTick = true;

	mallaNaveEnemiga = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	mallaNaveEnemiga->SetupAttachment(RootComponent);
	RootComponent = mallaNaveEnemiga;

	FireRate = 0.7f;

}

void ANaveEnemiga::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ANaveEnemiga::FireProjectile, FireRate, true);

}

void ANaveEnemiga::FireProjectile()
{
	AProyectilEnemiga* Projectile = GetWorld()->SpawnActor<AProyectilEnemiga>(AProyectilEnemiga::StaticClass(), GetActorLocation(), GetActorRotation());
	if (Projectile)
	{
		// Obtén la dirección hacia adelante de la nave enemiga
		FVector ForwardDirection = GetActorForwardVector();

		// Calcula la rotación basada en la dirección hacia adelante
		FRotator SpawnRotation = ForwardDirection.Rotation();

		// Configura la posición y dirección del proyectil
		FVector SpawnLocation = GetActorLocation();
		Projectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);

		// Dispara el proyectil
		Projectile->Fire();
	}
}

void ANaveEnemiga::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime); 


}






