// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/Material.h"
#include "Paintball3_GrimshawProjectile.generated.h"

UCLASS(config=Game)
class APaintball3_GrimshawProjectile : public AActor
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(VisibleDefaultsOnly, Category=Projectile)
	class USphereComponent* CollisionComp;

	/** Projectile movement component */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovement;

	// Static mesh component
	UPROPERTY(EditAnywhere)
		class UStaticMeshComponent* ProjectileMesh;

public:
	APaintball3_GrimshawProjectile();

	// Projectile material
	UPROPERTY(EditAnywhere)
		UMaterial* DecalMat;

	// Projectile color
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float RColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float GColor;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float BColor;
	
	/** called when projectile hits something */
	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	/** Returns CollisionComp subobject **/
	FORCEINLINE class USphereComponent* GetCollisionComp() const { return CollisionComp; }
	/** Returns ProjectileMovement subobject **/
	FORCEINLINE class UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }

	FTimerHandle DestroyDelayTimer;

	void DestroyProjectile();
};

