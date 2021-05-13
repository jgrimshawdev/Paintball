// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/EngineTypes.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "TowerSensor.generated.h"

UCLASS()
class PAINTBALL3_GRIMSHAW_API ATowerSensor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATowerSensor();

	bool bBlink;
	bool bBlinkOn;
	float BlinkDelay;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Root component for static mesh
	USceneComponent* SensorRoot;

	// Static Mesh
	UStaticMeshComponent* SensorMesh;

	UStaticMeshComponent* Mesh;

	// Base color
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor BaseColor;
	// Base emissive
	UPROPERTY(EditAnywhere, BluePrintReadWrite)
		float BaseEmissive;
	// Blink color
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		FLinearColor BlinkColor;
	// Blink emissive
	UPROPERTY(EditAnywhere)
		float BlinkEmissive;
	// Material
	UPROPERTY()
		UMaterial* SensorMat;
	// Dynamic material
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		UMaterialInstanceDynamic* SensorMID;

	// Set mesh blink on or off
	UFUNCTION(BlueprintCallable)
		void StartBlink();
	UFUNCTION(BlueprintCallable)
		void StopBlink();
	UFUNCTION(BlueprintCallable)
		void Blink();
	
	FTimerHandle BlinkTimer;
};
