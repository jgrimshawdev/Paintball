// Fill out your copyright notice in the Description page of Project Settings.

#include "TowerSensor.h"
#include "ConstructorHelpers.h"
#include "TimerManager.h"

// Sets default values
ATowerSensor::ATowerSensor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SensorRoot = CreateAbstractDefaultSubobject<USceneComponent>(TEXT("SensorRoot"));
	RootComponent = SensorRoot;

	SensorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SensorMesh"));
	SensorMesh->SetupAttachment(RootComponent);

	//Set sensor static mesh
	static ConstructorHelpers::FObjectFinder<UStaticMesh> asset(TEXT("StaticMesh'/Game/Meshes/TowerSensor_SM.TowerSensor_SM'"));
	SensorMesh->SetStaticMesh(asset.Object);

	BaseColor = FLinearColor(0.5625f, 0.5625f, 0.5625f);
	BaseEmissive = 0.0f;

	BlinkColor = FLinearColor(0.0f, 0.0f, 0.0f);
	BlinkEmissive = 5.0f;

	static ConstructorHelpers::FObjectFinder<UMaterial> matasset(TEXT("Material'/Game/TowerSensor/TowerSensor_M.TowerSensor_M'"));
	SensorMat = matasset.Object;
	SensorMesh->SetMaterial(0, SensorMat);
}

// Called when the game starts or when spawned
void ATowerSensor::BeginPlay()
{
	Super::BeginPlay();
	
	if (SensorMat)
	{
		SensorMID = UMaterialInstanceDynamic::Create(SensorMat, this);
		SensorMesh->SetMaterial(0, SensorMID);
	}

}

// Called every frame
void ATowerSensor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATowerSensor::StartBlink()
{
	// Call blink on 1 sec loop
	GetWorldTimerManager().SetTimer(BlinkTimer, this, &ATowerSensor::Blink, 0.5f, true, 0.0f);
}

void ATowerSensor::StopBlink()
{
	// Clear timer
	GetWorldTimerManager().ClearTimer(BlinkTimer);

	// Set to unblink status
	SensorMID->SetVectorParameterValue("Color", BaseColor);
	SensorMID->SetScalarParameterValue("Emissive", BaseEmissive);
}

void ATowerSensor::Blink()
{
	FLinearColor CurrentColor;

	
	if (SensorMID->GetVectorParameterValue("Color", CurrentColor))
	{
		// switch color and emissive
		if (CurrentColor == BaseColor)
		{
			SensorMID->SetVectorParameterValue("Color", BlinkColor);
			SensorMID->SetScalarParameterValue("Emissive", BlinkEmissive);
		}
		else
		{
			SensorMID->SetVectorParameterValue("Color", BaseColor);
			SensorMID->SetScalarParameterValue("Emissive", BaseEmissive);
		}
	}
}

