// Fill out your copyright notice in the Description page of Project Settings.


#include "TorreEifel.h"
#include "Components/StaticMeshComponent.h"
#include "TorreAtaque.h"
#include "ProyectilEnemiga.h"
#include "Publicador.h"


// Sets default values
ATorreEifel::ATorreEifel()
	: disparoDuroActivo(false)
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallatorre(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_10.TwinStickUFO_10'"));
	MallaTorre = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshPrope"));
	MallaTorre->SetupAttachment(RootComponent);
	MallaTorre->SetStaticMesh(mallatorre.Object);
	MallaTorre->SetWorldScale3D(FVector(3.0f, 3.0f, 3.0f));
	
	RootComponent = MallaTorre;

	

	//DisparoDuroEjecutado = false;

	disparoDuroActivo = false;
//disparoDuroEjecutado = false;

}

// Called when the game starts or when spawned// StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_13.TwinStickUFO_13'
void ATorreEifel::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetTimerManager().SetTimer(FireTimerHandle, this, &ATorreEifel::FireProjectile, FireRate1, true);
}

// Called every frame
void ATorreEifel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}


void ATorreEifel::FireProjectile()
{
	if (!disparoDuroActivo) {
		AProyectilEnemiga* Projectile = GetWorld()->SpawnActor<AProyectilEnemiga>(AProyectilEnemiga::StaticClass(), GetActorLocation(), GetActorRotation());
		if (Projectile) {
			// Obtén la dirección hacia adelante de la nave enemiga
			FVector ForwardDirection = GetActorForwardVector();

			// Calcula la rotación basada en la dirección hacia adelante
			FRotator SpawnRotation = ForwardDirection.Rotation();

			// Configura la posición y dirección del proyectil
			FVector SpawnLocation = GetActorLocation();
			Projectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);

			// Dispara el proyectil
			Projectile->Fire();

			//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("TORRE NO DISPARA"));
		}
	}
}


void ATorreEifel::SetPublicador(APublicador* _Publicador)
{
	Publicador = _Publicador;
	Publicador->AddSubscriptor(this);
}

void ATorreEifel::Actualizar()
{
	DispararDuro();
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("TORRE SE ACTUALIZO"));
}

void ATorreEifel::EliminaSubs()
{
	Publicador->RemoveSubscriptor(this);
}

void ATorreEifel::DispararDuro()
{
	disparoDuroActivo = true;
	ATorreAtaque* Projectile1 = GetWorld()->SpawnActor<ATorreAtaque>(ATorreAtaque::StaticClass(), GetActorLocation(), GetActorRotation());
	if (Projectile1) {
		// Obtén la dirección hacia adelante de la nave enemiga
		FVector ForwardDirection = GetActorForwardVector();

		// Calcula la rotación basada en la dirección hacia adelante
		FRotator SpawnRotation = ForwardDirection.Rotation();

		// Configura la posición y dirección del proyectil
		FVector SpawnLocation = GetActorLocation();
		Projectile1->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);

		// Dispara el proyectil
		Projectile1->Fire();
		//disparoDuroActivo = false;
		//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("TORRE DISPARO"));
	}
		
}

