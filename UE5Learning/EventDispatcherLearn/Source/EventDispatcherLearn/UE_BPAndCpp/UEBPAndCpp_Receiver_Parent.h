// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "UEBPAndCpp_Receiver_Parent.generated.h"

UCLASS()
class EVENTDISPATCHERLEARN_API AUEBPAndCpp_Receiver_Parent : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Cube;
	
public:	
	// Sets default values for this actor's properties
	AUEBPAndCpp_Receiver_Parent();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
