// Fill out your copyright notice in the Description page of Project Settings.


#include "Publicador.h"
#include "Reloj.h"
#include "ISubscriptor.h"


// Sets default values
APublicador::APublicador()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void APublicador::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APublicador::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (Reloj)
	{
		if (Reloj->Hora >= 5.0f)
		{
			Reloj->Hora = 0.0f;
			NotifySubscriptor();
		}
	}

}

void APublicador::AddSubscriptor(IISubscriptor* Subscriptor)
{
		Subscriptores.Add(Subscriptor);
}

void APublicador::RemoveSubscriptor(IISubscriptor* Subscriptor)
{
	Subscriptores.Remove(Subscriptor);
}

void APublicador::NotifySubscriptor()
{
		for (IISubscriptor* Subscriptor : Subscriptores)
		{
			if (Subscriptor)
			{
				Subscriptor->Actualizar();
				//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Yellow, TEXT("TORRE ACTUALIZADA"));
			}
		}

}

void APublicador::SubscriptorReloj(AReloj* _Reloj)
{
		Reloj = _Reloj;
}



