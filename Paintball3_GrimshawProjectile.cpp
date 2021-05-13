// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Paintball3_GrimshawProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Math/Vector2D.h"
#include "Kismet/KismetMathLibrary.h"
#include "UObject/ConstructorHelpers.h"
#include "Engine.h"
#include "Engine/DecalActor.h"
#include "TimerManager.h"

APaintball3_GrimshawProjectile::APaintball3_GrimshawProjectile() 
{
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(7.0f);
	CollisionComp->BodyInstance.SetCollisionProfileName("Projectile");
	CollisionComp->OnComponentHit.AddDynamic(this, &APaintball3_GrimshawProjectile::OnHit);		// set up a notification for when this component hits something blocking

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Set up mesh
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	ProjectileMesh->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> projmesh(TEXT("StaticMesh'/Game/StarterContent/Shapes/Shape_Sphere.Shape_Sphere'"));
	ProjectileMesh->SetStaticMesh(projmesh.Object);
	ProjectileMesh->SetRelativeScale3D(FVector(0.5f, 0.5f, 0.5f));
	
	// Set up material
	static ConstructorHelpers::FObjectFinder<UMaterial> projmat(TEXT("Material'/Game/Splatter/SplatterProjectile_M.SplatterProjectile_M'"));
	UMaterial* MeshMat = projmat.Object;
	UMaterialInstanceDynamic* ProjectileMID = UMaterialInstanceDynamic::Create(MeshMat, ProjectileMesh);
	ProjectileMesh->SetMaterial(0, ProjectileMID);
	ProjectileMID->SetVectorParameterValue("ProjectileColor", FLinearColor(0.0f, 0.0f, BColor));
	
	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	// Get color for projectile
	ProjectileMID->SetVectorParameterValue("ProjectileColor", FLinearColor(0.0f, 0.0f, BColor));
	
	//Set splat material
	static ConstructorHelpers::FObjectFinder<UMaterial> splatmat(TEXT("Material'/Game/Splatter/Splatter_M.Splatter_M'"));
	if (splatmat.Object != NULL)
	{
		DecalMat = (UMaterial*)splatmat.Object;
	}
	
	// Die after 3 seconds by default
	InitialLifeSpan = 3.0f;
}

void APaintball3_GrimshawProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if ((OtherActor != NULL) && (OtherActor != this))
	{
		if (DecalMat != nullptr)
		{
			// Spawn splatter decal
			auto Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), DecalMat, FVector(UKismetMathLibrary::RandomFloatInRange(20.0f, 40.0f)), Hit.Location, Hit.Normal.Rotation(), 0.0f);

			// Set splatter color
			auto MatInstance = Decal->CreateDynamicMaterialInstance();
			MatInstance->SetScalarParameterValue("Frame", UKismetMathLibrary::RandomIntegerInRange(0, 3));
			MatInstance->SetVectorParameterValue("Color", FLinearColor(RColor, 0.0f, BColor));
			UE_LOG(LogTemp, Warning, TEXT("RColor: %f, BColor: %f"), RColor, BColor);

			// Make invisible before destroy delay
			ProjectileMesh->SetVisibility(false);
			
			// Destroy projectile after delay for procedural mesh (DamageMeshActor)
			GetWorldTimerManager().SetTimer(DestroyDelayTimer, this, &APaintball3_GrimshawProjectile::DestroyProjectile, 1.0f, true, 0.02f);
		}
	}
}

void APaintball3_GrimshawProjectile::DestroyProjectile()
{
	Destroy();
}
