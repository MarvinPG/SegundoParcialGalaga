// Fill out your copyright notice in the Description page of Project Settings.


#include "TorreAtaque.h"
#include "FacadeNaves.h"
#include "Components/StaticMeshComponent.h"
#include "NaveEnemiga.h"
#include "Engine/World.h"
#include "Sound/SoundBase.h"
#include "GameFramework/ProjectileMovementComponent.h"



// Sets default values
ATorreAtaque::ATorreAtaque()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaP(TEXT("StaticMesh'/Game/StarterContent/Props/SM_Rock.SM_Rock'"));
	mallaProyectil = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));//crea el objeto mallaProyectil
	mallaProyectil->SetStaticMesh(mallaP.Object);  //asigna la malla al objeto mallaProyectil
	mallaProyectil->SetupAttachment(RootComponent);//asigna el objeto mallaProyectil al componente raiz
	RootComponent = mallaProyectil; //asigna el objeto mallaProyectil al componente raiz
	mallaProyectil->BodyInstance.SetCollisionProfileName("Projectile");
	mallaProyectil->OnComponentHit.AddDynamic(this, &ATorreAtaque::OnHit);

	//SetActorScale3D(FVector(0.7f, 0.7f, 0.7f));

	//FRotator SpawnRotation = FRotator(0.0f, 0.0f, 90.0f);

	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AEnemyProjectile::OnHit);  // set up a notification for when this component hits something
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = mallaProyectil;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 2.5f; // No gravity


	InitialLifeSpan = 3.0f;
	

}

// Called when the game starts or when spawned
void ATorreAtaque::BeginPlay()
{
	Super::BeginPlay();


}

// Called every frame
void ATorreAtaque::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATorreAtaque::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;

}

void ATorreAtaque::Fire()
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * 200.0f; // a que punto de la torre es disparado
	SetActorLocation(NewLocation);
}

void ATorreAtaque::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor->IsA(ANaveEnemiga::StaticClass()))
	{
		ANaveEnemiga* nave = Cast<ANaveEnemiga>(OtherActor);
		if (nave)
		{
			nave->Destroy();
		}
	}
	Destroy();

}