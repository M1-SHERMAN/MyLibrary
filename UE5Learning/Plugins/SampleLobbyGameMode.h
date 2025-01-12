// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SampleLobbyGameMode.generated.h"

/**
 * 大厅游戏模式类示例
 * 负责管理多人游戏的大厅阶段，包括：
 * - 追踪玩家的加入和离开
 * - 控制游戏开始的条件和时机
 * - 处理会话状态的转换
 */
UCLASS()
class ACCESSINGSTEAM_API ASampleLobbyGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASampleLobbyGameMode();
	/** 当新玩家登录时调用，处理玩家加入逻辑 */
	virtual void PostLogin(APlayerController* NewPlayer) override;
	/** 当玩家离开时调用，处理玩家离开逻辑 */
	virtual void Logout(AController* Exiting) override;
	/** 游戏模式初始化时调用，设置必要的子系统 */
	virtual void InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage) override;

	/** 开始游戏，转换到游戏地图 */
	UFUNCTION(BlueprintCallable)
	void StartGame();

	/** 启动游戏开始倒计时 */
	UFUNCTION(BlueprintCallable)
	void StartGameCountDown();

	/** 取消游戏开始倒计时 */
	UFUNCTION(BlueprintCallable)
	void CancelStartGame();

	/** 游戏地图的路径 */
	UPROPERTY(BlueprintReadWrite)
	FString PathToGameMap;
private:
	/** 多人游戏会话子系统的引用 */
	UPROPERTY()
	class USteamMultiplayerSessionSubsystem* SessionSubsystem;

	/** 处理会话启动完成的回调 */
	UFUNCTION()
	void OnStartSessionComplete(bool bWasSuccessful);

	/** 用于管理开始游戏倒计时的计时器句柄 */
	FTimerHandle StartGameTimerHandle;
};
