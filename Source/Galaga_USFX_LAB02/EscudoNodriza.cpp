// Fill out your copyright notice in the Description page of Project Settings.


#include "EscudoNodriza.h"

// Sets default values
AEscudoNodriza::AEscudoNodriza()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallav(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Trim_90_In.Shape_Trim_90_In'"));
	MeshEscudo = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshEscudo->SetupAttachment(RootComponent);
	MeshEscudo->SetStaticMesh(mallav.Object);
	RootComponent = MeshEscudo;
	SetActorScale3D(FVector(2.5f, 2.5f, 2.5f));
	PrimaryActorTick.bCanEverTick = true;

	MovimientoNavesComponent = CreateDefaultSubobject<UAComponenteMovimiento>(TEXT("MovimientoNavesComponente"));

	ContadorImpactos = 0; // Inicializa el contador de impactos

}

// Called when the game starts or when spawned
void AEscudoNodriza::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEscudoNodriza::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEscudoNodriza::ImpactoProyectil()
{
		ContadorImpactos++; // Incrementa el contador de impactos
		if (ContadorImpactos >= 5) // Si el contador de impactos es mayor o igual a 3
		{
		Destroy(); // Destruye el escudo
		FString Message = FString::Printf(TEXT("Escudo Nodriza Eliminado"));
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	}
}

