// Fill out your copyright notice in the Description page of Project Settings.


#include "SPowerupActor.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Net/UnrealNetwork.h"


ASPowerupActor::ASPowerupActor()
{
	SphereComp = CreateDefaultSubobject<USphereComponent>("SphereComp");
	SphereComp->SetCollisionProfileName("Powerup");
	RootComponent = SphereComp;

	// forgot to add this, check power up for changes
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>("MeshComp");
	//Disables collision, we use the sphere comp to handle instance queries
	MeshComp->SetCollisionEnabled((ECollisionEnabled::NoCollision));
	MeshComp->SetupAttachment(RootComponent);

	RespawnTime = 10.0f;
	bIsActive = true;

	SetReplicates(true);
}


void ASPowerupActor::Interact_Implementation(APawn* InstigatorPawn)
{
	// logic in derived classes...
}

void ASPowerupActor::ShowPowerup()
{
	SetPowerupState(true);
}


void ASPowerupActor::HideAndCooldownPowerup()
{
	SetPowerupState(false);
	
	GetWorldTimerManager().SetTimer(TimerHandle_RespawnTimer, this, &ASPowerupActor::ShowPowerup, RespawnTime);
}

void ASPowerupActor::SetPowerupState(bool bNewIsActive)
{
	bIsActive = bNewIsActive;
	OnRep_IsActive();
}

void ASPowerupActor::OnRep_IsActive()
{
	SetActorEnableCollision(bIsActive);
	// Set visibility on root and all children
	RootComponent->SetVisibility(bIsActive, true);
}

void ASPowerupActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ASPowerupActor, bIsActive);
}