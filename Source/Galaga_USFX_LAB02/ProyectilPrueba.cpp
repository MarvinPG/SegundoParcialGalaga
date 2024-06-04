// Fill out your copyright notice in the Description page of Project Settings.


#include "ProyectilPrueba.h"
#include "Galaga_USFX_LAB02Pawn.h"
#include "NaveEstado.h"

void AProyectilPrueba::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
}

void AProyectilPrueba::Fire()
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * 200.0f;
	SetActorLocation(NewLocation);
}

void AProyectilPrueba::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	AGalaga_USFX_LAB02Pawn* Pawn = Cast<AGalaga_USFX_LAB02Pawn>(OtherActor);
	if (Pawn)
	{

		Pawn->ReducirVida();

		// Mostrar un mensaje informando al jugador sobre la pérdida de vida
		FString Message = FString::Printf(TEXT("Vidas restantes: %d "), Pawn->GetVidasRestantes());
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Blue, Message);
		//PawnScore += ScorePorEnemigo;


		// Llamar a la función destruir de la nave enemiga
		Pawn->recibirImpacto();
	}


	ANaveEstado* Nav = Cast<ANaveEstado>(OtherActor);
	if (Nav)
	{
		Nav->RecibirDanio();
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Nave Atacada")));
	}

	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}

	Destroy();
}

// Sets default values
AProyectilPrueba::AProyectilPrueba()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaP(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	mallaProyectil = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));//crea el objeto mallaProyectil
	mallaProyectil->SetStaticMesh(mallaP.Object);  //asigna la malla al objeto mallaProyectil
	mallaProyectil->SetupAttachment(RootComponent);//asigna el objeto mallaProyectil al componente raiz
	RootComponent = mallaProyectil; //asigna el objeto mallaProyectil al componente raiz
	mallaProyectil->BodyInstance.SetCollisionProfileName("Projectile");
	mallaProyectil->OnComponentHit.AddDynamic(this, &AProyectilPrueba::OnHit);

	SetActorScale3D(FVector(0.5f, 0.5f, 0.5f));


	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AEnemyProjectile::OnHit);  // set up a notification for when this component hits something
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = mallaProyectil;
	ProjectileMovement->InitialSpeed = 2000.0f;
	ProjectileMovement->MaxSpeed = 2000.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f; // No gravity

	// Set default damage
	Damage = 10.0f;
	InitialLifeSpan = 3.0f;


}

// Called when the game starts or when spawned
void AProyectilPrueba::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProyectilPrueba::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

