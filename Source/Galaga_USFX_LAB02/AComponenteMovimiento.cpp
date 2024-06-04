#include "AComponenteMovimiento.h"

// Sets default values for this component's properties
UAComponenteMovimiento::UAComponenteMovimiento()
{
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UAComponenteMovimiento::BeginPlay()
{
	Super::BeginPlay();

	
}


void UAComponenteMovimiento::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

    AActor* Parent = GetOwner();
    if (Parent)
    {
        // Obtener la posición actual de la nave
        FVector PosicionActual = Parent->GetActorLocation();

        // Definir los límite DERECHO E IZQUIERDO de movimiento
        float LimiteDerecho = 1528.0f;
        float LimiteIzquierdo = -1600.0f;

        // Definir la velocidad de movimiento horizontal
        float VelocidadHorizontal = 200.0f;

        // Calcular el desplazamiento horizontal para este fotograma
        float DesplazamientoHorizontal = VelocidadHorizontal * DeltaTime;

        // Verificar si la nave está moviéndose hacia derecha o izquierda

        if (DireccionMovimientoHorizontal == 1) // Movimiento hacia derecha
        {
            // Mover la nave hacia derecha
            FVector NuevaPosicion = PosicionActual + FVector(0.0f, DesplazamientoHorizontal, 0.0f);
            if (NuevaPosicion.Y <= LimiteDerecho)
            {
                Parent->SetActorLocation(NuevaPosicion);
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
                Parent->SetActorLocation(NuevaPosicion);
            }
            else
            {
                // Si alcanza el límite de la izquierda, cambiar la dirección de movimiento a hacia la derecha
                DireccionMovimientoHorizontal = 1;
            }
        }
    }
}

