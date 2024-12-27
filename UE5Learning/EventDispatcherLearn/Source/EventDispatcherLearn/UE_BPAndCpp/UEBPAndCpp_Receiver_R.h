// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UEBPAndCpp_Receiver_Parent.h"
#include "UEBPAndCpp_Receiver_R.generated.h"

/**
 * 
 */
UCLASS()
class EVENTDISPATCHERLEARN_API AUEBPAndCpp_Receiver_R : public AUEBPAndCpp_Receiver_Parent
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
public:
	UFUNCTION()
	void OnReceived(int Value);
};
