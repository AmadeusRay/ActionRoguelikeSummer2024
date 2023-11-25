// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "SPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASPlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	ASPlayerState();
	
	UFUNCTION()
	float AddCreditState();

	UFUNCTION()
	float RemoveCreditState();

	UFUNCTION(BlueprintCallable, Category = "Credits")
	float GetCredit();

	
protected:

private:

	UPROPERTY()
	float credit = 0;
	
};


// notify when an AI character died.
// use implementation or addDynamic?
//Enemy health zero, add credit to playerstate of instigator)