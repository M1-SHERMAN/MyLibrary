// Fill out your copyright notice in the Description page of Project Settings.


#include "MyEventManager.h"
#include "EventDispatcherInterface.h"

TMap<FString, TArray<UObject*>> UMyEventManager::ListenerList;

void UMyEventManager::AddEventListener(const FString EventName, UObject* Listener)
{
	if(EventName==""
	||	Listener == nullptr
	||	!Listener->IsValidLowLevel()
	||	!Listener->GetClass()->ImplementsInterface(UEventDispatcherInterface::StaticClass()))
		{ return; }
	
	TArray<UObject*>* TempArray = UMyEventManager::ListenerList.Find(EventName);
	// If the event name is not found in the map, add it with the listener
	if(TempArray == nullptr || TempArray->Num() == 0)
	{
		const TArray<UObject*> NewArray = { Listener };
		UMyEventManager::ListenerList.Add(EventName, NewArray);
	}
	else
	{
		TempArray->Add(Listener);
	}
}

void UMyEventManager::RemoveEventListener(FString EventName, UObject* Listener)
{
	TArray<UObject*>* TempArray = UMyEventManager::ListenerList.Find(EventName);
	// If the event name is found in the map, remove the listener
	if(TempArray != nullptr && TempArray->Num() != 0)
	{
		TempArray->Remove(Listener);
	}
}

FString UMyEventManager::DispatchEvent(FString EventName, UObject* Data)
{
	TArray<UObject*>* TempArray = UMyEventManager::ListenerList.Find(EventName);

	if(TempArray == nullptr || TempArray->Num() == 0) {return "'" + EventName + "' event has no listeners";}

	FString ErrorInfo = "\n";

	for(int i = 0; i < TempArray->Num(); i++)
	{
		UObject* TempObject = (*TempArray)[i];

		if(TempObject == nullptr
		||	!TempObject->IsValidLowLevel()
		||	!TempObject->GetClass()->ImplementsInterface(UEventDispatcherInterface::StaticClass()))
		{
			TempArray->RemoveAt(i--); // use i-- to prevent skipping elements because TArray will reindex itself
		}
		else
		{
			UFunction* Func = TempObject->FindFunction("OnReceiveEvent");
			if(Func == nullptr || !Func->IsValidLowLevel())
			{
				ErrorInfo += TempObject->GetName() + " does not have 'OnReceiveEvent' function";
			}
			else
			{
				TempObject->ProcessEvent(Func, &Data);
			}
		}
	}

	return ErrorInfo;
}

UObject* UMyEventManager::CreateNewData(UClass* ClassType)
{
	UObject* TempObject = NewObject<UObject>(GetTransientPackage(), ClassType);
	return TempObject;
}
