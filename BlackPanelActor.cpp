// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackPanelActor.h"
#include "ConstructorHelpers.h"
#include "Kismet/KismetRenderingLibrary.h"
#include "Engine.h"

// Sets default values
ABlackPanelActor::ABlackPanelActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create root component
	RootComponent = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("Root Component"));

	// Create static meshes
	PanelMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Panel Mesh"));
	PanelMesh->SetupAttachment(RootComponent);
	FrameMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Frame Mesh"));
	FrameMesh->SetupAttachment(RootComponent);

	// Get static meshes
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshasset(TEXT("StaticMesh'/BlackPanel/Files/Panel100_SM.Panel100_SM'"));
	PanelMesh->SetStaticMesh(meshasset.Object);
	static ConstructorHelpers::FObjectFinder<UStaticMesh> meshasset2(TEXT("StaticMesh'/BlackPanel/Files/Panel100Frame5_SM.Panel100Frame5_SM'"));
	FrameMesh->SetStaticMesh(meshasset2.Object);

	// Create mesh materials
	static ConstructorHelpers::FObjectFinder<UMaterial> matasset(TEXT("Material'/BlackPanel/Files/Panel_M.Panel_M'"));
	PanelMesh->SetMaterial(0, matasset.Object);
	static ConstructorHelpers::FObjectFinder<UMaterial> matasset2(TEXT("Material'/BlackPanel/Files/WhiteGlowDim.WhiteGlowDim'"));
	FrameMesh->SetMaterial(0, matasset2.Object);

	// Create Box Collision
	PanelCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));
	PanelCollision->SetBoxExtent(FVector(50.0f, 50.0f, 40.0f), true);
	PanelCollision->SetupAttachment(RootComponent);
	PanelCollision->SetRelativeLocation(FVector(0.0f, 0.0f, 20.0f));

	// Create drawing material
	static ConstructorHelpers::FObjectFinder<UMaterial> markerasset(TEXT("Material'/BlackPanel/Files/PanelMarker_M.PanelMarker_M'"));
	MarkerMat = markerasset.Object;

	DrawSize = 0.01f;
}

// Called when the game starts or when spawned
void ABlackPanelActor::BeginPlay()
{
	Super::BeginPlay();
	
	// Create dynamic material for drawing
	if (MarkerMat)
	{
		MarkerMID = UMaterialInstanceDynamic::Create(MarkerMat, this);
	}

	// Set draw size
	MarkerMID->SetScalarParameterValue("DrawSize", DrawSize);
}

// Called every frame
void ABlackPanelActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABlackPanelActor::DrawOnPanel(FVector2D LocationToDraw)
{
	//Set draw location UV and draw
	MarkerMID->SetVectorParameterValue("DrawLocation", FLinearColor(LocationToDraw.X, LocationToDraw.Y, 0));
}

