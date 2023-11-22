// Fill out your copyright notice in the Description page of Project Settings.


#include "SPlayerState.h"

ASPlayerState::ASPlayerState()
{
}

float ASPlayerState::AddCreditState()
{
	UE_LOG(LogTemp, Warning, TEXT("ADDED CREDIT, %f"), credit);
	return ++credit;
}


