// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinUp.h"
#include "SCharacter.h"
#include "SPlayerState.h"

ASCoinUp::ASCoinUp()
{}

void ASCoinUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	
	ASCharacter* PlayerCharacter = Cast<ASCharacter>(InstigatorPawn);

	ASPlayerState* PS = Cast<ASPlayerState>(PlayerCharacter->GetPlayerState<ASPlayerState>());
	
	PS->AddCredit();
	HideAndCooldownPowerup();
}

