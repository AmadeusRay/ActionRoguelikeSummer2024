// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

ASPlayerState::ASPlayerState()
{
}

int32 ASPlayerState::AddCredit()
{
	++Credit;
	OnCreditsChanged.Broadcast(this, Credit);
	UE_LOG(LogTemp, Warning, TEXT("ADDED CREDIT, %f"), Credit);
	return 0;
}

int32 ASPlayerState::RemoveCredit()
{
	--Credit;
	OnCreditsChanged.Broadcast(this, Credit);
	UE_LOG(LogTemp, Warning, TEXT("REMOVED CREDIT, %f"), Credit);
	return 0;
}

int32 ASPlayerState::GetCredit()
{
	return Credit;
}



