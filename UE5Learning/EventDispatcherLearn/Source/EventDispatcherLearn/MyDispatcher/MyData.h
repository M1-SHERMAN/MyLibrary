// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "MyData.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class EVENTDISPATCHERLEARN_API UMyData : public UObject
{
	GENERATED_BODY()

public:
	UMyData();
	
	UPROPERTY(BlueprintReadWrite)
	int Param;
};
