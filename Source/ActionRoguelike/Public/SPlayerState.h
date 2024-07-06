// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnCreditsChanged, ASPlayerState*, PlayerState, int32, NewCredits);
// Looman uses a three param, with an int32 delta. Not sure what that is for. I messaged him.

UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASPlayerState();
	
	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 AddCredit();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 RemoveCredit();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	int32 GetCredit();

	UPROPERTY(BlueprintAssignable, Category = "Credits")
	FOnCreditsChanged OnCreditsChanged;

protected:
	UPROPERTY(EditDefaultsOnly, Category = "Credits")
	int32 Credit = 0;
	
private:


	
};


