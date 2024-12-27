// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBPandCpp_Sender.h"

#include "MyEventManager.h"
#include "MyData.h"

// Sets default values
AMyBPandCpp_Sender::AMyBPandCpp_Sender()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Sphere = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Sphere"));
	RootComponent = Sphere;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> SphereMesh(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	static ConstructorHelpers::FObjectFinder<UMaterial> SphereMaterial(TEXT("Material'/Engine/BasicShapes/BasicShapeMaterial.BasicShapeMaterial'"));

	if(SphereMesh.Succeeded() && SphereMaterial.Succeeded())
	{
		Sphere->SetStaticMesh(SphereMesh.Object);
		Sphere->SetMaterial(0, SphereMaterial.Object);
	}

}

// Called when the game starts or when spawned
void AMyBPandCpp_Sender::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle TimerHandle;
	auto Lambda = []()
	{
		// create a new data object and dispatch an event
		UMyData* Data = Cast<UMyData>(UMyEventManager::CreateNewData(UMyData::StaticClass()));
		Data->Param = FMath::RandRange(0, 100); // send a random number as a parameter to the listener
		UMyEventManager::DispatchEvent("MyBPAndCpp_DispatchEvent", Data);
	};
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, Lambda, 3.0f, true);
	
}

// Called every frame
void AMyBPandCpp_Sender::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AMyBPandCpp_Sender::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

