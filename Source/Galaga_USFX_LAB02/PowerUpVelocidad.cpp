// Fill out your copyright notice in the Description page of Project Settings.


#include "PowerUpVelocidad.h"
#include "Galaga_USFX_LAB02Pawn.h"

APowerUpVelocidad::APowerUpVelocidad()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaC(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_WideCapsule.Shape_WideCapsule'"));
	mallaPowerUp->SetStaticMesh(mallaC.Object);
	mallaPowerUp->BodyInstance.SetCollisionProfileName("PowerUp_Velocidad");
	mallaPowerUp->OnComponentHit.AddDynamic(this, &APowerUpVelocidad::OnHit);

}

void APowerUpVelocidad::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    AGalaga_USFX_LAB02Pawn* Pawn = Cast<AGalaga_USFX_LAB02Pawn>(OtherActor);
    if (Pawn)
    {
        Pawn->VELOCIDAD();

        FString Message = FString::Printf(TEXT("MEJORA AUMENTADA"));
        GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, Message);

        Destroy();
    }
}

void APowerUpVelocidad::BeginPlay()
{
	Super::BeginPlay();
}

void APowerUpVelocidad::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // Obt�n la posici�n actual del PowerUpVelocidad
    FVector CurrentLocation = GetActorLocation();

    // Define la velocidad de descenso del PowerUpVelocidad
    float DescendSpeed = 1000.0f; // Puedes ajustar esta velocidad seg�n sea necesario

    // Calcula la nueva posici�n del PowerUpVelocidad con la velocidad de descenso
    FVector NewLocation = CurrentLocation + FVector(0.0f, 0.0f, -DescendSpeed * DeltaTime);

    // Limita la posici�n m�nima en el eje Z para detener el descenso
    float MinZ = 200.0f;
    NewLocation.Z = FMath::Max(NewLocation.Z, MinZ);

    // Establece la nueva posici�n del PowerUpVelocidad
    SetActorLocation(NewLocation);

    // Si alcanza la posici�n final, puedes detener el movimiento o realizar alguna acci�n adicional
    if (NewLocation.Z <= MinZ)
    {
        // Detener el descenso o realizar alguna acci�n adicional
    }
}
