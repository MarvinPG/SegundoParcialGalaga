// Fill out your copyright notice in the Description page of Project Settings.


#include "Reloj.h"

// Sets default values
AReloj::AReloj()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallareloj(TEXT("StaticMesh'/Game/StarterContent/Architecture/Pillar_50x500.Pillar_50x500'"));
	MallaReloj = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MallaReloj"));
	RootComponent = MallaReloj;
	MallaReloj->SetStaticMesh(mallareloj.Object);
	MallaReloj->SetWorldScale3D(FVector(2.0f, 2.0f, 1.0f));

	Hora = 0;

}

// Called when the game starts or when spawned
void AReloj::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AReloj::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Hora += GetWorld()->GetDeltaSeconds();

	if (Hora >= 10.0f)
	{
		Hora = 0.0f;
	}

}

