// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinUp.h"
#include "SPlayerState.h"

ASCoinUp::ASCoinUp()
{
	CreditsAmount = 80;
}

void ASCoinUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	
	if (ASPlayerState* PS = InstigatorPawn->GetPlayerState<ASPlayerState>())
	{
		PS->AddCredits(CreditsAmount);
		HideAndCooldownPowerup();
	}
}

