// Fill out your copyright notice in the Description page of Project Settings.


#include "BuilderNaveEscudo.h"
#include "NODRIZA.h"
#include "HijasNodriza.h"
#include "MotorNaveNodriza.h"
#include "EscudoNodriza.h"


// Sets default values
ABuilderNaveEscudo::ABuilderNaveEscudo()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ABuilderNaveEscudo::BeginPlay()
{
	Super::BeginPlay();
	NaveNodriza = GetWorld()->SpawnActor<ANODRIZA>(ANODRIZA::StaticClass());
	NaveNodriza->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform); 
	
}

void ABuilderNaveEscudo::GetHijasNodriza()
{
	FVector Location = FVector(1880, -60, 200);
	FVector Location2 = FVector(1880, 240, 200);
	FRotator Rotation = FRotator(0, 180, 0);


	Hijas = GetWorld()->SpawnActor<AHijasNodriza>(AHijasNodriza::StaticClass(), Location, Rotation);
	Hijas = GetWorld()->SpawnActor<AHijasNodriza>(AHijasNodriza::StaticClass(), Location2, Rotation);
	NaveNodriza->SetHijasNodrizas(Hijas);

}

void ABuilderNaveEscudo::GetEscudoNodriza()
{
	FVector Location = FVector(1680, 95, 200);
	FRotator Rotation = FRotator(0, 225, 0);
	Escudo = GetWorld()->SpawnActor<AEscudoNodriza>(AEscudoNodriza::StaticClass(), Location, Rotation);
	NaveNodriza->SetEscudoNodriza(Escudo); 
}

void ABuilderNaveEscudo::GetMotorNaveNodriza()
{
	FVector Location = FVector(1780, 90, 200);
	FRotator Rotation = FRotator(0, 180, 0);
	Motor = GetWorld()->SpawnActor<AMotorNaveNodriza>(AMotorNaveNodriza::StaticClass(), Location, Rotation);
	NaveNodriza->SetMotorNaveNodriza(Motor);
}

ANODRIZA* ABuilderNaveEscudo::GetNaveNodriza()
{
	return NaveNodriza;
}

// Called every frame
void ABuilderNaveEscudo::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

