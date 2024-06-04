// Derechos de autor de Epic Games, Inc. Todos los derechos reservados

#include "Galaga_USFX_LAB02Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Engine/StaticMesh.h"
#include "NaveEnemiga.h"
#include "HijasNodriza.h"
#include "EscudoNodriza.h"
#include "MotorNaveNodriza.h"
#include "NaveEstado.h"
#include "FacadeNaves.h"


AGalaga_USFX_LAB02Projectile::AGalaga_USFX_LAB02Projectile()
{
	// Referencia estática al mesh a utilizar para el proyectil
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ProjectileMeshAsset(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));

	// Crear el componente de mesh para el proyectil
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	ProjectileMesh->SetStaticMesh(ProjectileMeshAsset.Object);
	ProjectileMesh->SetupAttachment(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AGalaga_USFX_LAB02Projectile::OnHit);		// configurar una notificación para cuando este componente golpee algo
	RootComponent = ProjectileMesh;

	SetActorScale3D(FVector(2.5f, 0.3f, 0.3f));

	// Usar un ProjectileMovementComponent para gobernar el movimiento del proyectil
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 5000.f;
	ProjectileMovement->MaxSpeed = 5000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f; // Sin gravedad

	// Morir después de 3 segundos por defecto
	InitialLifeSpan = 3.0f;

}

void AGalaga_USFX_LAB02Projectile::Fire()
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * 200.0f;
	SetActorLocation(NewLocation);
}

void AGalaga_USFX_LAB02Projectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

	// Verificar si OtherActor es una nave enemiga y destruir la nave enemiga
	ANaveEnemiga* NaveEnemiga = Cast<ANaveEnemiga>(OtherActor);
	if (NaveEnemiga)
	{
		//FString Message = FString::Printf(TEXT("Nave Enemiga Eliminada"));
		//GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);

		NaveEnemiga->Destroy();
	}
	 ANaveEstado* NaveEstado = Cast<ANaveEstado>(OtherActor);
	 if (NaveEstado)
	 {
		 NaveEstado->RecibirDanio();
		// FString Message = FString::Printf(TEXT("Nave Enemiga Eliminada"));
		// GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, Message);
	 }



	// Verificar si OtherActor es un escudo nodriza y destruir el escudo nodriza

	AEscudoNodriza* EscudoNodriza = Cast<AEscudoNodriza>(OtherActor);
	if (EscudoNodriza)
	{
		EscudoNodriza->ImpactoProyectil();
	}

	// Verificar si OtherActor es una nave hija nodriza y destruir la nave hija nodriza
	AHijasNodriza* HijasNodriza = Cast<AHijasNodriza>(OtherActor);
	if (HijasNodriza)
	{
		HijasNodriza->ImpactoProyectilHijas();
	}

	// Verificar si OtherActor es una nave nodriza y destruir la nave nodriza
	AMotorNaveNodriza* MotorNaveNodriza = Cast<AMotorNaveNodriza>(OtherActor);
	if (MotorNaveNodriza)
	{
		MotorNaveNodriza->ImpactoProyectilMotor();
	}
	
	// Solo añadir impulso y destruir el proyectil si golpea algo físico
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}



