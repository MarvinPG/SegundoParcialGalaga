// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoNokia.h"
#include "Galaga_USFX_LAB02Projectile.h"
#include "NaveEstado.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AEstadoNokia::AEstadoNokia()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	FireRate = 0.2f;



	// Asignar coordenadas de destino
	targetLocations.Add(FVector(-1570, 0, 200));    // Coordenada 1
	targetLocations.Add(FVector(-1570, 800, 200));  // Coordenada 2
	targetLocations.Add(FVector(-1570, -800, 200));  // Coordenada 3
	targetLocations.Add(FVector(-1570, 0, 200));  // Coordenada 4
	targetLocations.Add(FVector(-1570, 0, 2500));  // Coordenada 5


	// Set the initial target location index

	currentTargetIndex = 0;


	// Inicializar el contador de proyectiles
	MaxProjectiles = 50;  // Establecer el máximo de proyectiles disponibles
	ProjectileCount = MaxProjectiles;  // Iniciar el contador con el máximo de proyectiles

}

// Called when the game starts or when spawned
void AEstadoNokia::BeginPlay()
{
	Super::BeginPlay();
	GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEstadoNokia::Disparar, FireRate, true);

}

// Called every frame
void AEstadoNokia::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


void AEstadoNokia::Mover(float DeltaTime)
{
	// Calculate the new position based on the current direction and speed
	FVector newLocation = NaveAliada1->GetActorLocation();
	FVector targetLocation = targetLocations[currentTargetIndex];
	FVector direction = (targetLocation - newLocation).GetSafeNormal();
	float distance = FVector::Distance(targetLocation, newLocation);
	newLocation += direction * Speed * DeltaTime;

	NaveAliada1->SetActorLocation(newLocation);

	// Verificar si la nave ha llegado a la ubicación de destino actual
	if (distance < 20.0f)
	{
		// Mover a la siguiente ubicación de destino
		currentTargetIndex = (currentTargetIndex + 1) % targetLocations.Num();
	}
}

void AEstadoNokia::Disparar()
{
	if (NaveAliada1 && ProjectileCount > 0)  // Solo dispara si hay proyectiles disponibles
	{
		AGalaga_USFX_LAB02Projectile* Projectile = GetWorld()->SpawnActor<AGalaga_USFX_LAB02Projectile>(AGalaga_USFX_LAB02Projectile::StaticClass(), NaveAliada1->GetActorLocation(), NaveAliada1->GetActorRotation());
		if (Projectile)
		{
			FVector ForwardDirection = NaveAliada1->GetActorForwardVector();
			FRotator SpawnRotation = ForwardDirection.Rotation();
			FVector SpawnLocation = NaveAliada1->GetActorLocation();
			Projectile->SetActorLocationAndRotation(SpawnLocation, SpawnRotation);
			Projectile->Fire();

			// Disminuir el contador de proyectiles
			ProjectileCount--;

			// Verificar si se han agotado los proyectiles
			if (ProjectileCount <= 0)
			{
				// Detener el temporizador de disparo
				GetWorldTimerManager().ClearTimer(FireTimerHandle);
			}
		}
	}

}

void AEstadoNokia::CambiarMalla()
{
	//Nokia Tiene La Originalidad de Su Malla
}

void AEstadoNokia::SetAliada(ANaveEstado* _NaveAliada)
{
	NaveAliada1 = Cast <ANaveEstado>(_NaveAliada);
	NaveAliada1->MostrarEstado(NaveAliada1->GetEstadoNokia());
}
