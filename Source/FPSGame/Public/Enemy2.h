// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy_Interface.h"
#include "GameFramework/Actor.h"
#include "Enemy2.generated.h"

UCLASS()
class FPSGAME_API AEnemy2 : public AActor, public IEnemy_Interface
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemy2();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
