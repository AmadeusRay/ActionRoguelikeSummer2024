// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinUp.h"
#include "SPlayerState.h"
#include "Net/UnrealNetwork.h"

ASCoinUp::ASCoinUp()
{
	CreditsAmount = 10;

	bReplicates=true;
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
		OnRep_CoinTaken();
	}
}

void ASCoinUp::OnRep_CoinTaken()
{
	bCoinTaken = true;
	HideAndCooldownPowerup();
}

void ASCoinUp::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ASCoinUp, bCoinTaken);
}