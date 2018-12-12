// Fill out your copyright notice in the Description page of Project Settings.

#include "Enemy2.h"


// Sets default values
AEnemy2::AEnemy2()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Level = 2;
	Strength = 5;
}

// Called when the game starts or when spawned
void AEnemy2::BeginPlay()
{
	Super::BeginPlay();
	
	Attack();
}

// Called every frame
void AEnemy2::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

