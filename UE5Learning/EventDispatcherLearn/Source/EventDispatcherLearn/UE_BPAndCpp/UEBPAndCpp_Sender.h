// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "UEBPAndCpp_Sender.generated.h"

UCLASS()
class EVENTDISPATCHERLEARN_API AUEBPAndCpp_Sender : public APawn
{
	GENERATED_BODY()

public:
	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* Sphere;

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FUEBPAndCpp_BroadcastDelegate, int, Value);
	UPROPERTY(BlueprintAssignable)
	FUEBPAndCpp_BroadcastDelegate UEBPAndCpp_Broadcast;
	
public:
	// Sets default values for this pawn's properties
	AUEBPAndCpp_Sender();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
