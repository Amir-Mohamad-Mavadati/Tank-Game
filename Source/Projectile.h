// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Projectile.generated.h"

class USoundBase;

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Components")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovement;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	UPROPERTY(EditAnywhere, Category = "Damage")
	float Damage = 50.f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* HitParticles;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	UParticleSystemComponent* HitParticlesComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* LuanchSound;

	UPROPERTY(EditDefaultsOnly, Category = "Sounds")
	USoundBase* HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Effects")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass;
};
