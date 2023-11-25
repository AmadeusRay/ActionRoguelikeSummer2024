// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

ASPlayerState::ASPlayerState()
{
}

float ASPlayerState::AddCreditState()
{
	++ credit;
	UE_LOG(LogTemp, Warning, TEXT("ADDED CREDIT, %f"), credit);
	return 0;
}

float ASPlayerState::RemoveCreditState()
{
	--credit;
	UE_LOG(LogTemp, Warning, TEXT("REMOVED CREDIT, %f"), credit);
	return 0;
}

float ASPlayerState::GetCredit()
{
	return credit;
}



