// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUp.h"

// Sets default values
APowerUp::APowerUp()
{

	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaC(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_NarrowCapsule_2.Shape_NarrowCapsule_2'"));
	mallaPowerUp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("mallaPowerUp"));
	mallaPowerUp->SetupAttachment(RootComponent);
	mallaPowerUp->SetStaticMesh(mallaC.Object);
	RootComponent = mallaPowerUp;
	InitialLifeSpan = 5.0f;


 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APowerUp::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APowerUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

