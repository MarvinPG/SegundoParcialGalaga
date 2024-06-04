// Fill out your copyright notice in the Description page of Project Settings.


#include "HijasNodriza.h"
#include "ProyectilNodriza.h"

// Sets default values
AHijasNodriza::AHijasNodriza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallav(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Cube.Shape_Cube'"));
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
	MeshComp->SetStaticMesh(mallav.Object);
	RootComponent = MeshComp;
	SetActorScale3D(FVector(1.5f, 1.5f, 1.5f));
	PrimaryActorTick.bCanEverTick = true;

	// Configura el componente de movimiento
	MovimientoNavesComponent = CreateDefaultSubobject<UAComponenteMovimiento>(TEXT("MovimientoNavesComponente"));

	//******
	FireRate = 1.0f;

	ContadorImpactos = 0; // Inicializa el contador de impactos


}

// Called when the game starts or when spawned
void AHijasNodriza::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AHijasNodriza::FireProjectile, FireRate, true);
}

void AHijasNodriza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AHijasNodriza::FireProjectile()
{
	AProyectilNodriza* Projectile = GetWorld()->SpawnActor<AProyectilNodriza>(AProyectilNodriza::StaticClass(), GetActorLocation(), GetActorRotation());
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

void AHijasNodriza::ImpactoProyectilHijas()
{
	ContadorImpactos++; // Incrementa el contador de impactos
	if (ContadorImpactos >= 3) // Si el contador de impactos es mayor o igual a 3
	{
		Destroy(); // Destruye la nave
		FString Message = FString::Printf(TEXT("Hija Nodriza Eliminada"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	}
}





