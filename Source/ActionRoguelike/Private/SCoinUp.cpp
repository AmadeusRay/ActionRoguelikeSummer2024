// Fill out your copyright notice in the Description page of Project Settings.


#include "SCoinUp.h"
#include "SCharacter.h"
#include "SPlayerState.h"

ASCoinUp::ASCoinUp()
{
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	// Disable collision, instead we use SphereComp to handle interaction queries
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetupAttachment(RootComponent);
}

void ASCoinUp::Interact_Implementation(APawn* InstigatorPawn)
{
	if (!ensure(InstigatorPawn))
	{
		return;
	}
	
	ASCharacter* PlayerCharacter = Cast<ASCharacter>(InstigatorPawn);

	ASPlayerState* PS = Cast<ASPlayerState>(PlayerCharacter->GetPlayerState<ASPlayerState>());
	
	PS->AddCreditState();
	HideAndCooldownPowerup();
}

