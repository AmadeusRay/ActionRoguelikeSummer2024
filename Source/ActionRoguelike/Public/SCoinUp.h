// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SPowerupActor.h"
#include "SCoinUp.generated.h"



/**
 * 
 */
UCLASS()
class ACTIONROGUELIKE_API ASCoinUp : public ASPowerupActor
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere, Category = "Credts")
	int32 CreditsAmount;

public:
	void Interact_Implementation(APawn* InstigatorPawn) override;

	ASCoinUp();
	
};
