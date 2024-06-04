// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEstado.h"
#include "EstadoNormal.h"
#include "EstadoNokia.h"
#include "EstadoAplazado.h"
#include "Galaga_USFX_LAB02Projectile.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "INaveState.h"


// Sets default values
ANaveEstado::ANaveEstado()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaEstado(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_14.TwinStickUFO_14'"));
	MallaEstado = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaAliada"));
	RootComponent = MallaEstado;
	MallaEstado->SetStaticMesh(mallaEstado.Object);
	MallaEstado->SetWorldScale3D(FVector(2.0f, 2.0f, 2.0f));


//**********************************************************
	vida = 200.0f;

}

// Called when the game starts or when spawned
void ANaveEstado::BeginPlay()
{
	Super::BeginPlay();
	 
	EstadoAplazado = GetWorld()->SpawnActor<AEstadoAplazado>(AEstadoAplazado::StaticClass());
	EstadoNokia = GetWorld()->SpawnActor<AEstadoNokia>(AEstadoNokia::StaticClass());
	EstadoNormal = GetWorld()->SpawnActor<AEstadoNormal>(AEstadoNormal::StaticClass());

	InicializarEstados();

	
}

// Called every frame
void ANaveEstado::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MoverAliada(DeltaTime);

}

void ANaveEstado::RecibirDanio() 
{
	vida -= 10.0f;


	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("LA VIDA DE THOM ES: %d"), vida));
	if (vida <= 0.0f)
	{
		Destroy();
		FString Message = FString::Printf(TEXT("THOM MURIO"));
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, Message, true, FVector2D(2.0f, 2.0f));

		return;
	}


	InicializarEstados();
}

void ANaveEstado::InicializarEstados()
{
	if (vida >= 130.0f)
	{
		EstadoNokia->SetAliada(this);
		MostrarEstado(EstadoNokia);

	}
	else if (vida >= 60.0f && vida < 130)
	{
		EstadoNormal->SetAliada(this);
		MostrarEstado(EstadoNormal);

	}
	else
	{
		EstadoAplazado->SetAliada(this);
		MostrarEstado(EstadoAplazado);

	}

}
//ALMACENO METODOS DE MI INTERFACE
void ANaveEstado::MoverAliada(float DeltaTime)
{
	Estado->Mover(DeltaTime);
}

void ANaveEstado::DispararAliada()
{
	Estado->Disparar();
}

void ANaveEstado::CambiarMalla()
{
	Estado->CambiarMalla();
}
//OBTENGO LOS METODOS DE MI INTERFACE
void ANaveEstado::MostrarEstado(IINaveState* _State)
{
	GetWorldTimerManager().ClearAllTimersForObject(this);


	Estado = _State;
}

IINaveState* ANaveEstado::GetEstadoNormal()
{
	return EstadoNormal;
}

IINaveState* ANaveEstado::GetEstadoNokia()
{
	return EstadoNokia;
}

IINaveState* ANaveEstado::GetEstadoAplazado()
{
	return EstadoAplazado;
}

IINaveState* ANaveEstado::GetEstado()
{
	return Estado;
}
