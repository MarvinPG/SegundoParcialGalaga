// Fill out your copyright notice in the Description page of Project Settings.


#include "EstrategiaEspiadora.h"
#include "IEstrategias.h"
#include "Engine/Engine.h"
#include "NaveEstrategica.h"


bool AEstrategiaEspiadora::bMensajeMostrado = false;
// Sets default values
AEstrategiaEspiadora::AEstrategiaEspiadora()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEstrategiaEspiadora::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEstrategiaEspiadora::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEstrategiaEspiadora::Mover(class ANaveEstrategica* PADRIZA, float DeltaTime)
{
	if (PADRIZA)
	{
		Angulo += Speed * DeltaTime;

		float NuevaY = PADRIZA->GetActorLocation().Y + Radio * FMath::Sin(Angulo) * DeltaTime;
		float NuevaX = PADRIZA->GetActorLocation().X + Radio * FMath::Cos(Angulo) * DeltaTime;

		FVector NewLocation = FVector(NuevaX, NuevaY, PADRIZA->GetActorLocation().Z);
		PADRIZA->SetActorLocation(NewLocation);

		if (!AEstrategiaEspiadora::bMensajeMostrado && GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("PADRIZA NOS OBSERBA")));
			AEstrategiaEspiadora::bMensajeMostrado = true;
		}
	}
}

