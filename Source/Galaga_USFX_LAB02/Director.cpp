// Fill out your copyright notice in the Description page of Project Settings.


#include "Director.h"

// Sets default values
ADirector::ADirector()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADirector::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADirector::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADirector::ConstruirNaves()
{
	if (ShipBuilder)
	{
		ShipBuilder->GetHijasNodriza();
		ShipBuilder->GetEscudoNodriza();
        ShipBuilder->GetMotorNaveNodriza();

	}

}

void ADirector::SetBuilder(AActor* Builder)
{
	ShipBuilder = Cast<IBuilderNaveNodriza>(Builder);
}



ANODRIZA* ADirector::GetNaveNodriza()
{
    if (ShipBuilder)
    {
        return ShipBuilder->GetNaveNodriza();
    }
    else
    {
        // Manejar el caso en que ShipBuilder es nulo, por ejemplo, lanzar una advertencia o devolver un valor predeterminado
        UE_LOG(LogTemp, Warning, TEXT("ShipBuilder es nulo"));
        return nullptr;
    }
}




