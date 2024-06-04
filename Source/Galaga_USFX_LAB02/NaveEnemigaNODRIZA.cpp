// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaNODRIZA.h"

ANaveEnemigaNODRIZA::ANaveEnemigaNODRIZA()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> malla(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_2.TwinStickUFO_2'"));
	mallaNaveEnemiga->SetStaticMesh(malla.Object);

	PrimaryActorTick.bCanEverTick = true;


}

void ANaveEnemigaNODRIZA::Tick(float DeltaTime)
{

	Super::Tick(DeltaTime);
}

void ANaveEnemigaNODRIZA::BeginPlay()
{
}

void ANaveEnemigaNODRIZA::Mover(float DeltaTime)
{
}
