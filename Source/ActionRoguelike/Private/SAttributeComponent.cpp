// Fill out your copyright notice in the Description page of Project Settings.


#include "SAttributeComponent.h"
#include "SGameModeBase.h"
#include "AI/SAICharacter.h"
#include "Net/UnrealNetwork.h"


static TAutoConsoleVariable<float> CVarDamageMultiplier(TEXT("su.DamageMultipler"), 1.0f, TEXT("Global Damage Modifier for Attribute Component."), ECVF_Cheat);

USAttributeComponent::USAttributeComponent()
{
	Rage = 0;
	HealthMax = 100;
	Health = HealthMax;
	RageMax = 100;

	SetIsReplicatedByDefault(true); // if in constructor use SetIsReplicatedByDefault() not SetIsReplicated()

}

bool USAttributeComponent::Kill(AActor* InstigatorActor)
{
	return ApplyHealthChange(InstigatorActor, -GetHealthMax());
}


bool USAttributeComponent::IsAlive() const
{
	return Health > 0.0f;
}

//Health

bool USAttributeComponent::IsFullHealth() const
{
	return Health == HealthMax;
}


float USAttributeComponent::GetHealth() const
{
	return Health;
}

float USAttributeComponent::GetHealthMax() const
{
	return HealthMax;
}

bool USAttributeComponent::ApplyHealthChange(AActor* InstigatorActor, float Delta)
{
	if (!GetOwner()->CanBeDamaged() && Delta < 0.0f)
	{
		return false;
	}

	if(Delta < 0.0f)
	{
		float DamageMultiplier = CVarDamageMultiplier.GetValueOnGameThread();
	}

	// For Rage
	if (Delta <= 0)
	{
		Rage = FMath::Clamp(Rage - Delta, 0.0f, RageMax);
	}
	

	float OldHealth = Health;

	Health = FMath::Clamp(Health + Delta, 0.0f, HealthMax);
	
	float ActualDelta = Health - OldHealth;
	OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);

	//Thorns damage
	AActor* OwnerActor = Cast<AActor>(GetOwner());
	USActionComponent* ActionComp = Cast<USActionComponent>(OwnerActor->GetComponentByClass(USActionComponent::StaticClass()));
	static FGameplayTag Tag = FGameplayTag::RequestGameplayTag("Status.Thorns");
	if (ActionComp->ActiveGameplayTags.HasTag(Tag))
		{
		if (GetOwner()!=InstigatorActor)
			{
			USAttributeComponent* AttributeComp = USAttributeComponent::GetAttributes(InstigatorActor);
			AttributeComp->ApplyHealthChange(InstigatorActor, -2);
			}
		}

	//OnHealthChanged.Broadcast(InstigatorActor, this, Health, ActualDelta);
	if(ActualDelta != 0.0f)
	{
		MulticastHealthChanged(InstigatorActor, Health, ActualDelta);
	}
	
	// Died
	if (ActualDelta < 0.0f && Health == 0.0f)
	{
		ASGameModeBase* GM = GetWorld()->GetAuthGameMode<ASGameModeBase>();
		if (GM)
		{
			GM->OnActorKilled(GetOwner(), InstigatorActor);
		}
	}
	
	return ActualDelta != 0;
}

//Rage
bool USAttributeComponent::IsFullRage() const
{
	return Rage == RageMax;
}

float USAttributeComponent::GetRage() const
{
	return Rage;
}

float USAttributeComponent::GetRageMax() const
{
	return RageMax;
}

void USAttributeComponent::LoseRage()
{
	 Rage -= (float)25;
}


USAttributeComponent* USAttributeComponent::GetAttributes(AActor* FromActor)
{
	if (FromActor)
	{
		return Cast<USAttributeComponent>(FromActor->GetComponentByClass(USAttributeComponent::StaticClass()));
	}
	return nullptr;
}


bool USAttributeComponent::IsActorAlive(AActor* Actor)
{
	USAttributeComponent* AttributeComp = GetAttributes(Actor);
	if (AttributeComp)
	{
		return AttributeComp->IsAlive();
	}

	return false;
}

void USAttributeComponent::MulticastHealthChanged_Implementation(AActor* InstigatorActor, float NewHealth, float Delta)
{
	OnHealthChanged.Broadcast(InstigatorActor, this, NewHealth, Delta);
}


void USAttributeComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USAttributeComponent, Health);
	//DOREPLIFETIME(USAttributeComponent, HealthMax);

	DOREPLIFETIME_CONDITION(USAttributeComponent, HealthMax, COND_OwnerOnly); // only owner sees the change
}

