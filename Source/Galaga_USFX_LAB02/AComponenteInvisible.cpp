#include "AComponenteInvisible.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"

UAComponenteInvisible::UAComponenteInvisible()
{
	PrimaryComponentTick.bCanEverTick = true;
}


void UAComponenteInvisible::BeginPlay()
{
	Super::BeginPlay();
}

void UAComponenteInvisible::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UAComponenteInvisible::Invisibilidad(float Duracion)
{
	Duracion = 5.0f;
	// Make the owning actor invisible
	GetOwner()->SetActorHiddenInGame(true);
	GetOwner()->SetActorEnableCollision(false);

	// Schedule a timer to make the actor visible again after 'Duracion' seconds
	GetWorld()->GetTimerManager().SetTimer(TimerHandle_VisibleTimerExpired, this, &UAComponenteInvisible::HacerVisible, Duracion, false);
}

void UAComponenteInvisible::HacerVisible()
{
	GetOwner()->SetActorHiddenInGame(false);
	GetOwner()->SetActorEnableCollision(true);
}




