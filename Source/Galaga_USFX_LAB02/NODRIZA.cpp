// Fill out your copyright notice in the Description page of Project Settings.


#include "NODRIZA.h"
#include "HijasNodriza.h"
#include "MotorNaveNodriza.h"
#include "EscudoNodriza.h"
// Sets default values
ANODRIZA::ANODRIZA()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ANODRIZA::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ANODRIZA::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ANODRIZA::SetHijasNodrizas(AHijasNodriza* hijas)
{
	Hijas = hijas;

}

void ANODRIZA::SetEscudoNodriza(AEscudoNodriza* escudo)
{
	Escudo = escudo;

}

void ANODRIZA::SetMotorNaveNodriza(AMotorNaveNodriza* motor)
{
	Motor = motor;

}

