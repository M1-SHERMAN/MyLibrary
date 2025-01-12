// Fill out your copyright notice in the Description page of Project Settings.


#include "SampleLobbyGameMode.h"

#include "SteamMultiplayerSessionSubsystem.h"
#include "GameFramework/GameStateBase.h"
#include "GameFramework/PlayerState.h"

class USteamMultiplayerSessionSubsystem;

ASampleLobbyGameMode::ASampleLobbyGameMode()
{
	PathToGameMap = TEXT("/Game/Maps/GameMap");
}

/**
 * 当新玩家登录时的处理逻辑
 * - 更新玩家计数
 * - 显示玩家加入信息
 * - 检查是否满足开始游戏的条件
 */
void ALobbyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (AGameStateBase* GS = GetGameState<AGameStateBase>())
	{
		int32 NumberOfPlayers = GS->PlayerArray.Num();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Number of players: %d"), NumberOfPlayers));

			if (APlayerState* PlayerState = NewPlayer->GetPlayerState<APlayerState>())
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s has joined the game"), *PlayerState->GetPlayerName()));
			}
		}

		// 如果玩家数量达到3个或以上则开始游戏
		// 这里为了方便将玩家数量的判断条件设置为3个，实际游戏中可以根据需求调整
		if (NumberOfPlayers >= 3)
		{
			StartGameCountDown();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.f,
					FColor::Yellow,
					TEXT("Game will start in 5 seconds..."));
			}
		}
		else
		{
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.f,
					FColor::Yellow,
					TEXT("Waiting for more players..."));
			}
		}
	}
}

/**
 * 当玩家登出时的处理逻辑
 * - 更新玩家计数
 * - 显示玩家离开信息
 * - 如果玩家数量不足则取消游戏开始
 */
void ALobbyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);
	if (APlayerState* PlayerState = Exiting->GetPlayerState<APlayerState>())
	{
		int32 NumberOfPlayers = GameState.Get()->PlayerArray.Num();
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				1,
				60.f,
				FColor::Yellow,
				FString::Printf(TEXT("Number of players: %d"), NumberOfPlayers - 1));// -1 是因为Logout调用时，玩家虽然已经离开，但还没有从PlayerArray中移除

			GEngine->AddOnScreenDebugMessage(
					-1,
					60.f,
					FColor::Cyan,
					FString::Printf(TEXT("%s has leaved the game"), *PlayerState->GetPlayerName()));
		}
		if (NumberOfPlayers - 1 < 3)
		{
			CancelStartGame();
			if (GEngine)
			{
				GEngine->AddOnScreenDebugMessage(
					-1,
					5.f,
					FColor::Yellow,
					TEXT("Player left, game start canceled"));
			}
		}
	}
}

/**
 * 游戏模式初始化
 * 获取并存储对会话子系统的引用
 */
void ALobbyGameMode::InitGame(const FString& MapName, const FString& Options, FString& ErrorMessage)
{
	Super::InitGame(MapName, Options, ErrorMessage);
	
	if (const UGameInstance* GameInstance = GetGameInstance())
	{
		SessionSubsystem = GameInstance->GetSubsystem<USteamMultiplayerSessionSubsystem>();

		SessionSubsystem->MultiplayerOnStartSessionComplete.AddDynamic(this, &ThisClass::OnStartSessionComplete);
	}
}

/**
 * 开始游戏
 * 启动会话，成功后切换到游戏地图
 */
void ALobbyGameMode::StartGame()
{
	if (SessionSubsystem)
	{
		SessionSubsystem->StartSession();
	}
}

/**
 * 处理会话启动完成的回调
 * 如果成功则切换到游戏地图，失败则显示错误信息
 */
void ALobbyGameMode::OnStartSessionComplete(bool bWasSuccessful)
{
	if (!bWasSuccessful)
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(
				-1,
				5.f,
				FColor::Red,
				TEXT("Failed to start session!"));
		}
		return;
	}

	GetWorld()->ServerTravel(PathToGameMap);
}

/**
 * 启动5秒倒计时后开始游戏
 */
void ALobbyGameMode::StartGameCountDown()
{
	GetWorldTimerManager().SetTimer(
		StartGameTimerHandle,
		this,
		&ALobbyGameMode::StartGame,
		5.f,
		false);
}

/**
 * 取消游戏开始倒计时
 * 当玩家数量不足时调用
 */
void ALobbyGameMode::CancelStartGame()
{
	GetWorldTimerManager().ClearTimer(StartGameTimerHandle);
}

