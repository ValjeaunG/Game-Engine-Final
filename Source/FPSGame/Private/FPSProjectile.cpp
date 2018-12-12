// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "FPSProjectile.h"
#include "FPSCharacter.h"
#include "EngineUtils.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/SphereComponent.h"

namespace Parameters
{
	double separation_distance = 0.1;
	double cohesion_distance = 6.0;
	double alignment_distance = 4.0;

	double separation_force_mag = 5;
	double cohesion_force_mag = 0.1;
	double alignment_force_mag = 2.0;
	double target_force_mag = 24.0;

	double friction = 0.95;
}

AFPSProjectile::AFPSProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
	
	// Use a sphere as a simple collision representation
	CollisionComp = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComp"));
	CollisionComp->InitSphereRadius(2.0f);
	CollisionComp->SetCollisionProfileName("Projectile");
	CollisionComp->SetSimulatePhysics(true);
	CollisionComp->OnComponentHit.AddDynamic(this, &AFPSProjectile::OnHit);	// set up a notification for when this component hits something blocking
	//CollisionComp->SetSimulatePhysics(true);

	// Players can't walk on it
	CollisionComp->SetWalkableSlopeOverride(FWalkableSlopeOverride(WalkableSlope_Unwalkable, 0.f));
	CollisionComp->CanCharacterStepUpOn = ECB_No;

	// Set as root component
	RootComponent = CollisionComp;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileMovement->UpdatedComponent = CollisionComp;
	ProjectileMovement->InitialSpeed = 50.f;
	ProjectileMovement->MaxSpeed = 300.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = true;

	// Die after 3 seconds by default
	InitialLifeSpan = 300.0f;
}

void AFPSProjectile::Tick(float DeltaTime)
{
	FVector avg_pos = { 0,0,0 };
	FVector avg_vel = { 0,0,0 };
	int n_bullets = 0;

	UWorld* world = GetWorld();
	Super::Tick(DeltaTime);
	for (TActorIterator<AFPSProjectile>i(world, AFPSProjectile::StaticClass()); i; ++i)
	{
		AFPSProjectile* projectile = *i;
		if (this == projectile) continue;

		/*FVector pos_i = AActor::GetActorLocation();
		FVector vel_i = AActor::GetVelocity();
		FVector impulse;*/

		float distance = this->GetDistanceTo(projectile);
		FVector projectile_loc = projectile->CollisionComp->GetRelativeTransform().GetLocation();
		FVector this_loc = CollisionComp->GetRelativeTransform().GetLocation();
		if (distance < 1000)
		{
			n_bullets++;
			avg_pos += projectile_loc;
			avg_vel += projectile->GetVelocity();
		}

		if (distance < 150)
		{
			//apply sepaeration
			FVector separation = this_loc - projectile_loc;
			separation.Normalize();
			CollisionComp->AddImpulse(separation * 300);
		}

		UE_LOG(LogTemp, Warning, TEXT("%f"), distance);
	}

	if (n_bullets != 0)
	{
		avg_pos /= n_bullets;
		avg_vel /= n_bullets;
		//apply cohesion
		FVector cohesion = avg_pos - CollisionComp->GetRelativeTransform().GetLocation();
		cohesion.Normalize();
		CollisionComp->AddImpulse(cohesion * 250);
		//apply alignment
		avg_vel.Normalize();
		CollisionComp->AddImpulse(avg_vel * 0.9);
	}
}

void AFPSProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		//OtherComp->AddImpulseAtLocation(GetVelocity() * 100.0f, GetActorLocation());

		//Destroy();
	}
}
