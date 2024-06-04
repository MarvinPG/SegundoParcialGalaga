// Fill out your copyright notice in the Description page of Project Settings.


#include "MotorNaveNodriza.h"

#include "ProyectilPrueba.h"

// Sets default values
AMotorNaveNodriza::AMotorNaveNodriza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallav(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_9.TwinStickUFO_9'"));
	MeshComponente = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComponente->SetupAttachment(RootComponent);
	MeshComponente->SetStaticMesh(mallav.Object);
	RootComponent = MeshComponente;

	SetActorScale3D(FVector(2.5f, 2.5f, 2.5f));
	PrimaryActorTick.bCanEverTick = true;

	// Configura el componente de movimiento
	MovimientoNavesComponent = CreateDefaultSubobject<UAComponenteMovimiento>(TEXT("MovimientoNavesComponente"));

	//******
	FireRate = 0.2f;

	ContadorImpactos = 0; // Inicializa el contador de impactos
}

// Called when the game starts or when spawned
void AMotorNaveNodriza::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AMotorNaveNodriza::FireProjectile, FireRate, true);
	
}

// Called every frame
void AMotorNaveNodriza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMotorNaveNodriza::FireProjectile()
{
	AProyectilPrueba* Projectile = GetWorld()->SpawnActor<AProyectilPrueba>(AProyectilPrueba::StaticClass(), GetActorLocation(), GetActorRotation());
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

void AMotorNaveNodriza::ImpactoProyectilMotor()
{
	ContadorImpactos++; // Incrementa el contador de impactos
	if (ContadorImpactos >= 10) // Si el contador de impactos es mayor o igual a 3
	{
		Destroy(); // Destruye el motor
		FString Message = FString::Printf(TEXT("Nodriza Eliminada"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, Message, true, FVector2D(5.0f, 5.0f));
	}
}

