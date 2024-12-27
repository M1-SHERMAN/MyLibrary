// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"

#include "EventDispatcherInterface.h"

#include "MyBPandCpp_Receiver_Parent.h"
#include "MyBPandCpp_Receiver_R.generated.h"

/**
 * 
 */
UCLASS()
class EVENTDISPATCHERLEARN_API AMyBPandCpp_Receiver_R : public AMyBPandCpp_Receiver_Parent, public IEventDispatcherInterface
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;
	
	virtual void BeginDestroy() override;
	
public:
	virtual void OnReceiveEvent_Implementation(UObject* Data) override;
	
};
