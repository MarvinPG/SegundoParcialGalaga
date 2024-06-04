
#include "ProyectilEnemiga.h"
#include "Galaga_USFX_LAB02Pawn.h"
#include "NaveEstado.h"

AProyectilEnemiga::AProyectilEnemiga()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	static ConstructorHelpers::FObjectFinder<UStaticMesh> mallaP(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere_2.Shape_Sphere_2'"));
	mallaProyectil = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh"));//crea el objeto mallaProyectil
	mallaProyectil->SetStaticMesh(mallaP.Object);  //asigna la malla al objeto mallaProyectil
	mallaProyectil->SetupAttachment(RootComponent);//asigna el objeto mallaProyectil al componente raiz
	RootComponent = mallaProyectil; //asigna el objeto mallaProyectil al componente raiz
	mallaProyectil->BodyInstance.SetCollisionProfileName("Projectile");
	mallaProyectil->OnComponentHit.AddDynamic(this, &AProyectilEnemiga::OnHit);

	SetActorScale3D(FVector(1.0f, 0.2f, 0.1f));

	FRotator SpawnRotation = FRotator(0.0f, 0.0f, 90.0f);

	//ProjectileMesh->OnComponentHit.AddDynamic(this, &AEnemyProjectile::OnHit);  // set up a notification for when this component hits something
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->UpdatedComponent = mallaProyectil;
	ProjectileMovement->InitialSpeed = 1500.0f;
	ProjectileMovement->MaxSpeed = 1500.0f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.0f; // No gravity

	// Set default damage
	InitialLifeSpan = 5.0f;

}

void AProyectilEnemiga::FireInDirection(const FVector& ShootDirection)
{
	ProjectileMovement->Velocity = GetActorForwardVector() * ProjectileMovement->InitialSpeed;
}

void AProyectilEnemiga::Fire()
{
	FVector NewLocation = GetActorLocation() + GetActorForwardVector() * 100.0f;
	SetActorLocation(NewLocation);
}

void AProyectilEnemiga::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
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

void AProyectilEnemiga::BeginPlay()
{
	Super::BeginPlay();
}

void AProyectilEnemiga::Tick(float DeltaTime)
{
		Super::Tick(DeltaTime); 

}

