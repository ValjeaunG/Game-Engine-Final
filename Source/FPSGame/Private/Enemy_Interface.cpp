// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy_Interface.h"


// Add default functionality here for any IEnemy_Interface functions that are not pure virtual.

void IEnemy_Interface::Attack()
{
	UE_LOG(LogTemp, Warning, TEXT("A level %d enemy attacks and does %d damage."), Level, Strength);
}
