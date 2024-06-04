// Fill out your copyright notice in the Description page of Project Settings.


#include "NaveEnemigaTitan.h"

ANaveEnemigaTitan::ANaveEnemigaTitan()
{

    static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshFinder(TEXT("StaticMesh'/Game/TwinStick/Meshes/TwinStickUFO_8.TwinStickUFO_8'"));
    mallaNaveEnemiga->SetStaticMesh(MeshFinder.Object);
    nombre = "NaveEnemigaTitan";
    PrimaryActorTick.bCanEverTick = true;

}

void ANaveEnemigaTitan::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}


void ANaveEnemigaTitan::Mover(float DeltaTime)
{

}
