// Fill out your copyright notice in the Description page of Project Settings.


#include "EstadoNormal.h"
#include "Galaga_USFX_LAB02Projectile.h"
#include "NaveEstado.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AEstadoNormal::AEstadoNormal()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    FireRate = 1.0f;

    // Encuentra la nueva malla
    static ConstructorHelpers::FObjectFinder<UStaticMesh> NuevaMallaFinder(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_15.TwinStickUFO_15'"));
    if (NuevaMallaFinder.Succeeded())
    {
        NuevaMalla = NuevaMallaFinder.Object;
    }

    // Inicializar el contador de proyectiles
    MaxProjectiles = 5;  // Establecer el máximo de proyectiles disponibles
    ProjectileCount = MaxProjectiles;  // Iniciar el contador con el máximo de proyectiles


}

// Called when the game starts or when spawned
void AEstadoNormal::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstadoNormal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstadoNormal::Mover(float DeltaTime)
{
    if (NaveAliada)
    {
        // Obtener la posición actual de la nave
        FVector PosicionActual = NaveAliada->GetActorLocation();

        // Definir los límite DERECHO E IZQUIERDO de movimiento
        float LimiteDerecho = 1600.0f;
        float LimiteIzquierdo = -1600.0f;

        // Definir la velocidad de movimiento horizontal
        float VelocidadHorizontal = 1000.0f;

        // Calcular el desplazamiento horizontal para este fotograma
        float DesplazamientoHorizontal = VelocidadHorizontal * DeltaTime;

        // Verificar si la nave está moviéndose hacia derecha o izquierda

        if (DireccionMovimientoHorizontal == 1) // Movimiento hacia derecha
        {
            // Mover la nave hacia derecha
            FVector NuevaPosicion = PosicionActual + FVector(0.0f, DesplazamientoHorizontal, 0.0f);
            if (NuevaPosicion.Y <= LimiteDerecho)
            {
                NaveAliada->SetActorLocation(NuevaPosicion);
            }
            else
            {
                // Si alcanza el límite superior, cambiar la dirección de movimiento a hacia izquierda
                DireccionMovimientoHorizontal = -1;
            }
        }
        else // Movimiento hacia izquierda
        {
            // Mover la nave hacia izquierda
            FVector NuevaPosicion = PosicionActual - FVector(0.0f, DesplazamientoHorizontal, 0.0f);
            if (NuevaPosicion.Y >= LimiteIzquierdo)
            {
                NaveAliada->SetActorLocation(NuevaPosicion);
            }
            else
            {
                // Si alcanza el límite de la izquierda, cambiar la dirección de movimiento a hacia la derecha
                DireccionMovimientoHorizontal = 1;
            }
        }
    }
}

void AEstadoNormal::Disparar()
{
    if (NaveAliada && ProjectileCount > 0)  // Solo dispara si hay proyectiles disponibles
    {
        AGalaga_USFX_LAB02Projectile* Projectile = GetWorld()->SpawnActor<AGalaga_USFX_LAB02Projectile>(AGalaga_USFX_LAB02Projectile::StaticClass(), NaveAliada->GetActorLocation(), NaveAliada->GetActorRotation());
        if (Projectile)
        {
            FVector ForwardDirection = NaveAliada->GetActorForwardVector();
            FRotator SpawnRotation = ForwardDirection.Rotation();
            FVector SpawnLocation = NaveAliada->GetActorLocation();
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

void AEstadoNormal::CambiarMalla()
{
    if (NaveAliada && NuevaMalla)
    {
        NaveAliada->GetStaticMeshComponent()->SetStaticMesh(NuevaMalla);
    }
}

void AEstadoNormal::SetAliada(ANaveEstado* _NaveAliada)
{
    NaveAliada = Cast <ANaveEstado>(_NaveAliada);
    NaveAliada->MostrarEstado(NaveAliada->GetEstadoAplazado());

   CambiarMalla();

    // Iniciar el temporizador de disparo
    if (NaveAliada)
    {
        GetWorldTimerManager().SetTimer(FireTimerHandle, this, &AEstadoNormal::Disparar, FireRate, true);
    }
}


