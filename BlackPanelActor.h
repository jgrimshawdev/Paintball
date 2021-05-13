// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "BlackPanelActor.generated.h"

UCLASS()
class BLACKPANEL_API ABlackPanelActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABlackPanelActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Static mesh components
	UPROPERTY(BlueprintReadWrite)
		UStaticMeshComponent* PanelMesh;
	UPROPERTY()
		UStaticMeshComponent* FrameMesh;

	// Collision component
	UPROPERTY()
		UBoxComponent* PanelCollision;

	// Drawing material
	UPROPERTY()
		UMaterialInterface* MarkerMat;

	// Dynamic material
	UPROPERTY(BlueprintReadWrite)
		UMaterialInstanceDynamic* MarkerMID;

	// Render target
	//UPROPERTY()
		//UTextureRenderTarget2D* RenderTarget;

	// Draw to render target
	UFUNCTION(BlueprintCallable)
		void DrawOnPanel(FVector2D LocationToDraw);

	// size of brush
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		float DrawSize;
	
};
