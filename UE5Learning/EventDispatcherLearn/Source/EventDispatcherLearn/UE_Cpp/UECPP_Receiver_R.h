// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UECPP_Receiver_Parent.h"
#include "UECPP_Receiver_R.generated.h"

/**
 * 
 */
UCLASS()
class EVENTDISPATCHERLEARN_API AUECPP_Receiver_R : public AUECPP_Receiver_Parent
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:
	void OnReceived(int Value);
	
};
