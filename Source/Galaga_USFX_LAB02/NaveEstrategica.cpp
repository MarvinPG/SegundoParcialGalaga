
// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEstrategica.h"
#include "ProyectilNodriza.h"
#include "IEstrategias.h"

// Sets default values
ANaveEstrategica::ANaveEstrategica()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallapapa(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_16.TwinStickUFO_16'"));
	MallaPapa = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaAliada"));
	RootComponent = MallaPapa;
	MallaPapa->SetStaticMesh(mallapapa.Object);
	MallaPapa->SetWorldScale3D(FVector(2.5f, 2.5f, 2.5f));

	FireRate = 0.5f;

	// Inicializar el contador de proyectiles
	MaxProjectiles = 30;  // Establecer el máximo de proyectiles disponibles
	ProjectileCount = MaxProjectiles;  // Iniciar el contador con el máximo de proyectiles

}

// Called when the game starts or when spawned
void ANaveEstrategica::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &ANaveEstrategica::FireProjectile, FireRate, true);

}

// Called every frame
void ANaveEstrategica::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	EmplearEstrategia(DeltaTime);
}

//***********************************************************************************************

void ANaveEstrategica::FireProjectile()
{
	if (ProjectileCount > 0)  // Solo dispara si hay proyectiles disponibles
	{
		// Disminuir el contador de proyectiles
		ProjectileCount--;

		// Crear y disparar el proyectil
		AProyectilNodriza* Projectile = GetWorld()->SpawnActor<AProyectilNodriza>(AProyectilNodriza::StaticClass(), GetActorLocation(), GetActorRotation());
		if (Projectile)
		{
			FVector ForwardDirection = GetActorForwardVector();
			FRotator SpawnRotation = ForwardDirection.Rotation();
			FVector SpawnLocation = GetActorLocation();
			Projectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
			Projectile->Fire();
		}
	}
}

void ANaveEstrategica::AlterarEstrategia(AActor* _EstrategiaElegida)
{
	Estrategia = Cast<IIEstrategias>(_EstrategiaElegida);
}

void ANaveEstrategica::EmplearEstrategia(float DeltaTime)
{
	//Super::Tick(DeltaTime);
	if (Estrategia)
	{
		Estrategia->Mover(this, DeltaTime);
	}
}

//***********************************************************************************************